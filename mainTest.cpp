#include "Target.h"
#include "Arrow.h"
#include <string>
#include <iostream>

#include "Target.h"
#include "Arrow.h"
#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#define TAM_GERACAO 50
#define NUM_GERACOES 30

//gera um double entre 0 e 1
double rand_double(){
    double ret = (1.0*rand())/(1.0*RAND_MAX);
    return ret;
}

struct individuo{   
    double velocity;
    double theta;
    Arrow* arrow;

    bool operator<(const individuo &i) const{
        return arrow->GetScore() < i.arrow->GetScore();
    }

    bool operator>(const individuo &i) const{
        return arrow->GetScore() > i.arrow->GetScore();
    }
};

individuo mutacao( individuo ind ){

    int moeda = rand()%3;

    individuo mutado;

    if(moeda == 0){
        mutado.theta = ind.theta;
        mutado.velocity = ind.velocity;
    }else if(moeda == 1){
        mutado.theta = ind.theta;
        double mutation_velocity = rand_double()/50.0 - 0.01;
        mutado.velocity = ind.velocity + mutation_velocity;

        mutado.velocity = std::min(mutado.velocity, 3.0);
        mutado.velocity = std::max(mutado.velocity, 0.1);
    }else{
        mutado.velocity = ind.velocity;

        double mutation_theta = rand_double()/50.0 - 0.01;

        mutado.theta = ind.theta + mutation_theta;

        mutado.theta = std::min(mutado.theta, (M_PI/2));
        mutado.theta = std::max(mutado.theta, 0.0);
    }

    return mutado; 
}

individuo cruzamento(individuo mom, individuo dad){
    individuo child;

    child.velocity = (mom.velocity + 4*dad.velocity)/5;
    child.theta = (mom.theta + 4*dad.theta)/5;

    return child;
}

void evaluate_generation(std::vector<individuo> &generation, std::vector<double> &best_of_generation, std::vector<double> &mean_of_generation){
    double best = 0;
    double mean = 0;
    for(int i = 0; i < TAM_GERACAO; i++){
        double theta = generation[i].theta;
        double velocity = generation[i].velocity;
        generation[i].arrow->Update(theta, velocity);

        mean += generation[i].arrow->GetScore();
        best = std::max(best , generation[i].arrow->GetScore());
    }
    mean /= TAM_GERACAO;
    best_of_generation.push_back( best );
    mean_of_generation.push_back(mean);
}

void next_generation(std::vector<individuo> &generation, std::vector<Arrow *> &Arrows){

    std::sort(generation.rbegin(), generation.rend());


    std::vector<individuo> new_generation(TAM_GERACAO);

    new_generation[0] = generation[0];

    //quantidade de novos que serao gerados atraves de cruzamento
    int cruza = TAM_GERACAO/2;

    for(int i = 1; i < cruza; i++){

        new_generation[i] = cruzamento(generation[0], generation[i]);
    }
    //o indice de quem eu estou mutando no momento
    for(int i = cruza; i < TAM_GERACAO; i++){
        
        //cruzamento do melhor de todos cos os iniciais
        new_generation[i] = mutacao( generation[i - cruza] );
        

    }

    for(int i = 0; i < TAM_GERACAO; i++){
        generation[i] = new_generation[i];
        generation[i].arrow = Arrows[i];
        generation[i].arrow->Update(generation[i].theta, generation[i].velocity);
    }

}


std::vector<individuo> generate_initial_population(std::vector<Arrow*> &Arrows){

    std::vector<individuo> population(TAM_GERACAO);


    for(int i = 0; i < TAM_GERACAO; i++){

        population[i].arrow = Arrows[i];
        population[i].theta = rand_double()*M_PI/2.0;
        population[i].velocity = rand_double()*2.5; 

    }

    return population;

}


int main(void){
 
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(800, 800, "Minha Janela", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();


    // GLSL para Vertex Shader
    std::string vc = "attribute vec3 position;\n"
    "uniform mat4 mat_transformation;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = mat_transformation * vec4(position, 1.0);\n"
    "}\n";

    char vertex_code[vc.size()+1];
    
    for (int i = 0; i < vc.size(); i++)
    {
        vertex_code[i] = vc[i];
    }
    vertex_code[vc.size()] = 0;

    // GLSL para Fragment Shader
    std::string fc =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n"; 

    char fragment_code[fc.size()+1];
    
    for (int i = 0; i < fc.size(); i++)
    {
        fragment_code[i] = fc[i];
        
    }
    fragment_code[fc.size()] = 0;

    char* a = vertex_code;
    char* b = fragment_code;

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders

    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // Associando nosso código-fonte GLSL aos slots solicitados
    glShaderSource(vertex, 1, (const GLchar *const *)&a, NULL);
    glShaderSource(fragment, 1,(const GLchar *const *)&b, NULL);

    // Compilando o Vertex Shader e verificando erros
    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n",info);

    }

    // Compilando o Fragment Shader e verificando erros
    glCompileShader(fragment);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n",info);

    }
    
    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);

    // Preparando dados para enviar a GPU
    coordenadas vertices[10000];
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    std::vector<Arrow*> Arrows(TAM_GERACAO);    

    Target *alvo = new Target(vertices, 0, 128, 0.8, 0.5, 0, 0, 1, 0, 0.08, 0.06, 0.04, 0.02);
    Obstacle *obstaculo = new Obstacle(vertices, 128 ,4, 0.0, -0.1, 0.5, 0, 0, 1, 0);

    for(int i = 0; i < TAM_GERACAO; i++){
        Arrows[i] = new Arrow(vertices, 132 + i*14, 14, 0 , 0, -0.8, -0.2, 0.3, 0, 1, 1.5, alvo, obstaculo);
    }

    std::vector<double> best_of_generation;
    std::vector<double> mean_of_generation;
    auto generation = generate_initial_population(Arrows);

    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
    

    GLint loc_color = glGetUniformLocation(program, "color");
    GLint loc_matriz = glGetUniformLocation(program, "mat_transformation");


    // Exibindo nossa janela
    glfwShowWindow(window);


    double timestamp = 0.03;
    double max_time = 4;
    int geracao = 0;
    double time = 0;
    evaluate_generation(generation, best_of_generation, mean_of_generation);
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        alvo->draw(loc_color, loc_matriz);
        obstaculo->draw(loc_color, loc_matriz);

        for(int i = 0; i < TAM_GERACAO; i++){
            Arrows[i]->Move(timestamp);
            Arrows[i]->draw(loc_color, loc_matriz);
        }
        glfwSwapBuffers(window);
        time += timestamp;
        if(time >= max_time){
            if(geracao >= NUM_GERACOES){
                break;
            }
            
            geracao++;
            for(int i = 0; i < 1; i++){
                next_generation(generation, Arrows);
                evaluate_generation(generation, best_of_generation, mean_of_generation);
            }
            time = 0;
        }
        
    }

    /*
    escrevendo o melhor e a media da geracao no arquivo de log
    */

    FILE* fp;
    fp = fopen("dados.txt", "w");
    int sz = best_of_generation.size();

    fprintf(fp, "%d\n", sz);

    for(double best: best_of_generation){
        fprintf(fp, "%lf\n", best);
    }
    for(double mean: mean_of_generation){
        fprintf(fp, "%lf\n", mean);
    }

    fclose(fp);


 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
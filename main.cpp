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
#define NUM_ALVOS 2
#define NUM_GERACOES_PROCESSA 10

double mutation_tax = 1.0;

double HP_ALVO = 20000;

int count_alvos = 0;

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

/*
esta funcao faz a alteracao na taxa de mutacao, de acordo com o valor
dos melhores individuos das geracoes passadas, vendo o quanto o melhor esta
proximo do maximo e o quanto ele melhorou em relacao as geracoes anterioes
@PARAMETROS
    std::vector<double> bests - vetor com o score do melhor individuo de cada geracao
*/
void change_mutation_tax( std::vector<double> &bests){

    double best_at = bests.back();

    //compara o melhor de todos com o melhor de todos de 5 geracoes atras
    
    //se nao teve ainda 5 geracoes, pega a geracao mais antiga(de indice 0 no vetor)
    double best_anterior = bests[0];
    if( int(bests.size()) > 5 ){
        best_anterior = bests[  int(bests.size()) -6 ];
    }
    double melhora = best_at - best_anterior;

    //se o melhor ja alcancou o maximo, faz a formula padrao
    if(best_at >= 1 - 0.01){
        //mutacao = 1 - x^5
        mutation_tax = 1.0 - pow(best_at,5);
    }else{
        //se nao melhorou nas ultimas 5 geracoes, aumenta ao maximo a mutacao
        if(melhora <= 0.001){
            mutation_tax = 1.0;
        //se melhorou, utiliza a formula padrao
        }else{
            //mutacao = 1 - x^5
            mutation_tax = 1.0 - pow(best_at,5);
        }
    }
    mutation_tax *= 3;
}

/*
Esta funcao calcula o quanto um parametro deve mutar
de acordo com a taxa de mutacao
@RETORNO
    double - o quanto deve-se mutar
*/
double get_mutation(){
    //esse numero esta entre -0.5 e 0.5, e baseado
    double ini_mutation = rand_double() - 0.5;
    
    double mut = ini_mutation*mutation_tax;        
    return mut;
}

/*
Dado um inviduo da nossa populacao, realiza uma mutacao, e 
retorna o individuo mutado, a mutacao pode variar a velocidade da flecha,
o angulo, ou nao mutar nada
@PARAMETROS
    individuo ind - individuo a ser mutado
@RETORNO
    individuo - inviduo mutado.
*/
individuo mutacao( individuo ind ){

    int moeda = rand()%3;

    individuo mutado;
    //se nao muta
    if(moeda == 0){
        mutado.theta = ind.theta;
        mutado.velocity = ind.velocity;
    //se muta a velocidade
    }else if(moeda == 1){
        mutado.theta = ind.theta;
        double mutation_velocity = get_mutation();
        mutado.velocity = ind.velocity + mutation_velocity;

        mutado.velocity = std::min(mutado.velocity, 3.0);
        mutado.velocity = std::max(mutado.velocity, 0.1);
    //se muta o angulo
    }else{
        mutado.velocity = ind.velocity;

        double mutation_theta = get_mutation();

        mutado.theta = ind.theta + mutation_theta;

        mutado.theta = std::min(mutado.theta, (M_PI/2));
        mutado.theta = std::max(mutado.theta, 0.0);
    }

    return mutado; 
}

/*
Dado dois individuos da populacao, esta funcao faz o cruzamento
dos dois individuos e retorna seu filho, o filho tende a puxar
mais as caracteristicas do pai( a mae deve ser o melhor de todos)
@PARAMETROS
    individuo mom - o melhor de todos da geracao
    individuo dad - um indiviuo que cruzara com o melhor de todos
@RETORNO
    invidivuo - o filho gerado.
*/
individuo cruzamento(individuo mom, individuo dad){
    individuo child;
    //faz a media pondera, com a mae tendo peso 1 e o pai peso 4
    child.velocity = (mom.velocity + 4*dad.velocity)/5;
    child.theta = (mom.theta + 4*dad.theta)/5;

    return child;
}

/*
Esta funcao avalia todos os individuos de uma geracao, e armazena no 
vetor a media dos scores e o score do melhor de todos.
@PARAMETROS
    std::vector<individuo> &generation - geracao a ser avaliada
    std:vector<double> &best_of_generation - vetor que armazena o score do melhor de todos das geracoes
    std::vector<double> &mean_of_generation - vetor que armazena a media dos score de cada geracao
*/
void evaluate_generation(std::vector<individuo> &generation, std::vector<double> &best_of_generation, std::vector<double> &mean_of_generation){
    double best = 0;
    double mean = 0;
    //iterando sobre os individuos
    for(int i = 0; i < TAM_GERACAO; i++){
        double theta = generation[i].theta;
        double velocity = generation[i].velocity;
        generation[i].arrow->Update(theta, velocity);
        //adicionando a media
        mean += generation[i].arrow->GetScore();
        //comparando com o melhor atual
        best = std::max(best , generation[i].arrow->GetScore());
    }
    //armazenando a media e o melhor de todos
    mean /= TAM_GERACAO;
    best_of_generation.push_back( best );
    change_mutation_tax(best_of_generation);
    mean_of_generation.push_back(mean);
}

/*
Esta funcao calcula a proxima geracao de indivuos em funcao da geracao atual
@PARAMETROS
    std::vector<individuo> &generation - vetor armazena a geracao atual, este vetor
                                        sera sobrescrito com a nova geracao
    std::vector<Arrow*>  &Arrows - vetor de flechas que sao desenhadas na tela.
*/
void next_generation(std::vector<individuo> &generation, std::vector<Arrow *> &Arrows){

    //ordenando a geracao pelo score
    std::sort(generation.rbegin(), generation.rend());


    std::vector<individuo> new_generation(TAM_GERACAO);
    //armazenando o melhor de todos
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
    //passando o vetor da new_generation para generation e linkando a 
    //Arrow a cada individuo.
    for(int i = 0; i < TAM_GERACAO; i++){
        generation[i] = new_generation[i];
        generation[i].arrow = Arrows[i];
        generation[i].arrow->Update(generation[i].theta, generation[i].velocity);
    }

}

/*
Esta funcao gera uma populacao inicial, gerando um conjunto de individuos
randomicamente.
@PARAMETROS
    std::vector<Aroow*> &Arrows - vetor de flechas que sao desenhadas na tela.
@RETORNO
    std::vector<individuo> - populacao/geracao inicial.
*/
std::vector<individuo> generate_initial_population(std::vector<Arrow*> &Arrows){

    std::vector<individuo> population(TAM_GERACAO);

    //geranco os parametros randomicamente e linkando as flechas
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

    /*
    Criando o vetor de flechas que serao desenhas,
    o alvo, o obstaculo.
    */
    std::vector<Arrow*> Arrows(TAM_GERACAO);    

    Target *alvo = new Target(vertices, 0, 128, 0.3, -0.05, 0, 0, 1, 0, 0.08, 0.06, 0.04, 0.02, HP_ALVO);
    Obstacle *obstaculo = new Obstacle(vertices, 128 ,4, 0.0, -0.1, 0.5, 0, 0, 1, 0);

    for(int i = 0; i < TAM_GERACAO; i++){
        Arrows[i] = new Arrow(vertices, 132 + i*14, 14, 0 , 0, -0.8, -0.2, 0.3, 0, 1, 1.5, alvo, obstaculo);
    }
    /*
    criando os vetores que armazena o score do melhor de todos e a media,
    e criando a populacao inicial.
    */
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

    /*
    variaveis de controle da simulacao
    */
    double timestamp = 0.03;
    double max_time = 4;
    int geracao = 0;
    double time = 0;
    //necessario avaliar a geracao inicial, para desenhar, para arrumar o comportamento
    //das flechas
    evaluate_generation(generation, best_of_generation, mean_of_generation);
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        //desenhando o alvo, obstaculo e as flechas.
        alvo->draw(loc_color, loc_matriz);
        obstaculo->draw(loc_color, loc_matriz);

        for(int i = 0; i < TAM_GERACAO; i++){
            Arrows[i]->Move(timestamp);
            Arrows[i]->draw(loc_color, loc_matriz);
        }
        glfwSwapBuffers(window);

        //aumentando o tempo
        time += timestamp;
        //se o tempo limite acabou, encerra a simulacao da geracao atual
        if(time >= max_time){
            /*
            se o alvo morreu, muda o alvo de local
            */
            if(alvo->isDead()){
                count_alvos++;
                //

                double new_y = rand_double()*1.8 - 0.9;
                alvo->setY(new_y);

                double new_x = rand_double()*0.5+ 0.3;
                alvo->setX(new_x);
                
            }
            /*
            se passou da quantidade de alvos que queremos matar, encerra o programa
            */
            if(count_alvos >= NUM_ALVOS) break;
            
            /*
            Faz um loop para processar um numero X de geracoes, sem que tenha que simulalas,
            com isto, conseguimos, por exemplo, mostrar na tela de 10 em 10 geracoes,
            ao inves de uma.
            */
            for(int i = 0; i < NUM_GERACOES_PROCESSA; i++){
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
#include "Target.h"
#include "Arrow.h"
#include <string>
#include <iostream>

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
    coordenadas vertices[2000];
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    /*chamando as funcoes de criar os objetos e atualizando atual*/
    Target *alvo = new Target(vertices, 0, 128, 0.5, 0.5, 0, 0, 1, 0, 0.08, 0.06, 0.04, 0.02);
    Arrow *flecha = new Arrow(vertices, 128, 14, -0.5, 0, 0, 0, 0.5, 1, 1.26598, 1, alvo);

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

    std::cout << flecha->GetScore() << std::endl;

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        alvo->draw(loc_color, loc_matriz);
        flecha->Move(0.017);
        flecha->draw(loc_color, loc_matriz);

        glfwSwapBuffers(window);
        
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
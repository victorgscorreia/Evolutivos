#include "Obstacle.h"
    
/*
Construtor da classe target
@PARAMETROS
    coordenadas* coord  - endereco do vetor com os vertices para serem envidos a GPU
    int vertice_inicial - posicao do vertice inical no vetor de vertices
    int num_vertices    - numero de vertices da figura
    double x            - posicao no eixo x do obstaculo
    double min_y        - posicao de baixo do obstaculo no eixo y
    double max_y        - posicao de cima do obstaculo no eixo y
    double tx           - translacao em x
    double ty           - translacao em y
    double s            - escala do obstaculo
    double theta        - algulo de rotacao do obstaculo
OBS: alterar os parametro de translacao rotacao e escala nao alteram as propriedades do obstaculo na simulacao
        somente de forma visual.
*/
Obstacle::Obstacle(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double min_y, double max_y, double tx, double ty, double s, double theta) : Object(vertice_inicial, num_vertices, x, 0, tx, ty, s, theta)
{

    this->min_y = min_y;
    this->max_y = max_y;


    int atual = this->vertice_inicial;

    vertices[atual].x = x - 0.005;
    vertices[atual].y = min_y;
    atual++;

    vertices[atual].x = x + 0.005;
    vertices[atual].y = min_y;
    atual++;

    vertices[atual].x = x - 0.005;
    vertices[atual].y = max_y;
    atual++;

    vertices[atual].x = x + 0.005;
    vertices[atual].y = max_y;
    atual++;

    return;
}

/*
Desenha o objeto na tela. Cria a matriz de transformacao e faz
chamadas ao openGL para desenha o objeto na tela
@PARAMETROS
    GLint loc_color  - variavel associada a variavel color na GPU
    GLint loc_matriz - variavel associada a variavel matriz na GPU
@RETORNO
    int ret - 0 funcao finalizada com sucesso
*/
int Obstacle::draw(GLint loc_color, GLint loc_matriz){
    matriz_transformacao_objeto(loc_matriz);

    int atual = this->vertice_inicial;
    glUniform4f(loc_color, 0, 0, 0, 1);
    desenha_quadrado(atual);
    return 0;
}

/*
Dada a altura y em que a flecha esta no memento em que atinge a coordenada x do obstaculo,
a funcao retorna se colidiu ou nao
@PARAMETROS
    double  yArrow - O valor da coordenada y da flecha no memento em que ela esta na coordenada x do obstaculo
@RETORNO
    int ret - 0 nao atingiu o obstaculo
                    - 1 atingiu o obstaculo
*/
int Obstacle::checkColision(double yArrow){
    if(this->min_y <= yArrow && yArrow <= this->max_y){
        return 1;
    }
    return 0;
}

/*
Retorna o valor da coordenada x do obstaculo
@RETORNO
    double x - valor da coordenada x do obstaculo
*/
double Obstacle::getX(){
    return this->x;
}
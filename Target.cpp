#include "Target.h"
#include <iostream>

/*
Construtor da classe alvo
@PARAMETROS
    coordenadas* coord  - endereco do vetor com os vertices para serem envidos a GPU
    int vertice_inicial - posicao do vertice inical no vetor de vertices
    int num_vertices    - numero de vertices da figura
    double x            - posicao no eixo x do alvo
    double y            - posicao no eixo y do alvo
    double tx           - translacao em x
    double ty           - translacao em y
    double s            - escala do alvo
    double theta        - algulo de rotacao do alvo
    double radius1      - tamnho da elipse mais externa
    double radius2      - tamnho da 2 elipse
    double radius3      - tamanho da 3 elipse
    double radius4      - tamanho da elipse mais interna
OBS: alterar os parametro de translacao rotacao e escala nao alteram as propriedades do alvo na simulacao
        somente de forma visual.
*/
Target::Target(coordenadas* coord, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, double radius1, double radius2, double radius3, double radius4) : Object(vertice_inicial, num_vertices, x, y, tx, ty, s, theta)
{
    this->radius1 = radius1;
    this->radius2 = radius2;
    this->radius3 = radius3;
    this->radius4 = radius4;

    int atual = this->vertice_inicial;

    add_elipse(coord, atual, 32, x, y, radius1);
    atual += 32;
    add_elipse(coord, atual, 32, x, y, radius2);
    atual += 32;
    add_elipse(coord, atual, 32, x, y, radius3);
    atual += 32;
    add_elipse(coord, atual, 32, x, y, radius4);

    return;
}

Target::~Target()
{
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
int Target::draw(GLint loc_color, GLint loc_matriz)
{   
    matriz_transformacao_objeto(loc_matriz);

    int atual = this->vertice_inicial;

    glUniform4f(loc_color, 1, 0, 0, 1);
    desenha_circulo(atual, 32);
    atual+=32;

    glUniform4f(loc_color, 1, 1, 1, 1);
    desenha_circulo(atual, 32);
    atual+=32;

    glUniform4f(loc_color, 0, 0, 1, 1);
    desenha_circulo(atual, 32);
    atual+=32;

    glUniform4f(loc_color, 1, 1, 1, 1);
    desenha_circulo(atual, 32);

    return 0;
}

/*
Dada a altura y em que a flecha esta no memento em que atinge a coordenada x do alvo,
a funcao retorna o score feito pela flecha
@PARAMETROS
    double  yArrow - O valor da coordenada y da flecha no memento em que ela esta na coordenada x do alvo
@RETORNO
    double score - 0 nao atingiu o alvo
                    - > 0 pontuacao feita
*/
double Target::checkColision(double yArrow)
{    
    if (yArrow <= this->y + this->radius1 * 1.6 && yArrow >= this->y - this->radius1 * 1.6)
    {

        double dist = this->y  - yArrow;
        if(dist < 0) dist = -dist;

        
        return (5.0 - dist*dist)/5.0;
    }
    return 0;
}

/*
Retorna o valor da coordenada x do alvo
@RETORNO
    double x - valor da coordenada x do alvo
*/
double Target::getX()
{
    return this->x;
}

/*
Retorna o valor da coordenada y do alvo
@RETORNO
    double y - valor da coordenada y do alvo
*/
double Target::getY()
{
    return this->y;
}
#include "Object.h"

Object::Object(int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta)
{   
    this->vertice_inicial = vertice_inicial;
    this->num_vertices = num_vertices;
    this->x = x;
    this->y = y;
    this->tx = tx;
    this->ty = ty;
    this->s = s;
    this->theta = theta;
    return;
}

Object::~Object()
{
    return;
}

int Object::draw(){

    return 0;
}

void Object::matriz_transformacao_objeto(GLint loc_matriz){

    //matriz de rotacao objeto baseado no seu angulo theta
    float cose = cos(this->theta);
    float seno = sin(this->theta);

    //matriz de rotacao
    float matriz_rotacao[16] = {
            cose, -seno, 0.0f, 0.0f,
            seno,  cose, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

    //matriz de escala objeto baseado no seu parametro s
    float s = this->s;
    float matriz_escala[16] = {
            s   , 0.0f, 0.0f, 0.0f,
            0.0f, s   , 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

    //matriz de transladacao do objeto baseado nos seus parametros tx e ty 
    float tx = this->tx;
    float ty = this->ty;
    float matriz_transladacao[16] = {
            1.0f, 0.0f, 0.0f, tx  ,
            0.0f, 1.0f, 0.0f, ty  ,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

    float matriz_final[16];
    //fazendo as multiplicacoes das matrizes
    mult_matrix(matriz_escala, matriz_rotacao, matriz_final);
    mult_matrix(matriz_transladacao, matriz_final , matriz_final);

    //setando o valor de gpu para ser a matriz final
    glUniformMatrix4fv(loc_matriz, 1, GL_TRUE, matriz_final);

}
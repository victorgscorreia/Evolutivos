#include "Object.h"

/*
Construtor da classe object
@PARAMETROS
    int vertice_inicial - posicao do vertice inical no vetor de vertices
    int num_vertices    - numero de vertices da figura
    double x            - posicao no eixo x da flecha
    double y            - posicao no eixo y da flecha
    double tx           - translacao em x
    double ty           - translacao em y
    double s            - escala da flecha
    double theta        - algulo de lancamento da flecha
*/
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

/*
Desenha o objeto na tela. Cria a matriz de transformacao e faz
chamadas ao openGL para desenha o objeto na tela
@PARAMETROS
    GLint loc_color  - variavel associada a variavel color na GPU
    GLint loc_matriz - variavel associada a variavel matriz na GPU
@RETORNO
    int ret - 0 funcao finalizada com sucesso
*/
int Object::draw(){

    return 0;
}

/*
Esta funcao monta a matriz de transformacao de um objeto baseado em seus parametros
de transformacao ( s, tx, ty e theta), e chama a passa esta matriz para a loc_matriz da
GPU
@PARAMETROS
    OBJ objeto - objeto que queremos montar a matriz de transformacao
    GLint loc_matriz - variavel linkada a matriz de tranformacao da GPU
*/
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
#ifndef OBJECT_H
#define OBJECT_H
#include "base.h"

class Object
{
public:
    
    int vertice_inicial;
    int num_vertices;
    double x;
    double y;
    double tx;
    double ty;
    double s;
    double theta;

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
    Object(int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta);
    
    ~Object();

    /*
    Desenha o objeto na tela. Cria a matriz de transformacao e faz
    chamadas ao openGL para desenha o objeto na tela
    @PARAMETROS
        GLint loc_color  - variavel associada a variavel color na GPU
        GLint loc_matriz - variavel associada a variavel matriz na GPU
    @RETORNO
        int ret - 0 funcao finalizada com sucesso
    */
    virtual int draw();

    /*
    Esta funcao monta a matriz de transformacao de um objeto baseado em seus parametros
    de transformacao ( s, tx, ty e theta), e chama a passa esta matriz para a loc_matriz da
    GPU
    @PARAMETROS
        OBJ objeto - objeto que queremos montar a matriz de transformacao
        GLint loc_matriz - variavel linkada a matriz de tranformacao da GPU
    */
    void matriz_transformacao_objeto(GLint loc_matriz);
};

#endif
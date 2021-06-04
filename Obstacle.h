#ifndef OBS_H
#define OBS_H

#include "Object.h"

class Obstacle : private Object 
{
private:
    double min_y;
    double max_y;

public:

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
    Obstacle(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double min_y, double max_y, double tx, double ty, double s, double theta);
  
    ~Obstacle();
    
    /*
    Desenha o objeto na tela. Cria a matriz de transformacao e faz
    chamadas ao openGL para desenha o objeto na tela
    @PARAMETROS
        GLint loc_color  - variavel associada a variavel color na GPU
        GLint loc_matriz - variavel associada a variavel matriz na GPU
    @RETORNO
        int ret - 0 funcao finalizada com sucesso
    */
    int draw(GLint loc_color, GLint loc_matriz);
  
    /*
    Dada a altura y em que a flecha esta no memento em que atinge a coordenada x do obstaculo,
    a funcao retorna se colidiu ou nao
    @PARAMETROS
        double  yArrow - O valor da coordenada y da flecha no memento em que ela esta na coordenada x do obstaculo
    @RETORNO
        int ret - 0 nao atingiu o obstaculo
                     - 1 atingiu o obstaculo
    */
    int checkColision(double yArrow);
  
    /*
    Retorna o valor da coordenada x do obstaculo
    @RETORNO
        double x - valor da coordenada x do obstaculo
    */
    double getX();
};

#endif
#ifndef TARGET_H
#define TARGET_H

#include "Object.h"

class Target : private Object 
{
private:
    double radius1;
    double radius2;
    double radius3;
    double radius4;

    double hp_ini;
    double hp;

public:
    /*
    Construtor da classe target
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
    Target(coordenadas* coord, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, double radius1, double radius2, double radius3, double radius4, double hp_ini);
   
    ~Target();

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
    Dada a altura y em que a flecha esta no memento em que atinge a coordenada x do alvo,
    a funcao retorna o score feito pela flecha
    @PARAMETROS
        double  yArrow - O valor da coordenada y da flecha no memento em que ela esta na coordenada x do alvo
    @RETORNO
        double score - 0 nao atingiu o alvo
                     - 0 < score <= 1 pontuacao feita
    */
    double checkColision(double yArrow);

    /*
    Retorna o valor do hp do alvo
    @RETORNO
        double hp - valor do hp do alvo
    */
    double getHP();

    /*
    Retorna se o alvo esta morto ou nao, se estiver
    sua vida sera setada para o valor inicial
    @RETORNO
        bool - se o alvo esta morto
    */
    bool isDead();
    
    /*
    Retorna o valor da coordenada x do alvo
    @RETORNO
        double x - valor da coordenada x do alvo
    */
    double getX();
    
    /*
    Retorna o valor da coordenada y do alvo
    @RETORNO
        double y - valor da coordenada y do alvo
    */
    double getY();

    /*
    Seta o valor de x, com base no parametro passado
    @RETORNO
        double x - valor a qual o atributo x seta setado.
    */
    void setX(double x);

    /*
    Seta o valor de y, com base no parametro passado
    @RETORNO
        double y - valor a qual o atributo y seta setado.
    */
    void setY(double y);    
};

#endif
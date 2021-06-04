#ifndef ARROW_H
#define ARROW_H

#include "Object.h"
#include "Target.h"
#include "Obstacle.h"
#include <math.h>

class Arrow : private Object
{

private:
    Target* targetLocal;
    Obstacle* obstacle;
    double velocityX;
    double velocityY;
    double time;
    double initX;
    double initY;
    double xColision;
    double gravity;
    double score;
    bool status;

public:
    /*
    Construtor da classe arrow
    @PARAMETROS
        coordenadas* coord  - endereco do vetor com os vertices para serem envidos a GPU
        int vertice_inicial - posicao do vertice inical no vetor de vertices
        int num_vertices    - numero de vertices da figura
        double x            - posicao no eixo x da flecha
        double y            - posicao no eixo y da flecha
        double tx           - translacao em x
        double ty           - translacao em y
        double s            - escala da flecha
        double theta        - algulo de lancamento da flecha
        double velocity     - velocidade inical da flecha
        double gravity      - velocidade da gravidade sobre a flecha
        Target* targetLocal - referencia para o alvo
        Obstacle* obstacle  - referencia para o obstaculo
    OBS: alterar os parametro de translacao e escala nao alteram as propriedades da flecha na simulacao
         somente de forma visual.
    */
    Arrow(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, double velocity, double gravity, Target* targetLocal, Obstacle* obstacle);
    
    ~Arrow();
    
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
    Dado um tempo, a funcao arruma a posicao da flecha para e passdos esse tempo
    na animacao 
    @PARAMETROS
        double time - tempo para a flecha avancar na animacao
    */
    void Move(double time);
    
    /*
    Atualiza a flecha para uma nova flecha, tambem reinicia os valores de sua animacao
    @RETORNO
        double theta    - valor do angulo da nova flecha
        double velocity - valor da velocidada inicial da nova flecha
    */
    void Update(double theta, double velocity);

    /*
    Retorna o status da flecha na animacao, se ela colidiu ou nao 
    @RETORNO
        bool status -
                        true - se colidiu
                        false - se nao colidiu
    */
    bool GetStatus();

    /*
    O valor da pontuacao feita pela flecha 
    @RETORNO
        double score - pontuacao feita pela flecha
    */
    double GetScore();
    
    /*
    O valor do x duratande a colicao da flecha
    @RETORNO
        double x - coordenada x da colisao
    */
    double GetXColision();
};


#endif
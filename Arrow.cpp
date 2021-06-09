#include "Arrow.h"

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
Arrow::Arrow(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, const double velocity, double gravity, Target* targetLocal, Obstacle* obstacle) : Object(vertice_inicial, num_vertices, x, y, tx, ty, s, theta)
{
    this->initX = tx;
    this->initY = ty;
    this->targetLocal = targetLocal;
    this->obstacle = obstacle;
    this->gravity = gravity*(-1);
    this->xColision = 1;
    this->velocityX = velocity*cos(theta);
    this->velocityY = velocity*sin(theta);
    this->status = false;    
    this->time = 0;

    // calcula a colisao com o obstaculo
    double xObstacle = obstacle->getX();
    double timeColisionObstacle = ((xObstacle-this->initX)/velocityX);
    double yObstacle = this->initY+(this->velocityY*timeColisionObstacle)+((this->gravity*(timeColisionObstacle*timeColisionObstacle))/2);
    int hit = this->obstacle->checkColision(yObstacle);
    
    if(hit){
        this->xColision = xObstacle;
        this->score = 0;
        
    }
    
    // caso nao tenha colidido com o obstaculo calcula a colisao com o alvo
    else
    {
        double xTarget = targetLocal->getX();
        double timeColisionTarget = ((xTarget-this->initX)/velocityX);
        double yTarget = this->initY+(this->velocityY*timeColisionTarget)+((this->gravity*(timeColisionTarget*timeColisionTarget))/2);
        this->score = this->targetLocal->checkColision(yTarget);
        
        if (this->score > 0)
        {
            this->xColision = xTarget;
        }
    }

    // adiciona os pontos ao vetor
    int atual = this->vertice_inicial;

    //Ponta
    vertices[atual].x = 0.00f;
    vertices[atual].y = 0.00f;
    atual++;

    vertices[atual].x = -0.20f;
    vertices[atual].y = 0.06f;
    atual++;

    vertices[atual].x = -0.20f;
    vertices[atual].y = -0.06f;
    atual++;

    //Corpo
    vertices[atual].x = -0.50f;
    vertices[atual].y = 0.010f;
    atual++;

    vertices[atual].x = -0.20f;
    vertices[atual].y = 0.010f;
    atual++;

    vertices[atual].x = -0.50f;
    vertices[atual].y = -0.010f;
    atual++;

    vertices[atual].x = -0.20f;
    vertices[atual].y = -0.010f;
    atual++;

    //Rabiola
    vertices[atual].x = -0.55f;
    vertices[atual].y = 0.00f;
    atual++;

    vertices[atual].x = -0.60f;
    vertices[atual].y = 0.04f;
    atual++;

    vertices[atual].x = -0.50f;
    vertices[atual].y = 0.04f;
    atual++;

    vertices[atual].x = -0.45f;
    vertices[atual].y = 0.01f;
    atual++;

    vertices[atual].x = -0.45f;
    vertices[atual].y = -0.01f;
    atual++;

    vertices[atual].x = -0.50f;
    vertices[atual].y = -0.04f;
    atual++;

    vertices[atual].x = -0.60f;
    vertices[atual].y = -0.04f;
    atual++;


    this->num_vertices = atual - this->vertice_inicial;

    return;
}

Arrow::~Arrow()
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
int Arrow::draw(GLint loc_color, GLint loc_matriz)
{   
    matriz_transformacao_objeto(loc_matriz);

    int atual = this->vertice_inicial;

    glUniform4f(loc_color, 184.0/256.0, 184.0/256.0, 184.0/256.0, 1);
    desenha_triangulo(atual);
    atual += 3;

    glUniform4f(loc_color, 158.0/256.0, 132.0/256.0, 90.0/256.0, 1);
    desenha_quadrado(atual);
    atual += 4;

    glUniform4f(loc_color, 1, 0, 0, 1);
    desenha_circulo(atual, 7);

    return 0;
}

/*
Dado um tempo, a funcao arruma a posicao da flecha para e passdos esse tempo
na animacao 
@PARAMETROS
    double time - tempo para a flecha avancar na animacao
*/
void Arrow::Move(const double time)
{
    double time_temp;
    //verifica se a flecha ja colidiu
    if (GetStatus())
    {
        this->time += time;
        return;
    }
    
    // adiciona o tempo para a flecha
    this->time += time;
    time_temp = this->time; 
    //calcula a nova posicao em x
    this->tx = this->initX+this->velocityX*this->time;
    
    //verifica se colidiu com o alvo
    if (this->tx > this->xColision)
    {
        this->tx = this->xColision;


        //calculando ty baseado no tx
        time_temp = (this->tx - this->initX)/this->velocityX;


        this->status = true;
    }

    //verifica se colidiu com o chao
    else if(this->ty <= -1)
    {
        this->ty = -1;
        this->status = true;
    }

    // calcula y
    this->ty = this->velocityY*time_temp + ((this->gravity*(time_temp*time_temp))/2) + this->initY;

    // faz o calculo do angulo da flecha no ponto
    double tangente = (this->velocityY + (this->gravity*this->tx) - (this->gravity*this->initX))/this->velocityX;
    this->theta = atan(tangente);

    return;
}

/*
Atualiza a flecha para uma nova flecha, tambem reinicia os valores de sua animacao
@RETORNO
    double theta    - valor do angulo da nova flecha
    double velocity - valor da velocidada inicial da nova flecha
*/
void Arrow::Update(double theta, double velocity){
    this->tx = this->initX;
    this->ty = this->initY;
    this->velocityX = velocity*cos(theta);
    this->velocityY = velocity*sin(theta);
    this->status = false;    
    this->time = 0;
    this->xColision = 1;
    double xObstacle = obstacle->getX();

    // calcula a colisao com o obstaculo
    double timeColisionObstacle = ((xObstacle-this->initX)/velocityX);
    double yObstacle = this->initY+(this->velocityY*timeColisionObstacle)+((this->gravity*(timeColisionObstacle*timeColisionObstacle))/2);
    int hit = this->obstacle->checkColision(yObstacle);
    
    if(hit)
    {
        this->xColision = xObstacle;
        this->score = 0;
        
    }
    
    // caso nao tenha colidido com o obstaculo calcula a colisao com o alvo
    else
    {
        double xTarget = targetLocal->getX();
        double timeColisionTarget = ((xTarget-this->initX)/velocityX);

        double yTarget = this->initY+(this->velocityY*timeColisionTarget)+((this->gravity*(timeColisionTarget*timeColisionTarget))/2);
        
        this->score = this->targetLocal->checkColision(yTarget);
        
        if (this->score > 0)
        {
            this->xColision = xTarget;
        }
    }

    return;
}

/*
Retorna o status da flecha na animacao, se ela colidiu ou nao 
@RETORNO
    bool status -
                    true - se colidiu
                    false - se nao colidiu
*/
bool Arrow::GetStatus()
{
    return this->status;
}

/*
O valor da pontuacao feita pela flecha 
@RETORNO
    double score - pontuacao feita pela flecha
*/
double Arrow::GetScore()
{
    return this->score;
}

/*
O valor do x duratande a colicao da flecha
@RETORNO
    double x - coordenada x da colisao
*/
double Arrow::GetXColision()
{
    return this->xColision;
}
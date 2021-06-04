#include "Arrow.h"
#include <iostream>

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

    double xObstacle = obstacle->getX();

    
    double timeColisionObstacle = ((xObstacle-this->initX)/velocityX);
    double yObstacle = this->initY+(this->velocityY*timeColisionObstacle)+((this->gravity*(timeColisionObstacle*timeColisionObstacle))/2);
    
    int hit = this->obstacle->checkColision(yObstacle);
    
    if(hit){
        this->xColision = xObstacle;
        this->score = 0;
        
    }else{
        /*
            verificando a colisao com o target
        */
        double xTarget = targetLocal->getX();
        double timeColisionTarget = ((xTarget-this->initX)/velocityX);

        double yTarget = this->initY+(this->velocityY*timeColisionTarget)+((this->gravity*(timeColisionTarget*timeColisionTarget))/2);
        
        this->score = this->targetLocal->checkColision(yTarget);
        
        if (this->score > 0)
        {
            this->xColision = xTarget;
        }
    }

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

void Arrow::Update(double theta, double velocity){
    this->tx = this->initX;
    this->ty = this->initY;
    this->velocityX = velocity*cos(theta);
    this->velocityY = velocity*sin(theta);
    this->status = false;    
    this->time = 0;
    this->xColision = 1;
    double xObstacle = obstacle->getX();

    
    double timeColisionObstacle = ((xObstacle-this->initX)/velocityX);
    double yObstacle = this->initY+(this->velocityY*timeColisionObstacle)+((this->gravity*(timeColisionObstacle*timeColisionObstacle))/2);
    
    int hit = this->obstacle->checkColision(yObstacle);
    
    if(hit){
        this->xColision = xObstacle;
        this->score = 0;
        
    }else{
        /*
            verificando a colisao com o target
        */
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

Arrow::~Arrow()
{
    return;
}

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

void Arrow::Move(const double time)
{
    if (GetStatus())
    {
        this->time += time;
        return;
    }
    
    this->time += time;

    this->tx = this->initX+this->velocityX*this->time;
    
    if (this->tx > this->xColision)
    {
        this->tx = this->xColision;
        this->status = true;
    }else if(this->ty <= -1){
        this->ty = -1;
        this->status = true;
    }

    this->ty = this->velocityY*this->time + ((this->gravity*(this->time*this->time))/2) + this->initY;

    double tangente = (this->velocityY + (this->gravity*this->tx) - (this->gravity*this->initX))/this->velocityX;

    this->theta = atan(tangente);
    return;
}

bool Arrow::GetStatus()
{
    return this->status;
}

double Arrow::GetScore()
{
    return this->score;
}

double Arrow::GetXColision()
{
    return this->xColision;
}
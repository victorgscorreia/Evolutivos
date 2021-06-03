#include "Arrow.h"
#include <iostream>

Arrow::Arrow(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, const double velocity, double gravity, Target* targetLocal) : Object(vertice_inicial, num_vertices, x, y, tx, ty, s, theta)
{
    this->initX = x;
    this->initY = y;
    this->velocityX = velocity*cos(theta);
    this->velocityY = velocity*sin(theta);
    this->gravity = gravity*(-1);
    this->status = false;
    this->targetLocal = targetLocal;
    this->time = 0;

    double xTarget = targetLocal->getX();
    double timeColisionTarget = ((xTarget-this->initX)/velocityX);
    double yTarget = this->initY+(this->velocityY*timeColisionTarget)+((this->gravity*(timeColisionTarget*timeColisionTarget))/2);
    //std::cout << yTarget << "\n";
    this->score = this->targetLocal->checkColision(yTarget);
    
    if (this->score > 0)
    {
        this->xColision = xTarget;
    }

    else
    {

        double delta = (this->velocityY*this->velocityY)-(2.0*this->gravity*(-1.0-this->initY));
    
        double timeColisionGround = (((this->velocityY*(-1.0))-sqrt(delta))/this->gravity);
        this->xColision = this->initX + (this->velocityX*timeColisionGround);
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
    }
    else if(this->ty <= -1){
        this->ty = -1;
        this->status = true;
    }
    else if(this->tx >= 1){
        this->tx = 1;
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

int Arrow::GetScore()
{
    return this->score;
}

double Arrow::GetXColision()
{
    return this->xColision;
}
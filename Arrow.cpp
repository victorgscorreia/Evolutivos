#include "Arrow.h"
#include <iostream>
Arrow::Arrow(int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, const double angle,const double velocity, double gravity, Target* targetLocal) : Object(vertice_inicial, num_vertices, x, y, tx, ty, s, theta)
{
    this->initX = x;
    this->initY = y;
    this->velocityX = velocity*cos(angle);
    this->velocityY = velocity*sin(angle);
    this->gravity = gravity*(-1);
    this->status = false;
    this->targetLocal = targetLocal;
    this->time = 0;

    double xTarget = targetLocal->getX();
    double timeColisionTarget = ((xTarget-this->initX)/velocityX);
    double yTarget = this->initY+(this->velocityY*timeColisionTarget)+((this->gravity*(timeColisionTarget*timeColisionTarget))/2);
    std::cout << yTarget << "\n";
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

    return;
}

Arrow::~Arrow()
{
    return;
}

int Arrow::draw()
{
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

    this->x = this->initX+this->velocityX*this->time;
    
    if (this->x > this->xColision)
    {
        this->x = this->xColision;
        this->status = true;
    }

    this->y = this->velocityY*this->time + ((this->gravity*(this->time*this->time))/2) + this->initY;


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
#include "Target.h"

Target::Target(double x, double y, double radius1, double radius2, double radius3, double radius4, int *circ1Color, int *circ2Color, int *circ3Color, int *circ4Color) : Object(x, y)
{
    this->radius1 = radius1;
    this->radius2 = radius2;
    this->radius3 = radius3;
    this->radius4 = radius4;

    for (int i = 0; i < 4; i++)
    {
        this->circ1Color[i] = circ1Color[i];
        this->circ2Color[i] = circ2Color[i]; 
        this->circ3Color[i] = circ3Color[i];
        this->circ4Color[i] = circ4Color[i];
    }
    
    return;
}

Target::~Target()
{
    return;
}

int Target::draw()
{
    return 0;
}

double Target::randPosX(unsigned int seed)
{
    return 0;
}

double Target::randPosY(unsigned int seed)
{
    return 0;
}

int Target::checkColision(double yArrow)
{

    if (yArrow <= this->y + this->radius4 && yArrow >= this->y - this->radius4)
    {
        return 4;
    }

    if (yArrow <= this->y + this->radius3 && yArrow >= this->y - this->radius3)
    {
        return 3;
    }

    if (yArrow <= this->y + this->radius2 && yArrow >= this->y - this->radius2)
    {
        return 2;
    }
    
    if (yArrow <= this->y + this->radius1 && yArrow >= this->y - this->radius1)
    {
        return 1;
    }
    
    return 0;
}

double Target::getX()
{
    return this->x;
}

double Target::getY()
{
    return this->y;
}
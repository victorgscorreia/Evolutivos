#include "Target.h"
#include <iostream>

Target::Target(coordenadas* coord, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, double radius1, double radius2, double radius3, double radius4) : Object(vertice_inicial, num_vertices, x, y, tx, ty, s, theta)
{
    this->radius1 = radius1;
    this->radius2 = radius2;
    this->radius3 = radius3;
    this->radius4 = radius4;

    int atual = this->vertice_inicial;

    add_elipse(coord, atual, 32, x, y, radius1);
    atual += 32;
    add_elipse(coord, atual, 32, x, y, radius2);
    atual += 32;
    add_elipse(coord, atual, 32, x, y, radius3);
    atual += 32;
    add_elipse(coord, atual, 32, x, y, radius4);

    return;
}

Target::~Target()
{
    return;
}

int Target::draw(GLint loc_color, GLint loc_matriz)
{   
    matriz_transformacao_objeto(loc_matriz);

    int atual = this->vertice_inicial;

    glUniform4f(loc_color, 1, 0, 0, 1);
    desenha_circulo(atual, 32);
    atual+=32;

    glUniform4f(loc_color, 1, 1, 1, 1);
    desenha_circulo(atual, 32);
    atual+=32;

    glUniform4f(loc_color, 0, 0, 1, 1);
    desenha_circulo(atual, 32);
    atual+=32;

    glUniform4f(loc_color, 1, 1, 1, 1);
    desenha_circulo(atual, 32);

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
    //std::cout << this->y + this->radius4 << std::endl;

    if (yArrow <= this->y + this->radius4 * 1.6 && yArrow >= this->y - this->radius4 * 1.6)
    {
        return 4;
    }

    if (yArrow <= this->y + this->radius3 * 1.6 && yArrow >= this->y - this->radius3 * 1.6)
    {
        return 3;
    }

    if (yArrow <= this->y + this->radius2 * 1.6 && yArrow >= this->y - this->radius2 * 1.6)
    {
        return 2;
    }
    
    if (yArrow <= this->y + this->radius1 * 1.6 && yArrow >= this->y - this->radius1 * 1.6)
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
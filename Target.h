#ifndef TARGET_H
#define TARGET_H

#include "Object.h"
#include <stdlib.h>

class Target : private Object 
{
private:
    double radius1;
    double radius2;
    double radius3;
    double radius4;
    int circ1Color[4];
    int circ2Color[4];
    int circ3Color[4];
    int circ4Color[4];

public:
    Target(coordenadas* coord, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, double radius1, double radius2, double radius3, double radius4);
    ~Target();
    int draw(GLint loc_color, GLint loc_matriz);
    double randPosX(unsigned int seed);
    double randPosY(unsigned int seed);
    int checkColision(double yArrow);
    double getX();
    double getY();
};

#endif
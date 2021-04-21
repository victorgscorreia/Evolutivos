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
    Target(double x, double y, double radius1, double radius2, double radius3, double radius4, int *circ1Color, int *circ2Color, int *circ3Color, int *circ4Color);
    ~Target();
    int draw();
    double randPosX(unsigned int seed);
    double randPosY(unsigned int seed);
    int checkColision(double yArrow);
    double getX();
    double getY();
};

#endif
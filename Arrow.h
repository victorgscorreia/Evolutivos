#ifndef ARROW_H
#define ARROW_H

#include "Object.h"
#include "Target.h"
#include <math.h>

class Arrow : private Object
{

private:
    Target* targetLocal;
    double velocityX;
    double velocityY;
    double time;
    double initX;
    double initY;
    double xColision;
    double gravity;
    int score;
    bool status;

public:
    Arrow(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, double velocity, double gravity, Target* targetLocal);
    ~Arrow();
    int draw(GLint loc_color, GLint loc_matriz);
    void Move(double time);
    bool GetStatus();
    int GetScore();
    double GetXColision();
};


#endif
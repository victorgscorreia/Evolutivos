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
    Arrow(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta, double velocity, double gravity, Target* targetLocal, Obstacle* obstacle);
    ~Arrow();
    int draw(GLint loc_color, GLint loc_matriz);
    void Move(double time);
    bool GetStatus();
    double GetScore();
    double GetXColision();
    void Update(double theta, double velocity);
};


#endif
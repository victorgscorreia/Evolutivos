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
    Arrow(double x, double y, double angle, double velocity, double gravity, Target* targetLocal);
    ~Arrow();
    int draw();
    void Move(double time);
    bool GetStatus();
    int GetScore();
    double GetXColision();
};


#endif
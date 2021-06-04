#ifndef OBS_H
#define OBS_H

#include "Object.h"

class Obstacle : private Object 
{
private:
    double min_y;
    double max_y;

public:
    Obstacle(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double min_y, double max_y, double tx, double ty, double s, double theta);
    ~Obstacle();
    int draw(GLint loc_color, GLint loc_matriz);
    int checkColision(double yArrow);
    double getX();
};

#endif
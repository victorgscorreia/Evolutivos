#ifndef OBJECT_H
#define OBJECT_H
#include "base.h"

class Object
{
public:
    
    int vertice_inicial;
    int num_vertices;
    double x;
    double y;
    double tx;
    double ty;
    double s;
    double theta;

    Object(int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta);
    ~Object();

    virtual int draw();
    void matriz_transformacao_objeto(GLint loc_matriz);
};

#endif
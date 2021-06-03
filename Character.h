#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"

class Character : private Object
{
public:
    Character(int vertice_inicial, int num_vertices, double x, double y, double tx, double ty, double s, double theta);
    ~Character();
    int draw();
};

#endif
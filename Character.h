#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"

class Character : private Object
{
public:
    Character(double x, double y);
    ~Character();
    int draw();
};

#endif
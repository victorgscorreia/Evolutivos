#ifndef OBJECT_H
#define OBJECT_H


class Object
{
public:

    double x;
    double y;

    Object(double x, double y);
    ~Object();

    virtual int draw();
};

#endif
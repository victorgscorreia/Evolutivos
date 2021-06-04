
#include "Obstacle.h"
#include <iostream>
Obstacle::Obstacle(coordenadas* vertices, int vertice_inicial, int num_vertices, double x, double min_y, double max_y, double tx, double ty, double s, double theta) : Object(vertice_inicial, num_vertices, x, 0, tx, ty, s, theta)
{

    this->min_y = min_y;
    this->max_y = max_y;


    int atual = this->vertice_inicial;

    vertices[atual].x = x - 0.005;
    vertices[atual].y = min_y;
    atual++;

    vertices[atual].x = x + 0.005;
    vertices[atual].y = min_y;
    atual++;

    vertices[atual].x = x - 0.005;
    vertices[atual].y = max_y;
    atual++;

    vertices[atual].x = x + 0.005;
    vertices[atual].y = max_y;
    atual++;

    return;
}

int Obstacle::draw(GLint loc_color, GLint loc_matriz){
    matriz_transformacao_objeto(loc_matriz);

    int atual = this->vertice_inicial;
    glUniform4f(loc_color, 0, 0, 0, 1);
    desenha_quadrado(atual);
    return 0;
}

int Obstacle::checkColision(double yArrow){
    if(this->min_y <= yArrow && yArrow <= this->max_y){
        return 1;
    }
    return 0;
}

double Obstacle::getX(){
    return this->x;
}
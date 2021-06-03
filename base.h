#ifndef BASE
#define BASE

#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
estrutura de coordenadas que sera passado para GPU.
*/
typedef struct{
    float x, y;
} coordenadas;

/*
adiciona um circulo ao nosso vetor de vertices, as coordenadas do pontos do circulo começa na posicao
vertice_inicial do nosso vetor e possui num_vertices.
@PARAMETROS
    coordenadas *vertices - o nosso vetor de vertices
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso circulo
    int num_vertices - quantidade de vertices que nosso circulo tera
    float x_ini - coordenada x do centro do nosso circulo
    float y_ini - coordenada y do centro do nosso circulo
    float radius - raio do nosso circulo
*/
void add_elipse( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius);

/*
adiciona um semi-circulo ao nosso vetor de vertices, as coordenadas do pontos do circulo começa na posicao
vertice_inicial do nosso vetor e possui num_vertices.
o semi-circulo só tem a metade de cima do circulo, ou seja os pontos que respeitam a equacao y = sqrt(radius - x^2).
Utiliza-se a funcao desenha_circulo para desenhar o semi-circulo, por necessitar de usar a mesma primitiva para desenhar.
@PARAMETROS
    coordenadas *vertices - o nosso vetor de vertices
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso circulo
    int num_vertices - quantidade de vertices que nosso circulo tera
    float x_ini - coordenada x do centro do nosso circulo
    float y_ini - coordenada y do centro do nosso circulo
    float radius - raio do nosso circulo
*/
void add_semi_circulo( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius);

/*
chama a primitiva para se denhar um circulo, passando a posicao do vetor do primeiro
ponto do circulo, e sua quantidade de pontos.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso circulo
    int num_vertices - quantidade de vertices que nosso circulo tera
*/
void desenha_circulo(int vertice_inicial, int num_vertices);

/*
chama a primitiva para se desenhar um triangulo, passando a posicao do vetor do primeiro
ponto do triangulo.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso triangulo
*/
void desenha_triangulo(int vertice_inicial);

/*
chama a primitiva para se desenhar varios triangulos, passando a posicao do vetor do
primeiro ponto do primeiro triangulo, e a quantidade de triangulos que se deseja desenhar.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do primeiro triangulo.
    int qtd_triangulos - a quantidade de triangulos que deve ser desenhado.
*/
void desenha_triangulos(int vertice_inicial, int qtd_triangulos);

/*
chama a primitiva para se desenhar um quadrado, passando a posicao do vetor do primeiro
ponto do quadrado.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso quadrado
*/
void desenha_quadrado(int vertice_inicial);

/*
chama a primitiva para se desenhar uma linha, passando a posicao do vetor do primeiro
ponto da linha.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nossa linha
*/
void desenha_linha(int vertice_inicial);


/*
Faz a multiplicao de duas matrizes 4x4 e retorna o seu resultado
@PARAMETROS
    float* matrix1 - vetor representando de tamanho 16 representando uma matrix 4x4
    float* matrix2 - vetor representando de tamanho 16 representando uma matrix 4x4
    float* matrix_resultante - onde sera guardado a matriz resultando da multiplicacao matrix1*matrix2
*/
void mult_matrix(float* matrix1, float* matrix2, float* matrix_result);

#endif
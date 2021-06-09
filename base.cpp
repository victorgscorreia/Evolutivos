#include "base.h"

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
void add_elipse( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius){
    float pi = 3.14;
    float counter = 0;
    float angle = 0.0;
    float x, y;
    for(int i=0; i < num_vertices; i++){
	    angle += (2.0*pi)/num_vertices;
	    x = cos(angle)*radius + x_ini;
	    y = sin(angle)*radius*1.6 + y_ini;
	    vertices[i + vertice_inicial].x = x;
	    vertices[i + vertice_inicial].y = y;
    }
}

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
void add_semi_circulo( coordenadas*vertices , int vertice_inicial, int num_vertices, float x_ini, float y_ini, float radius){
    
    vertices[vertice_inicial].x = x_ini + radius;
    vertices[vertice_inicial].y = y_ini;

    vertice_inicial++;
    num_vertices--;

    float pi = M_PI;
    float angle = 0.0;
    float x, y;
    
    for(int i=0; i < num_vertices; i++){
	    angle += (1.0*pi)/num_vertices;
        x = cos(angle)*radius + x_ini;
        y = sin(angle)*radius + y_ini;
        vertices[i + vertice_inicial].x = x;
        vertices[i + vertice_inicial].y = y;
    }
}

/*
chama a primitiva para se denhar um circulo, passando a posicao do vetor do primeiro
ponto do circulo, e sua quantidade de pontos.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso circulo
    int num_vertices - quantidade de vertices que nosso circulo tera
*/
void desenha_circulo(int vertice_inicial, int num_vertices){
    glDrawArrays(GL_TRIANGLE_FAN, vertice_inicial, num_vertices);
}

/*
chama a primitiva para se desenhar um triangulo, passando a posicao do vetor do primeiro
ponto do triangulo.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso triangulo
*/
void desenha_triangulo(int vertice_inicial){
    glDrawArrays(GL_TRIANGLES, vertice_inicial, 3);
}

/*
chama a primitiva para se desenhar varios triangulos, passando a posicao do vetor do
primeiro ponto do primeiro triangulo, e a quantidade de triangulos que se deseja desenhar.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do primeiro triangulo.
    int qtd_triangulos - a quantidade de triangulos que deve ser desenhado.
*/
void desenha_triangulos(int vertice_inicial, int qtd_triangulos){
    glDrawArrays(GL_TRIANGLES, vertice_inicial, qtd_triangulos*3);
}

/*
chama a primitiva para se desenhar um quadrado, passando a posicao do vetor do primeiro
ponto do quadrado.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nosso quadrado
*/
void desenha_quadrado(int vertice_inicial){
    glDrawArrays(GL_TRIANGLE_STRIP, vertice_inicial, 4);
}

/*
chama a primitiva para se desenhar uma linha, passando a posicao do vetor do primeiro
ponto da linha.
@PARAMETROS
    int vertice_inicial - a posicao do vetor que tera o primeiro ponto do nossa linha
*/
void desenha_linha(int vertice_inicial){
    glDrawArrays(GL_LINES, vertice_inicial, 2);
}


/*
Faz a multiplicao de duas matrizes 4x4 e retorna o seu resultado
@PARAMETROS
    float* matrix1 - vetor representando de tamanho 16 representando uma matrix 4x4
    float* matrix2 - vetor representando de tamanho 16 representando uma matrix 4x4
    float* matrix_resultante - onde sera guardado a matriz resultando da multiplicacao matrix1*matrix2
*/
void mult_matrix(float* matrix1, float* matrix2, float* matrix_result)
{
    float matrix_temp[16];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
            {
                sum += matrix1[4*i+k] * matrix2[4*k+j];
            }
            matrix_temp[4*i+j] = sum;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix_result[4*i+j] = matrix_temp[4*i+j];
        }
    }

    return;
}

/*
Esta funcao retorna um double randomico entre [0,1]
@RETORNO
    double - double gerado
*/
double rand_double(){
    double ret = (1.0*rand())/(1.0*RAND_MAX);
    return ret;
}
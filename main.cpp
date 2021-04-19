#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>

using namespace std;

#define windowWidth 800
#define windowHeight 800

float new_x = 0;
float new_y = 0;

typedef struct _circle{
  float radius;
  float x;
  float y;
  float theta;
  float r,g,b;
}Circle;

typedef struct _target{
  Circle t1, t2, t3, t4;
  bool hit;
}Target;

Target t = {{0.07,new_x,new_y,0,1,0,0}, {0.05,new_x,new_y,0,1,1,1}, {0.03,new_x,new_y,0,0,0,1}, {0.01,new_x,new_y,0,1,1,1}, false};

void drawCircle(Circle circle){
  
  float radius = circle.radius;
  float x = circle.x;
  float y = circle.y;

  glColor3f(circle.r, circle.g, circle.b);

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=1) {
    glVertex2d( radius*1*sin(i) + y, radius*1.6*cos(i) + x);
  }
  glEnd();

}

void drawTarget(Target t){
    drawCircle(t.t1);
    drawCircle(t.t2);
    drawCircle(t.t3);
    drawCircle(t.t4);
}

void draw(){
  glClear(GL_COLOR_BUFFER_BIT);

  t.t1 = {0.07,new_x,new_y,0,1,0,0};
  t.t2 = {0.05,new_x,new_y,0,1,1,1};
  t.t3 = {0.03,new_x,new_y,0,0,0,1};
  t.t4 = {0.01,new_x,new_y,0,1,1,1};

  drawTarget(t);

  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1.0);

    new_x = -0.9 + (rand()%180)/100.0f;
    new_y = (rand()%90)/100.0f;

    draw();

  }
}

void changeTarget(){
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1, 1, 1, 1.0);

  new_x = -0.9 + (rand()%180)/100.0f;
  new_y = (rand()%90)/100.0f;

  draw();
}

void moveTarget(Target *target, float distance){
  
  target->t1.x = target->t1.x + distance;
  target->t1.y = target->t1.y + distance;
  target->t2.x = target->t2.x + distance;
  target->t2.y = target->t2.y + distance;
  target->t3.x = target->t3.x + distance;
  target->t3.y = target->t3.y + distance;
  target->t4.x = target->t4.x + distance;
  target->t4.y = target->t4.y + distance;

  target->t1.x = target->t1.x>1 ? -1 : target->t1.x;
  target->t1.y = target->t1.y>1 ? -1 : target->t1.y;
  target->t2.x = target->t2.x>1 ? -1 : target->t2.x;
  target->t2.y = target->t2.y>1 ? -1 : target->t2.y;
  target->t3.x = target->t3.x>1 ? -1 : target->t3.x;
  target->t3.y = target->t3.y>1 ? -1 : target->t3.y;
  target->t4.x = target->t4.x>1 ? -1 : target->t4.x;
  target->t4.y = target->t4.y>1 ? -1 : target->t4.y;
}

void hitTarget(){
  t.hit = rand()%2;
}

void drawArrow(){

}

//------------------ Timer -----------------//
void timer(int){
  // Essa função é chamada em loop, é aqui que realizaremos as animações

  // Tenta ficar mudando os parâmetros para ver o que muda! :)

  //hitTarget();

  if(t.hit == true){
    changeTarget();
  }
  //moveTarget(&t, 0.005);

  // Executa a função draw para desenhar novamente
  //glutPostRedisplay();

  // O primeiro parâmetro define de quanto em quanto tempo em milissegundos timer será chaamdo
  // Eu coloquei 1000/60 para definir que vai atualizar a 60hz
  glutTimerFunc(1000/60, timer, 0);// Garante que esta função será chamada de novo
}

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Teste");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(draw);
    glutTimerFunc(0, timer, 0); // Define qual será a função de loop
    glutMouseFunc(mouse);
    
    
    
    glutMainLoop();

    return 0;
}
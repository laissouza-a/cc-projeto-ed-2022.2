#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

void display()
{ 

  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINES);
  
  //linha 1
  glVertex2i(400, 600);
  glVertex2i(400, 800);
  //linha 2
  glVertex2i(600, 600);
  glVertex2i(600, 800);
  //linha 3
  glVertex2i(400, 800);
  glVertex2i(500, 900);
  //linha 4
  glVertex2i(500, 900);
  glVertex2i(600, 800);
  //linha 5
  glVertex2i(400, 600);
  glVertex2i(500, 500);
  //linha 6
  glVertex2i(600, 600);
  glVertex2i(500, 500);

  glEnd();
  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(1200, 840);
  //glutInitWindowPosition(100, 100);
  glutCreateWindow("Planta baixa de casa");
  gluOrtho2D(0.0, 1200.0, 0.0, 1200.0);
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}
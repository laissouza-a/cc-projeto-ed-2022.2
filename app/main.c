#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct hexa {
  int x, y;
  struct hexa *next;
} hexa;

hexa *add_vertex (int x, int y, hexa *h)
{
  hexa *new_vertex = (hexa *) malloc(sizeof(hexa));

  if (new_vertex == NULL)
  {
    printf("Falta de memória no dispositivo\n");
    exit(1);
  }

  new_vertex->x = x;
  new_vertex->y = y;

  if (h == NULL)
  {
    return new_vertex;
  }
  else
  {
    hexa *aux = h;

    while (aux->next != NULL)
      aux = aux->next;
    
    aux->next = new_vertex;

    return h;
  }
}

hexa *create_hexa_for_area (int area, int pos)
{
  hexa *h = NULL;

  if (pos == 1)
  {
    int x0 = 400, x1 = 400, x2 = 400, x3 = 400, x4 = 400, x5 = 400;
    int y0 = 400 + (area/1000), y1 = 400, y2 = 400, y3 = 400 - (area/1000), y4 = 400, y5 = 400;

    int d1 = ((x1*y2 + x2*y3 + x2*y4 + x4*y1) - (x1*y2 + x3*y2 + x4*y3 + x1*y4));
    int d2 = ((x0*y1 + x1*y5 + x5*y0) - (x1*y0 + x5*y1 + x0*y5));
    int d3 = ((x3*y2 + x2*y4 + x4*y3) - (x2*y3 + x4*y2 + x3*y4));

    int i = 0;

    while (1)
    {
      if (i % 2 == 0)
      {
        y1 += 1;
        y2 -= 1;
        y5 += 1;
        y4 -= 1;
        y0 += 1;
      }
      else if (i % 2 == 1)
      {
        x1 += 1;
        x2 += 1;
        x4 -= 1;
        x5 -= 1;
        y3 -= 1;
      }

      int aux = ((x1*y2 + x2*y4 + x4*y5 + x5*y1) - (x2*y1 + x4*y2 + x5*y4 + x1*y5)) / 2;
      d3 = ((x3*y2 + x2*y4 + x4*y3) - (x2*y3 + x4*y2 + x3*y4)) / 2;
      d2 = ((x0*y1 + x1*y5 + x5*y0) - (x1*y0 + x5*y1 + x0*y5)) / 2;

      if (d2 < 0)
        d2 *= (-1);

      if (d3 < 0)
        d3 *= (-1);

      if (aux < 0)
        aux *= (-1);

      if ( aux + d2 + d3 >= area)
      {
          break;
      }
      else
      {
        d1 = aux;
      }
      

     // printf("d1 = %d\n", d1);
  
      i += 1;
    }
    
      printf("d1 = %d, d2 = %d, d3 = %d, soma = %d, area = %d\n", d1, d2, d3, d1+d2+d3, area);
      printf("(x0, y0) = (%d,%d)\n", x0, y0);
      printf("(x1, y1) = (%d,%d)\n", x1, y1);
      printf("(x2, y2) = (%d,%d)\n", x2, y2);
      printf("(x3, y3) = (%d,%d)\n", x3, y3);
      printf("(x4, y4) = (%d,%d)\n", x4, y4);
      printf("(x5, y5) = (%d,%d)\n", x5, y5);

      /*
      d2 = ((x0*y1 + x1*y5 + x5*y0) - (x1*y0 + x5*y1 + x0*y5));
      
      if (d2 < 0)
        d2 *= (-1);
      
      d3 = ((x3*y2 + x2*y4 + x4*y3) - (x2*y3 + x4*y2 + x3*y4));

      if (d3 < 0)
        d3 *= (-1);
      */

      h = add_vertex(x0, y0, h);
      h = add_vertex(x1, y1, h);
      h = add_vertex(x2, y2, h);
      h = add_vertex(x3, y3, h);
      h = add_vertex(x4, y4, h);
      h = add_vertex(x5, y5, h);

      return h;

    printf("test\n");
  }
  else if (pos == 2)
  {
    printf("test\n");
  }
  else if (pos == 3)
  {
    printf("test\n");
  }
  else if (pos == 4)
  {
    printf("test\n");
  }

  return h;
}

void display()
{ 
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINES);

  //linha 1
  //glVertex2i(400, 600);
  //glVertex2i(400, 800);
  //linha 2
  glVertex2i(400, 20);
  glVertex2i(400, 800);
  glVertex2i(10, 400);
  glVertex2i(800, 400);
  /*linha 3
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
  */

  glEnd();
  glFlush();
}

int main(int argc, char **argv)
{
  int area;

  while (1)
  {
    printf("Digite a area da casa (area >= 50000 || area <= 200000): ");
    scanf("%d", &area);
    
    if(area >= 50000 && area <= 2000000)
    {
      break;
    }

    printf("Valor da area nao esta no intervalo.\n\n");
  }

  hexa *h = create_hexa_for_area(area, 1);
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(820, 820);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Planta baixa de casa");
  gluOrtho2D(0.0, 820.0, 0.0, 820.0);
  //glutDisplayFunc(display);

  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINES);

  //linha 1
  //glVertex2i(400, 600);
  //glVertex2i(400, 800);
  //linha 2
  glVertex2i(400, 20);
  glVertex2i(400, 800);
  glVertex2i(20, 400);
  glVertex2i(800, 400);
  /*linha 3
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
  */

  hexa *aux = h;

  while (aux != NULL)
  {
    if (aux->next == NULL)
    {
      glVertex2i(aux->x, aux->y);
      glVertex2i(h->x, h->y);
    }
    else
    {
      glVertex2i(aux->x, aux->y);
      glVertex2i(aux->next->x, aux->next->y);
    }

    aux = aux->next;
  }
  

  glEnd();
  glFlush();

  glutMainLoop();

  return 0;
}
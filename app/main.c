#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
  int x, y;
  struct list *next;
} list;

list *add_vertex (int x, int y, list *head)
{
  list *new_vertex = (list *) malloc(sizeof(list));

  if (new_vertex == NULL)
  {
    printf("Falta de memória no dispositivo\n");
    exit(1);
  }

  new_vertex->x = x;
  new_vertex->y = y;
  new_vertex->next = NULL;
  
  if (head == NULL)
  {
    return new_vertex;
  }
  else
  {
    list *aux = head;

    while (aux->next != NULL)
      aux = aux->next;
    
    aux->next = new_vertex;

    return head;
  }
}



list *build_hexa_for_area (int area, int pos)
{
  list *head = NULL;

  if (pos == 1)
  {
    int x0 = 450, x1 = 450, x2 = 450, x3 = 450, x4 = 450, x5 = 450;
    int y0 = 450 + (area/1500), y1 = 450, y2 = 450, y3 = 450 - (area/1500), y4 = 450, y5 = 450;

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

      i += 1;
    }
    
      printf("d1 = %d, d2 = %d, d3 = %d, soma = %d, area = %d\n", d1, d2, d3, d1+d2+d3, area);
      printf("(x0, y0) = (%d,%d)\n", x0, y0);
      printf("(x1, y1) = (%d,%d)\n", x1, y1);
      printf("(x2, y2) = (%d,%d)\n", x2, y2);
      printf("(x3, y3) = (%d,%d)\n", x3, y3);
      printf("(x4, y4) = (%d,%d)\n", x4, y4);
      printf("(x5, y5) = (%d,%d)\n", x5, y5);

      head = add_vertex(x0, y0, head);
      head = add_vertex(x1, y1, head);
      head = add_vertex(x2, y2, head);
      head = add_vertex(x3, y3, head);
      head = add_vertex(x4, y4, head);
      head = add_vertex(x5, y5, head);
      head = add_vertex(x0, y0, head);

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

  return head;
}

list *build_bedroom_with_bathroom (int x0, int y0, int area)
{
  list *head = NULL;

  int x1 = x0, x2 = x0, x3 = x0;
  int y1 = y0, y2 = y0, y3 = y0;
  
  int area_bedroom = (x0*y1 + x1*y2 + x2*y3 + x3*y0) - (x1*y0 + x2*y1 + x3*y2 + x0*y3);

  printf("area = %d\n", area);

  while (area_bedroom < area)
  {
    y1 -= 1;
    x3 -= 1;
    x2 -= 1;
    y2 -= 1;

    area_bedroom = (x0*y1 + x1*y2 + x2*y3 + x3*y0) - (x1*y0 + x2*y1 + x3*y2 + x0*y3);

    if (area_bedroom < 0)
      area_bedroom *= (-1); 
  }
  
  printf("area = %d\n", area_bedroom);
  printf("\nquarto\n\n");
  printf("(x0, y0) = (%d,%d)\n", x0, y0);
  printf("(x1, y1) = (%d,%d)\n", x1, y1);
  printf("(x2, y2) = (%d,%d)\n", x2, y2);
  printf("(x3, y3) = (%d,%d)\n", x3, y3);

  head = add_vertex(x0, y0, head);
  head = add_vertex(x1, y1, head);
  head = add_vertex(x2, y2, head);
  head = add_vertex(x3, y3, head);
  head = add_vertex(x0, y0, head);
 
  return head;
}

list *build_gym_room (int x0, int x1, int y0, int area)
{
  list *head = NULL;

  int x2 = x1, x3 = x0;
  int y1 = y0, y2 = y0, y3 = y0;
  
  int area_gym_room = (x0*(y1 + y0)+ x1*(y2 + y3)) - (x1*(y1 + y0)+ x0*(y2 + y3));

  while (area_gym_room < area)
  {
    y2 -= 1;
    y3 -= 1;
    
    area_gym_room = (x0*(y1 + y0) + x1*(y2 + y3)) - (x1*(y1 + y0)+ x0*(y2 + y3));

    if (area_gym_room < 0)
      area_gym_room *= (-1); 
    
  }
  
  printf("area = %d\n", area_gym_room);
  printf("\nsala de ginastica\n\n");
  printf("(x0, y0) = (%d,%d)\n", x0, y0);
  printf("(x1, y1) = (%d,%d)\n", x1, y1);
  printf("(x2, y2) = (%d,%d)\n", x2, y2);
  printf("(x3, y3) = (%d,%d)\n", x3, y3);

  head = add_vertex(x0, y0, head);
  head = add_vertex(x1, y1, head);
  head = add_vertex(x2, y2, head);
  head = add_vertex(x3, y3, head);
  head = add_vertex(x0, y0, head);
 
  return head;
}

list *build_room (int x0, int y0, int area)
{
   list *head = NULL;

  int x1 = x0, x2 = x0, x3 = x0;
  int y1 = y0, y2 = y0, y3 = y0;
  
  int area_room = (x0*y1 + x1*y2 + x2*y3 + x3*y0) - (x1*y0 + x2*y1 + x3*y2 + x0*y3);

  while (area_room < area)
  {
    y1 += 1;
    y2 += 1;
    x2 += 1;
    x3 += 1;
    
    area_room = (x0*y1 + x1*y2 + x2*y3 + x3*y0) - (x1*y0 + x2*y1 + x3*y2 + x0*y3);

    if (area_room < 0)
      area_room *= (-1); 
    
  }
  
  printf("area = %d\n", area_room);
  printf("\nsala de estar\n\n");
  printf("(x0, y0) = (%d,%d)\n", x0, y0);
  printf("(x1, y1) = (%d,%d)\n", x1, y1);
  printf("(x2, y2) = (%d,%d)\n", x2, y2);
  printf("(x3, y3) = (%d,%d)\n", x3, y3);

  head = add_vertex(x0, y0, head);
  head = add_vertex(x1, y1, head);
  head = add_vertex(x2, y2, head);
  head = add_vertex(x3, y3, head);
  head = add_vertex(x0, y0, head);
 
  return head;
}

list *build_dining_room (int x0, int y0, int area)
{
   list *head = NULL;

  int x1 = x0, x2 = x0, x3 = x0;
  int y1 = y0, y2 = y0, y3 = y0;
  
  int dining_room = (x0*y1 + x1*y2 + x2*y3 + x3*y0) - (x1*y0 + x2*y1 + x3*y2 + x0*y3);

  while (dining_room < area)
  {
    x1 -= 1;
    y2 += 1;
    x2 -= 1;
    y3 += 1;
    
    dining_room = (x0*y1 + x1*y2 + x2*y3 + x3*y0) - (x1*y0 + x2*y1 + x3*y2 + x0*y3);

    if (dining_room < 0)
      dining_room *= (-1); 
    
  }
  
  printf("area = %d\n", dining_room);
  printf("\nsala de jantar\n\n");
  printf("(x0, y0) = (%d,%d)\n", x0, y0);
  printf("(x1, y1) = (%d,%d)\n", x1, y1);
  printf("(x2, y2) = (%d,%d)\n", x2, y2);
  printf("(x3, y3) = (%d,%d)\n", x3, y3);

  head = add_vertex(x0, y0, head);
  head = add_vertex(x1, y1, head);
  head = add_vertex(x2, y2, head);
  head = add_vertex(x3, y3, head);
  head = add_vertex(x0, y0, head);
 
  return head;
}

list *build_kitchen (int x0, int y0, int area)
{
   list *head = NULL;

  int x1 = x0, x2 = x0, x3 = x0;
  int y1 = y0, y2 = y0, y3 = y0;
  
  int area_kitchen = (x0*y1 + x1*y2 + x2*y3 + x3*y0) - (x1*y0 + x2*y1 + x3*y2 + x0*y3);

  while (area_kitchen < area)
  {
    x1 -= 1;
    y2 += 1;
    x2 -= 1;
    y3 += 1;
    
    area_kitchen = (x0*y1 + x1*y2 + x2*y3 + x3*y0) - (x1*y0 + x2*y1 + x3*y2 + x0*y3);

    if (area_kitchen < 0)
      area_kitchen *= (-1); 
    
  }
  
  printf("area = %d\n", area_kitchen);
  printf("\ncozinha\n\n");
  printf("(x0, y0) = (%d,%d)\n", x0, y0);
  printf("(x1, y1) = (%d,%d)\n", x1, y1);
  printf("(x2, y2) = (%d,%d)\n", x2, y2);
  printf("(x3, y3) = (%d,%d)\n", x3, y3);

  head = add_vertex(x0, y0, head);
  head = add_vertex(x1, y1, head);
  head = add_vertex(x2, y2, head);
  head = add_vertex(x3, y3, head);
  head = add_vertex(x0, y0, head);
 
  return head;
}

void display()
{ 
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINES);

  glEnd();
  glFlush();
}

int main(int argc, char **argv)
{
  int area;

  while (1)
  {
    printf("Digite a area da casa (area >= 135000 && area <= 255000): ");
    scanf("%d", &area);
    
    if(area >= 130000 && area <= 255000)
      break;

    printf("Valor da area nao esta no intervalo.\n\n");
  }

  list *hexa = build_hexa_for_area(area, 1);
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(920, 920);
  glutInitWindowPosition(100, 0);
  glutCreateWindow("Planta baixa de casa");
  gluOrtho2D(0.0, 920.0, 0.0, 920.0);
  //glutDisplayFunc(display);

  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINE_STRIP);

  list *aux = hexa;
  list *room = NULL;
  list *kitchen = NULL;

  int i = 0;

  while (aux != NULL)
  {
    glVertex2i(aux->x, aux->y);
    
    if (i == 2)
      kitchen = aux;

    if (i == 4)
      room = aux;

    i += 1;
    aux = aux->next;
  }
  
  list *q1 = build_bedroom_with_bathroom (hexa->next->x, hexa->next->y, 15000);
  list *prev = NULL;
  list *v1 = q1->next;
  
  while (q1 != NULL)
  {
    glVertex2i(q1->x, q1->y);
    
    if (q1->next != NULL)
    {
      prev = q1;
    }
    
    q1 = q1->next;
  }
  

  list *q2 = build_bedroom_with_bathroom (prev->x, prev->y, 15000);

  while (q2 != NULL)
  {
    if (q2->next != NULL)
    {
      prev = q2;
    }

    glVertex2i(q2->x, q2->y);
    q2 = q2->next;
  }

  list *q3 = build_bedroom_with_bathroom (prev->x, prev->y, 15000);
  list *v2 = q3->next;

  while (q3 != NULL)
  {
    if (q3->next != NULL)
    {
      prev = q3;
    }

    glVertex2i(q3->x, q3->y);
    q3 = q3->next;
  }

  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);

  list *gym_room = build_gym_room (v1->x, v2->x, v1->y, 20000);

  while (gym_room != NULL)
  {
    if (gym_room->next != NULL)
    {
      prev = gym_room;
    }

    glVertex2i(gym_room->x, gym_room->y);
    gym_room = gym_room->next;
  }

  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);

  room = build_room (room->x, room->y, 30000);

  while (room != NULL)
  {
    glVertex2i(room->x, room->y);
    room = room->next;
  }

  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);

  kitchen = build_kitchen (kitchen->x, kitchen->y, 10000);
  list *dining_room = NULL;
  i = 0;

  while (kitchen != NULL)
  {
    glVertex2i(kitchen->x, kitchen->y);

    if (i == 3)
      dining_room = kitchen;


    i += 1;
    kitchen = kitchen->next;
  }

  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);

  dining_room = build_dining_room (dining_room->x, dining_room->y, 15000);

  while (dining_room != NULL)
  {
    glVertex2i(dining_room->x, dining_room->y);
    dining_room = dining_room->next;
  }

  glEnd();
  glFlush();

  glutMainLoop();

  return 0;
}
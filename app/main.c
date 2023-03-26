#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_WINDOW 1000.0

typedef struct list {
  int x, y;
  struct list *next;
} list;

typedef struct living_room
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
} living_room;

typedef struct bathroom
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
} bathroom;

typedef struct closet
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
} closet;

typedef struct gym_room
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
} gym_room;

typedef struct service_area
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
} service_area;

typedef struct bedroom_with_bathroom
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
  bathroom *bathroom;
} bedroom_with_bathroom;

typedef struct bedroom_with_closet
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
  closet *closet;
} bedroom_with_closet;

typedef struct kitchen
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
} kitchen;

typedef struct dining_room_with_kitchen
{
  int window_x, window_y;
  int door_x, door_y;
  list *list_vertex;
  kitchen *kitchen;
} dining_room_with_kitchen;


typedef struct house {
  bedroom_with_bathroom *bedroom1;
  bedroom_with_bathroom *bedroom2;
  bedroom_with_closet *bedroom;
  bathroom *social_bathroom;
  dining_room_with_kitchen *dining_room_with_kitchen;
  service_area *service_area;
  gym_room *gym_room;
  living_room *living_room;
  list *area;
} house;

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

void print_lines_vertices (list *head)
{
  glBegin(GL_LINE_STRIP);

  while (head != NULL)
  {
    glVertex2i(head->x, head->y);
    head = head->next;
  }

  glEnd();
  glFlush();
}

int area_with_matrix (int matrix[][2], int size)
{
  int area = 0;

  for (int i = 0; i < size; i++)
  {
    if (i + 1 == size)
    {
      area += matrix[i][0]*matrix[0][1];
    }
    else
    {
      area += matrix[i][0]*matrix[i+1][1];
    }
  }
  
  for (int i = 0; i < size; i++)
  {
    if (i + 1 == size)
    {
      area -= matrix[0][0]*matrix[i][1];
    }
    else
    {
      area -= matrix[i+1][0]*matrix[i][1];
    }
  }

  if (area < 0)
    area *= (-1);

  area /= 2;


  return area;
}

int search_of_area_size (int matrix[][2], int sum_matrix[][2], int size, int area)
{

  int area_cal = area_with_matrix(matrix, size);

  while (area_cal < area)
  {
    for (int i = 0; i < size; i++)
    {
        matrix[i][0] += sum_matrix[i][0];
        matrix[i][1] += sum_matrix[i][1];
    }
    
    area_cal = area_with_matrix(matrix, size);
  }
  
  return area_cal;
}

list *build_area_house (int matrix[][2], int sum_matrix[][2], int area)
{
  list *l = (list *) malloc(sizeof(list));

  if (l == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  l = NULL;

  int area_end = search_of_area_size(matrix, sum_matrix, 6, area);

  for (int i = 0; i < 6; i++)
  {
    l = add_vertex(matrix[i][0], matrix[i][1], l);
    
    if (i + 1 == 6)
      l = add_vertex(matrix[0][0], matrix[0][1], l);
  }

  return l;
}

gym_room *build_gym_room (int matrix[][2], int sum_matrix[][2], int area)
{
  gym_room *g = (gym_room *) malloc(sizeof(gym_room));

  if (g == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  g->list_vertex = NULL;

  if (area > 30000)
    area = 30000;
  
  if (area < 20000)
    area = 20000;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);
  
  for (int i = 0; i < 4; i++)
  {
    g->list_vertex = add_vertex(matrix[i][0], matrix[i][1], g->list_vertex);
    
    if (i + 1 == 4)
      g->list_vertex = add_vertex(matrix[0][0], matrix[0][1], g->list_vertex);
  }

  return g;
}

service_area *build_service_area (int matrix[][2], int sum_matrix[][2], int area)
{

  service_area *s = (service_area *) malloc(sizeof(service_area));

  if (s == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  s->list_vertex = NULL;
  
  if (area > 10000)
    area = 10000;
  
  if (area < 6000)
    area = 6000;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  for (int i = 0; i < 4; i++)
  {
    s->list_vertex = add_vertex(matrix[i][0], matrix[i][1], s->list_vertex);
    
    if (i + 1 == 4)
      s->list_vertex = add_vertex(matrix[0][0], matrix[0][1], s->list_vertex);
  }

  return s;
}

kitchen *build_kitchen (int matrix[][2], int sum_matrix[][2], int area)
{
  kitchen *k = (kitchen *) malloc(sizeof(kitchen));

  if (k == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  k->list_vertex = NULL;

  if (area < 10000)
    area = 10000;

  if (area > 15000)
    area = 15000;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  for (int i = 0; i < 4; i++)
  {
    k->list_vertex = add_vertex(matrix[i][0], matrix[i][1], k->list_vertex);
    
    if (i + 1 == 4)
      k->list_vertex = add_vertex(matrix[0][0], matrix[0][1], k->list_vertex);
  }

  return k;
}

living_room *build_living_room (int matrix[][2], int sum_matrix[][2], int area)
{
  living_room *r = (living_room *) malloc(sizeof(living_room));

  if (r == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  r->list_vertex = NULL;

  if (area < 30000)
    area = 30000;

  if (area < 40000)
    area = 40000;


  int area_end = search_of_area_size(matrix, sum_matrix, 5, area);

  for (int i = 0; i < 5; i++)
  {
    r->list_vertex = add_vertex(matrix[i][0], matrix[i][1], r->list_vertex);
    
    if (i + 1 == 5)
      r->list_vertex = add_vertex(matrix[0][0], matrix[0][1], r->list_vertex);
  }

  return r;
}

bathroom *build_bathroom (int matrix[][2], int sum_matrix[][2], int area)
{
  bathroom *b = (bathroom *) malloc(sizeof(bathroom));

  if (b == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  b->list_vertex = NULL;
  
  if (area < 3000)
    area = 3000;
  
  if (area > 8000)
    area = 8000;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  for (int i = 0; i < 4; i++)
  {
    b->list_vertex = add_vertex(matrix[i][0], matrix[i][1], b->list_vertex);
    
    if (i + 1 == 4)
      b->list_vertex = add_vertex(matrix[0][0], matrix[0][1], b->list_vertex);
  }

  return b;
}

closet *build_closet (int matrix[][2], int sum_matrix[][2], int area)
{
  closet *c = (closet *) malloc(sizeof(closet));

  if (c == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  c->list_vertex = NULL;

  //verificando a area do closet [3,4]
  if (area > 4000)
    area = 4000;
  
  if (area < 3000)
    area = 3000;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  for (int i = 0; i < 4; i++)
  {
    c->list_vertex = add_vertex(matrix[i][0], matrix[i][1], c->list_vertex);
    
    if (i + 1 == 4)
      c->list_vertex = add_vertex(matrix[0][0], matrix[0][1], c->list_vertex);
  }

  return c;
}

dining_room_with_kitchen *build_dining_room_with_kitchen (int matrix[][2], int sum_matrix[][2], int area, int pos)
{
  dining_room_with_kitchen *r = (dining_room_with_kitchen *) malloc(sizeof(dining_room_with_kitchen));

  if (r == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  r->list_vertex = NULL;

  if (area > 45000)
    area = 45000;
  
  if (area < 25000)
    area = 25000;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  for (int i = 0; i < 4; i++)
  {
    r->list_vertex = add_vertex(matrix[i][0], matrix[i][1], r->list_vertex);
    
    if (i + 1 == 4)
      r->list_vertex = add_vertex(matrix[0][0], matrix[0][1], r->list_vertex);
  }
  
  //verificar pela posição do norte
  if (pos == 1)
  {
    matrix[0][0] = matrix[1][0];
    matrix[0][1] = matrix[1][1];
    matrix[3][0] = matrix[2][0];
    matrix[3][1] = matrix[2][1];

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = 0;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 0;
  }
  else if (pos == 2)
  {
    matrix[0][0] = matrix[3][0];
    matrix[0][1] = matrix[3][1];
    matrix[1][0] = matrix[2][0];
    matrix[1][1] = matrix[2][1];

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = 0;
    sum_matrix[3][0] = 1;
    sum_matrix[3][1] = 0;
  }
  else if (pos == 3)
  {
    matrix[0][0] = matrix[1][0];
    matrix[0][1] = matrix[1][1];
    matrix[3][0] = matrix[2][0];
    matrix[3][1] = matrix[2][1];

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = -1;
    sum_matrix[2][0] = 0;
    sum_matrix[2][1] = -1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 0;
  }
  else if (pos == 4)
  {
    matrix[0][0] = matrix[3][0];
    matrix[0][1] = matrix[3][1];
    matrix[1][0] = matrix[2][0];
    matrix[1][1] = matrix[2][1];

    sum_matrix[0][0] = -1;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = -1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 0;
    sum_matrix[2][1] = 0;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 0;
  } 

  int area_kitchen = (int) ((double)area_end * 0.4);

  r->kitchen = build_kitchen(matrix, sum_matrix, area_kitchen);

  return r;

}

bedroom_with_closet *build_beadroom_with_closet(int matrix[][2], int sum_matrix[][2], int area, int pos)
{
  bedroom_with_closet *b = (bedroom_with_closet *) malloc(sizeof(bedroom_with_closet));

  if (b == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  b->list_vertex = NULL;

  //verificando o limite [15, 38] m²
  if (area < 15000)
    area = 15000;

  if (area > 34000)
    area = 34000;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  for (int i = 0; i < 4; i++)
  {
    b->list_vertex = add_vertex(matrix[i][0], matrix[i][1], b->list_vertex);
    
    if (i + 1 == 4)
      b->list_vertex = add_vertex(matrix[0][0], matrix[0][1], b->list_vertex);
  }

  
  //verificar pela posição do norte
  if (pos == 1)
  {
    matrix[0][0] = matrix[3][0];
    matrix[0][1] = matrix[3][1];
    matrix[1][0] = matrix[2][0];
    matrix[1][1] = matrix[2][1];

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = -1;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = -1;
    sum_matrix[2][0] = 0;
    sum_matrix[2][1] = 0;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 0; 

  }
  else if (pos == 2)
  {
    matrix[0][0] = matrix[3][0];
    matrix[0][1] = matrix[3][1];
    matrix[1][0] = matrix[2][0];
    matrix[1][1] = matrix[2][1];

    sum_matrix[0][0] = -1;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = -1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 0;
    sum_matrix[2][1] = 0;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 0; 
  }
  else if (pos == 3)
  {
    matrix[0][0] = matrix[3][0];
    matrix[0][1] = matrix[3][1];
    matrix[1][0] = matrix[2][0];
    matrix[1][1] = matrix[2][1];

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 1;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = 0;
    sum_matrix[2][1] = 0;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 0; 
  }
  else if (pos == 4)
  {
    matrix[0][0] = matrix[1][0];
    matrix[0][1] = matrix[1][1];
    matrix[3][0] = matrix[2][0];
    matrix[3][1] = matrix[2][1];

    sum_matrix[0][0] = 1;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 0;
    sum_matrix[2][1] = 0;
    sum_matrix[3][0] = 1;
    sum_matrix[3][1] = 0; 
  }

  b->closet = build_closet(matrix, sum_matrix, (int) ((double)area_end * 0.25));

  return b;
}

bedroom_with_bathroom *build_beadroom_with_bathroom(int matrix[][2], int sum_matrix[][2], int area, int pos, int num_bed)
{
  bedroom_with_bathroom *b = (bedroom_with_bathroom *) malloc(sizeof(bedroom_with_bathroom));

  if (b == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  b->list_vertex = NULL;

  //verificando o limite [15, 38]
  if (area < 15000)
    area = 15000;

  if (area > 38000)
    area = 38000;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  for (int i = 0; i < 4; i++)
  {
    b->list_vertex = add_vertex(matrix[i][0], matrix[i][1], b->list_vertex);

    if (i + 1 == 4)
      b->list_vertex = add_vertex(matrix[0][0], matrix[0][1], b->list_vertex);
  }

  if (pos == 1)
  {
    for (int i = 1; i < 4; i++)
    {
      matrix[i][0] = matrix[0][0];
      matrix[i][1] = matrix[0][1];
    }

    if (num_bed == 1)
    {

      sum_matrix[0][0] = 0;
      sum_matrix[0][1] = 0;
      sum_matrix[1][0] = -1;
      sum_matrix[1][1] = 0;
      sum_matrix[2][0] = -1;
      sum_matrix[2][1] = 1;
      sum_matrix[3][0] = 0;
      sum_matrix[3][1] = 1; 
    }
    else if(num_bed == 2)
    {
      sum_matrix[0][0] = 0;
      sum_matrix[0][1] = 0;
      sum_matrix[1][0] = 1;
      sum_matrix[1][1] = 0;
      sum_matrix[2][0] = 1;
      sum_matrix[2][1] = 1;
      sum_matrix[3][0] = 0;
      sum_matrix[3][1] = 1;
    }
  }
  else if (pos == 2)
  {
    for (int i = 1; i < 4; i++)
    {
      matrix[i][0] = matrix[0][0];
      matrix[i][1] = matrix[0][1];
    }

    if (num_bed == 1)
    {

      sum_matrix[0][0] = 0;
      sum_matrix[0][1] = 0;
      sum_matrix[1][0] = 1;
      sum_matrix[1][1] = 0;
      sum_matrix[2][0] = 1;
      sum_matrix[2][1] = 1;
      sum_matrix[3][0] = 0;
      sum_matrix[3][1] = 1; 
    }
    else if(num_bed == 2)
    {
      sum_matrix[0][0] = 0;
      sum_matrix[0][1] = 0;
      sum_matrix[1][0] = 0;
      sum_matrix[1][1] = -1;
      sum_matrix[2][0] = 1;
      sum_matrix[2][1] = -1;
      sum_matrix[3][0] = 1;
      sum_matrix[3][1] = 0;
    }
  }
  else if (pos == 3)
  {
    for (int i = 1; i < 4; i++)
    {
      matrix[i][0] = matrix[0][0];
      matrix[i][1] = matrix[0][1];
    }

    if (num_bed == 1)
    {

      sum_matrix[0][0] = 0;
      sum_matrix[0][1] = 0;
      sum_matrix[1][0] = 1;
      sum_matrix[1][1] = 0;
      sum_matrix[2][0] = 1;
      sum_matrix[2][1] = -1;
      sum_matrix[3][0] = 0;
      sum_matrix[3][1] = -1; 
    }
    else if(num_bed == 2)
    {
      sum_matrix[0][0] = 0;
      sum_matrix[0][1] = 0;
      sum_matrix[1][0] = -1;
      sum_matrix[1][1] = 0;
      sum_matrix[2][0] = -1;
      sum_matrix[2][1] = -1;
      sum_matrix[3][0] = 0;
      sum_matrix[3][1] = -1;
    }
  }
  else if (pos == 4)
  {
    for (int i = 1; i < 4; i++)
    {
      matrix[i][0] = matrix[0][0];
      matrix[i][1] = matrix[0][1];
    }

    if (num_bed == 1)
    {

      sum_matrix[0][0] = 0;
      sum_matrix[0][1] = 0;
      sum_matrix[1][0] = -1;
      sum_matrix[1][1] = 0;
      sum_matrix[2][0] = -1;
      sum_matrix[2][1] = -1;
      sum_matrix[3][0] = 0;
      sum_matrix[3][1] = -1; 
    }
    else if(num_bed == 2)
    {
      sum_matrix[0][0] = 0;
      sum_matrix[0][1] = 0;
      sum_matrix[1][0] = 0;
      sum_matrix[1][1] = 1;
      sum_matrix[2][0] = -1;
      sum_matrix[2][1] = 1;
      sum_matrix[3][0] = -1;
      sum_matrix[3][1] = 0;
    }
  }

  b->bathroom = build_bathroom(matrix, sum_matrix, (int) ((double)area_end * 0.25));

  return b;
}

house *build_house (int area, int pos)
{
  house *h = (house *) malloc(sizeof(house));

  if (h == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  //inicializando os comodos como vazio
  h->social_bathroom = NULL;
  h->bedroom = NULL;
  h->bedroom1 = NULL;
  h->bedroom2 = NULL;
  h->dining_room_with_kitchen = NULL;
  h->gym_room = NULL;
  h->living_room = NULL;
  h->service_area = NULL;
  h->area = NULL;

  if (pos == 1)
  {

  //primeiro quarto com banheiro _
  int matrix[4][2], sum_matrix[4][2];

  for (int i = 0; i < 4; i++)
  {
    matrix[i][0] = MAX_SIZE_WINDOW / 2;
    matrix[i][1] = MAX_SIZE_WINDOW / 2;
  }

  sum_matrix[0][0] = 1;
  sum_matrix[0][1] = 0;
  sum_matrix[1][0] = 1;
  sum_matrix[1][1] = 2;
  sum_matrix[2][0] = -1;
  sum_matrix[2][1] = 2;
  sum_matrix[3][0] = -1;
  sum_matrix[3][1] = 0; 

  h->bedroom1 = build_beadroom_with_bathroom(matrix, sum_matrix, (int) ((double)area * 0.1315), pos, 1);

  //segundo quarto com banheiro 
  for (int i = 0; i < 4; i++)
  {
    matrix[i][0] = h->bedroom1->list_vertex->x;
    matrix[i][1] = h->bedroom1->list_vertex->y;
  }

  sum_matrix[0][0] = 0;
  sum_matrix[0][1] = 0;
  sum_matrix[1][0] = 1;
  sum_matrix[1][1] = 0;
  sum_matrix[2][0] = 1;
  sum_matrix[2][1] = 1;
  sum_matrix[3][0] = 0;
  sum_matrix[3][1] = 1; 

  h->bedroom2 = build_beadroom_with_bathroom(matrix, sum_matrix, (int) ((double)area * 0.1315), pos, 2);
  
  //quarto com closet  
  list *aux = h->bedroom1->list_vertex;
  int i = 0;
  
  while (i != 3)
  {
    aux = aux->next;
    i += 1;
  }
  
  for (int i = 0; i < 4; i++)
  {
    matrix[i][0] = aux->x;
    matrix[i][1] = aux->y;
  }

  sum_matrix[0][0] = 0;
  sum_matrix[0][1] = 0;
  sum_matrix[1][0] = -1;
  sum_matrix[1][1] = 0;
  sum_matrix[2][0] = -1;
  sum_matrix[2][1] = 1;
  sum_matrix[3][0] = 0;
  sum_matrix[3][1] = 1;
  
  h->bedroom = build_beadroom_with_closet(matrix, sum_matrix, (int) ((double)area * 0.1315), pos);

  //sala de ginastica
  aux = h->bedroom2->list_vertex;
  i = 0;
  
  while (i != 1)
  {
    aux = aux->next;
    i += 1;
  }

  for (int i = 0; i < 4; i++)
  {
    matrix[i][0] = aux->x;
    matrix[i][1] = aux->y;
  }

  sum_matrix[0][0] = 0;
  sum_matrix[0][1] = 0;
  sum_matrix[1][0] = 0;
  sum_matrix[1][1] = -1;
  sum_matrix[2][0] = -1;
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = -1;
  sum_matrix[3][1] = 0;

  h->gym_room = build_gym_room(matrix, sum_matrix, (int) ((double)area * 0.175));

  //sala de jantar com cozinha
  aux = h->gym_room->list_vertex;
  i = 0;
  
  while (i != 3)
  {
    aux = aux->next;
    i += 1;
  }

  for (int i = 0; i < 4; i++)
  {
    matrix[i][0] = aux->x;
    matrix[i][1] = aux->y;
  }

  sum_matrix[0][0] = 0;
  sum_matrix[0][1] = 0;
  sum_matrix[1][0] = 0;
  sum_matrix[1][1] = -1;
  sum_matrix[2][0] = -1;
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = -1;
  sum_matrix[3][1] = 0;

  h->dining_room_with_kitchen = build_dining_room_with_kitchen(matrix, sum_matrix, (int) ((double)area * 0.235), pos);
  
  //banheiro social
  aux = h->dining_room_with_kitchen->list_vertex;
  
  i = 0;

  while (i != 3)
  {
    aux = aux->next;
    i += 1;
  }

  matrix[0][0] = aux->x;
  matrix[0][1] = aux->y;
  matrix[1][0] = aux->x;
  matrix[1][1] = aux->y;
  
  aux = h->bedroom->list_vertex;

  i = 0;

  while (i != 1)
  {
    aux = aux->next;
    i += 1;
  }

  matrix[2][0] = aux->x;
  matrix[2][1] = aux->y;
  matrix[3][0] = aux->x;
  matrix[3][1] = aux->y;

  sum_matrix[0][0] = 0;
  sum_matrix[0][1] = 0;
  sum_matrix[1][0] = 0;
  sum_matrix[1][1] = -1;
  sum_matrix[2][0] = 0;
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = 0;
  sum_matrix[3][1] = 0;

  h->social_bathroom = build_bathroom(matrix, sum_matrix, (int) ((double)area * 0.027));
  
  //area de serviço
  aux = h->gym_room->list_vertex;
  i = 0;
  
  while (i != 2)
  {
    aux = aux->next;
    i += 1;
  }
  
  for (int i = 0; i < 4; i++)
  {
    matrix[i][0] = aux->x;
    matrix[i][1] = aux->y;
  }

  sum_matrix[0][0] = 0;
  sum_matrix[0][1] = 0;
  sum_matrix[1][0] = 0;
  sum_matrix[1][1] = -1;
  sum_matrix[2][0] = 2;
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = 2;
  sum_matrix[3][1] = 0;

  h->service_area = build_service_area(matrix, sum_matrix, (int) ((double)area * 0.055));

  //sala de estar
  int matrix_room[5][2], sum_matrix_room[5][2];

  aux = h->bedroom2->list_vertex;
  
  i = 0;
  
  while (i != 2)
  {
    aux = aux->next;
    i += 1;
  }

  matrix_room[0][0] = MAX_SIZE_WINDOW / 2;
  matrix_room[0][1] = aux->y + 100;
  matrix_room[1][0] = aux->x;
  matrix_room[1][1] = aux->y;
  matrix_room[2][0] = aux->x;
  matrix_room[2][1] = aux->y;
  
  aux = h->bedroom->list_vertex;
  i = 0;
  
  while (i != 2)
  {
    aux = aux->next;
    i += 1;
  }

  matrix_room[3][0] = aux->x - 30;
  matrix_room[3][1] = aux->y;
  matrix_room[4][0] = aux->x - 30;
  matrix_room[4][1] = aux->y;

  sum_matrix_room[0][0] = 0;
  sum_matrix_room[0][1] = 1;
  sum_matrix_room[1][0] = 0;
  sum_matrix_room[1][1] = 1;
  sum_matrix_room[2][0] = 0;
  sum_matrix_room[2][1] = 0;
  sum_matrix_room[3][0] = 0;
  sum_matrix_room[3][1] = 0;
  sum_matrix_room[4][0] = 0;
  sum_matrix_room[4][1] = 1;

  h->living_room = build_living_room(matrix_room, sum_matrix_room, (int) ((double)area * 0.265));

  //area da casa
  int matrix_area_house[6][2], sum_matrix_area_house[6][2];

  matrix_area_house[0][0] = h->living_room->list_vertex->x;
  matrix_area_house[0][1] = h->living_room->list_vertex->y;

  aux = h->living_room->list_vertex;
  i = 0;
  
  while (i != 1)
  {
    aux = aux->next;
    i += 1;
  }

  matrix_area_house[1][0] = aux->x;
  matrix_area_house[1][1] = aux->y;
  
  aux = h->living_room->list_vertex;
  i = 0;
  
  while (i != 4)
  {
    aux = aux->next;
    i += 1;
  }

  matrix_area_house[5][0] = aux->x;
  matrix_area_house[5][1] = aux->y;

  matrix_area_house[2][0] = matrix_room[1][0];

  aux = h->service_area->list_vertex;
  i = 0;
  
  while (i != 2)
  {
    aux = aux->next;
    i += 1;
  }

  matrix_area_house[2][1] = aux->y;

  matrix_area_house[3][0] = MAX_SIZE_WINDOW / 2;
  matrix_area_house[3][1] = aux->y - 100;

  matrix_area_house[4][0] = matrix_area_house[5][0];
  matrix_area_house[4][1] = aux->y;

  sum_matrix_area_house[0][0] = 0;
  sum_matrix_area_house[0][1] = 0;
  sum_matrix_area_house[1][0] = 0;
  sum_matrix_area_house[1][1] = 0;
  sum_matrix_area_house[2][0] = 0;
  sum_matrix_area_house[2][1] = 1;
  sum_matrix_area_house[3][0] = 0;
  sum_matrix_area_house[3][1] = 1;
  sum_matrix_area_house[4][0] = 0;
  sum_matrix_area_house[4][1] = 1;
  sum_matrix_area_house[5][0] = 0;
  sum_matrix_area_house[5][1] = 0;

  h->area = build_area_house(matrix_area_house, sum_matrix_area_house, area);

  }
  else if (pos == 2)
  {
    //primeiro quarto com banheiro _
    int matrix[4][2], sum_matrix[4][2];

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = MAX_SIZE_WINDOW / 2;
      matrix[i][1] = MAX_SIZE_WINDOW / 2;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = -1;
    sum_matrix[1][0] = 2;
    sum_matrix[1][1] = -1;
    sum_matrix[2][0] = 2;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 1; 

    h->bedroom1 = build_beadroom_with_bathroom(matrix, sum_matrix, (int) ((double)area * 0.1315), pos, 1);

    //segundo quarto com banheiro 
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = h->bedroom1->list_vertex->x;
      matrix[i][1] = h->bedroom1->list_vertex->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = -1;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = -1;
    sum_matrix[3][0] = 1;
    sum_matrix[3][1] = 0; 

    h->bedroom2 = build_beadroom_with_bathroom(matrix, sum_matrix, (int) ((double)area * 0.1315), pos, 2);
    
    //quarto com closet  
    list *aux = h->bedroom1->list_vertex;
    int i = 0;
    
    while (i != 3)
    {
      aux = aux->next;
      i += 1;
    }
    
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = 1;
    sum_matrix[3][1] = 0;
    
    h->bedroom = build_beadroom_with_closet(matrix, sum_matrix, (int) ((double)area * 0.1315), pos);
  
    //sala de ginastica
    aux = h->bedroom2->list_vertex;
    i = 0;
    
    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = -1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = -1;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 1;

    h->gym_room = build_gym_room(matrix, sum_matrix, (int) ((double)area * 0.175));

    //sala de jantar com cozinha
    aux = h->gym_room->list_vertex;
    i = 0;
    
    while (i != 3)
    {
      aux = aux->next;
      i += 1;
    }

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = -1;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = -1;
    sum_matrix[3][1] = 0;

    h->dining_room_with_kitchen = build_dining_room_with_kitchen(matrix, sum_matrix, (int) ((double)area * 0.235), pos);

    //banheiro social
    aux = h->dining_room_with_kitchen->list_vertex;
    
    i = 0;

    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    matrix[0][0] = aux->x;
    matrix[0][1] = aux->y;
    matrix[3][0] = aux->x;
    matrix[3][1] = aux->y;
    
    aux = h->bedroom->list_vertex;

    i = 0;

    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    matrix[1][0] = aux->x;
    matrix[1][1] = aux->y;
    matrix[2][0] = aux->x;
    matrix[2][1] = aux->y;

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = -1;
    sum_matrix[2][1] = 0;
    sum_matrix[3][0] = -1;
    sum_matrix[3][1] = 0;

    h->social_bathroom = build_bathroom(matrix, sum_matrix, (int) ((double)area * 0.027));
    
    //area de serviço
    aux = h->gym_room->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }
    
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = -2;
    sum_matrix[2][0] = -1;
    sum_matrix[2][1] = -2;
    sum_matrix[3][0] = -1;
    sum_matrix[3][1] = 0;

    h->service_area = build_service_area(matrix, sum_matrix, (int) ((double)area * 0.055));

    //sala de estar
    int matrix_room[5][2], sum_matrix_room[5][2];

    aux = h->bedroom2->list_vertex;
    
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_room[0][0] = aux->x + 100;
    matrix_room[0][1] = MAX_SIZE_WINDOW / 2;
    matrix_room[1][0] = aux->x;
    matrix_room[1][1] = aux->y;
    matrix_room[2][0] = aux->x;
    matrix_room[2][1] = aux->y;
    
    aux = h->bedroom->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_room[3][0] = aux->x;
    matrix_room[3][1] = aux->y + 30;
    matrix_room[4][0] = aux->x;
    matrix_room[4][1] = aux->y + 30;

    sum_matrix_room[0][0] = 1;
    sum_matrix_room[0][1] = 0;
    sum_matrix_room[1][0] = 1;
    sum_matrix_room[1][1] = 0;
    sum_matrix_room[2][0] = 0;
    sum_matrix_room[2][1] = 0;
    sum_matrix_room[3][0] = 0;
    sum_matrix_room[3][1] = 0;
    sum_matrix_room[4][0] = 1;
    sum_matrix_room[4][1] = 0;

    h->living_room = build_living_room(matrix_room, sum_matrix_room, (int) ((double)area * 0.265));
  
    //area da casa
    int matrix_area_house[6][2], sum_matrix_area_house[6][2];

    matrix_area_house[0][0] = h->living_room->list_vertex->x;
    matrix_area_house[0][1] = h->living_room->list_vertex->y;

    aux = h->living_room->list_vertex;
    i = 0;
    
    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[1][0] = aux->x;
    matrix_area_house[1][1] = aux->y;
    
    aux = h->living_room->list_vertex;
    i = 0;
    
    while (i != 4)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[5][0] = aux->x;
    matrix_area_house[5][1] = aux->y;
    matrix_area_house[4][1] = matrix_area_house[5][1];
    matrix_area_house[2][1] = matrix_room[1][1];

    aux = h->service_area->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[2][0] = aux->x;
    matrix_area_house[4][0] = matrix_area_house[2][0];

    matrix_area_house[3][0] = aux->x - 100;
    matrix_area_house[3][1] = MAX_SIZE_WINDOW / 2;


    sum_matrix_area_house[0][0] = 0;
    sum_matrix_area_house[0][1] = 0;
    sum_matrix_area_house[1][0] = 0;
    sum_matrix_area_house[1][1] = 0;
    sum_matrix_area_house[2][0] = -1;
    sum_matrix_area_house[2][1] = 0;
    sum_matrix_area_house[3][0] = -1;
    sum_matrix_area_house[3][1] = 0;
    sum_matrix_area_house[4][0] = -1;
    sum_matrix_area_house[4][1] = 0;
    sum_matrix_area_house[5][0] = 0;
    sum_matrix_area_house[5][1] = 0;

    h->area = build_area_house(matrix_area_house, sum_matrix_area_house, area);
    
  }
  else if (pos == 3)
  {
    //primeiro quarto com banheiro _
    int matrix[4][2], sum_matrix[4][2];

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = MAX_SIZE_WINDOW / 2;
      matrix[i][1] = MAX_SIZE_WINDOW / 2;
    }

    sum_matrix[0][0] = -1;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = -2;
    sum_matrix[3][0] = -1;
    sum_matrix[3][1] = -2; 

    h->bedroom1 = build_beadroom_with_bathroom(matrix, sum_matrix, (int) ((double)area * 0.1315), pos, 1);

    //segundo quarto com banheiro 
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = h->bedroom1->list_vertex->x;
      matrix[i][1] = h->bedroom1->list_vertex->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = -1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = -1;
    sum_matrix[2][1] = -1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = -1; 

    h->bedroom2 = build_beadroom_with_bathroom(matrix, sum_matrix, (int) ((double)area * 0.1315), pos, 2);
    
    
    //quarto com closet  
    list *aux = h->bedroom1->list_vertex;
    int i = 0;
    
    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }
    
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = -1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = -1;
    
    h->bedroom = build_beadroom_with_closet(matrix, sum_matrix, (int) ((double)area * 0.1315), pos);

    
    //sala de ginastica
    aux = h->bedroom2->list_vertex;
    i = 0;
    
    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = 1;
    sum_matrix[3][1] = 0;

    h->gym_room = build_gym_room(matrix, sum_matrix, (int) ((double)area * 0.175));

    
    //sala de jantar com cozinha
    aux = h->gym_room->list_vertex;
    i = 0;
    
    while (i != 3)
    {
      aux = aux->next;
      i += 1;
    }

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = 1;
    sum_matrix[3][1] = 0;

    h->dining_room_with_kitchen = build_dining_room_with_kitchen(matrix, sum_matrix, (int) ((double)area * 0.235), pos);
    
    //banheiro social
    aux = h->dining_room_with_kitchen->list_vertex;
    
    i = 0;

    while (i != 3)
    {
      aux = aux->next;
      i += 1;
    }

    matrix[0][0] = aux->x;
    matrix[0][1] = aux->y;
    matrix[1][0] = aux->x;
    matrix[1][1] = aux->y;
    
    aux = h->bedroom->list_vertex;

    i = 0;

    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    matrix[2][0] = aux->x;
    matrix[2][1] = aux->y;
    matrix[3][0] = aux->x;
    matrix[3][1] = aux->y;

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = 0;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 0;

    h->social_bathroom = build_bathroom(matrix, sum_matrix, (int) ((double)area * 0.027));
    
    //area de serviço
    aux = h->gym_room->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }
    
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = -2;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = -2;
    sum_matrix[3][1] = 0;

    h->service_area = build_service_area(matrix, sum_matrix, (int) ((double)area * 0.055));

    //sala de estar
    int matrix_room[5][2], sum_matrix_room[5][2];

    aux = h->bedroom2->list_vertex;
    
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_room[0][0] = MAX_SIZE_WINDOW / 2;
    matrix_room[0][1] = aux->y - 100;
    matrix_room[1][0] = aux->x;
    matrix_room[1][1] = aux->y;
    matrix_room[2][0] = aux->x;
    matrix_room[2][1] = aux->y;
    
    aux = h->bedroom->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_room[3][0] = aux->x + 30;
    matrix_room[3][1] = aux->y;
    matrix_room[4][0] = aux->x + 30;
    matrix_room[4][1] = aux->y;

    sum_matrix_room[0][0] = 0;
    sum_matrix_room[0][1] = -1;
    sum_matrix_room[1][0] = 0;
    sum_matrix_room[1][1] = -1;
    sum_matrix_room[2][0] = 0;
    sum_matrix_room[2][1] = 0;
    sum_matrix_room[3][0] = 0;
    sum_matrix_room[3][1] = 0;
    sum_matrix_room[4][0] = 0;
    sum_matrix_room[4][1] = -1;

    h->living_room = build_living_room(matrix_room, sum_matrix_room, (int) ((double)area * 0.265));

    //area da casa
    int matrix_area_house[6][2], sum_matrix_area_house[6][2];

    matrix_area_house[0][0] = h->living_room->list_vertex->x;
    matrix_area_house[0][1] = h->living_room->list_vertex->y;

    aux = h->living_room->list_vertex;
    i = 0;
    
    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[1][0] = aux->x;
    matrix_area_house[1][1] = aux->y;
    
    aux = h->living_room->list_vertex;
    i = 0;
    
    while (i != 4)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[5][0] = aux->x;
    matrix_area_house[5][1] = aux->y;

    matrix_area_house[2][0] = matrix_room[1][0];

    aux = h->service_area->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[2][1] = aux->y;

    matrix_area_house[3][0] = MAX_SIZE_WINDOW / 2;
    matrix_area_house[3][1] = aux->y + 100;

    matrix_area_house[4][0] = matrix_area_house[5][0];
    matrix_area_house[4][1] = aux->y;

    sum_matrix_area_house[0][0] = 0;
    sum_matrix_area_house[0][1] = 0;
    sum_matrix_area_house[1][0] = 0;
    sum_matrix_area_house[1][1] = 0;
    sum_matrix_area_house[2][0] = 0;
    sum_matrix_area_house[2][1] = 1;
    sum_matrix_area_house[3][0] = 0;
    sum_matrix_area_house[3][1] = 1;
    sum_matrix_area_house[4][0] = 0;
    sum_matrix_area_house[4][1] = 1;
    sum_matrix_area_house[5][0] = 0;
    sum_matrix_area_house[5][1] = 0;

    h->area = build_area_house(matrix_area_house, sum_matrix_area_house, area);
  }
  else if (pos == 4)
  {
     //primeiro quarto com banheiro _
    int matrix[4][2], sum_matrix[4][2];

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = MAX_SIZE_WINDOW / 2;
      matrix[i][1] = MAX_SIZE_WINDOW / 2;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 1;
    sum_matrix[1][0] = -2;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = -2;
    sum_matrix[2][1] = -1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = -1; 

    h->bedroom1 = build_beadroom_with_bathroom(matrix, sum_matrix, (int) ((double)area * 0.1315), pos, 1);
  
    //segundo quarto com banheiro 
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = h->bedroom1->list_vertex->x;
      matrix[i][1] = h->bedroom1->list_vertex->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 1;
    sum_matrix[2][0] = -1;
    sum_matrix[2][1] = 1;
    sum_matrix[3][0] = -1;
    sum_matrix[3][1] = 0; 

    h->bedroom2 = build_beadroom_with_bathroom(matrix, sum_matrix, (int) ((double)area * 0.1315), pos, 2);
    
    //quarto com closet  
    list *aux = h->bedroom1->list_vertex;
    int i = 0;
    
    while (i != 3)
    {
      aux = aux->next;
      i += 1;
    }
    
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = -1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = -1;
    sum_matrix[2][1] = -1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = -1;
    
    h->bedroom = build_beadroom_with_closet(matrix, sum_matrix, (int) ((double)area * 0.1315), pos);
    
    //sala de ginastica
    aux = h->bedroom2->list_vertex;
    i = 0;
    
    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = -1;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = -1;

    h->gym_room = build_gym_room(matrix, sum_matrix, (int) ((double)area * 0.175));
    
    
    //sala de jantar com cozinha
    aux = h->gym_room->list_vertex;
    i = 0;
    
    while (i != 3)
    {
      aux = aux->next;
      i += 1;
    }

    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = -1;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = -1;
    sum_matrix[3][0] = 1;
    sum_matrix[3][1] = 0;

    h->dining_room_with_kitchen = build_dining_room_with_kitchen(matrix, sum_matrix, (int) ((double)area * 0.235), pos);
    
    //banheiro social
    aux = h->dining_room_with_kitchen->list_vertex;
    
    i = 0;

    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    matrix[0][0] = aux->x;
    matrix[0][1] = aux->y;
    matrix[3][0] = aux->x;
    matrix[3][1] = aux->y;
    
    aux = h->bedroom->list_vertex;

    i = 0;

    while (i != 3)
    {
      aux = aux->next;
      i += 1;
    }

    matrix[1][0] = aux->x;
    matrix[1][1] = aux->y;
    matrix[2][0] = aux->x;
    matrix[2][1] = aux->y;

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 0;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = 0;
    sum_matrix[3][0] = 1;
    sum_matrix[3][1] = 0;

    h->social_bathroom = build_bathroom(matrix, sum_matrix, (int) ((double)area * 0.027));
  
    //area de serviço
    aux = h->gym_room->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }
    
    for (int i = 0; i < 4; i++)
    {
      matrix[i][0] = aux->x;
      matrix[i][1] = aux->y;
    }

    sum_matrix[0][0] = 0;
    sum_matrix[0][1] = 0;
    sum_matrix[1][0] = 1;
    sum_matrix[1][1] = 0;
    sum_matrix[2][0] = 1;
    sum_matrix[2][1] = 2;
    sum_matrix[3][0] = 0;
    sum_matrix[3][1] = 2;

    h->service_area = build_service_area(matrix, sum_matrix, (int) ((double)area * 0.055));

    //sala de estar
    int matrix_room[5][2], sum_matrix_room[5][2];

    aux = h->bedroom2->list_vertex;
    
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_room[0][0] = aux->x - 100;
    matrix_room[0][1] = MAX_SIZE_WINDOW / 2;
    matrix_room[1][0] = aux->x;
    matrix_room[1][1] = aux->y;
    matrix_room[2][0] = aux->x;
    matrix_room[2][1] = aux->y;
    
    aux = h->bedroom->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_room[3][0] = aux->x;
    matrix_room[3][1] = aux->y - 30;
    matrix_room[4][0] = aux->x;
    matrix_room[4][1] = aux->y - 30;

    sum_matrix_room[0][0] = -1;
    sum_matrix_room[0][1] = 0;
    sum_matrix_room[1][0] = -1;
    sum_matrix_room[1][1] = 0;
    sum_matrix_room[2][0] = 0;
    sum_matrix_room[2][1] = 0;
    sum_matrix_room[3][0] = 0;
    sum_matrix_room[3][1] = 0;
    sum_matrix_room[4][0] = -1;
    sum_matrix_room[4][1] = 0;

    h->living_room = build_living_room(matrix_room, sum_matrix_room, (int) ((double)area * 0.265));
  
    //area da casa
    int matrix_area_house[6][2], sum_matrix_area_house[6][2];

    matrix_area_house[0][0] = h->living_room->list_vertex->x;
    matrix_area_house[0][1] = h->living_room->list_vertex->y;

    aux = h->living_room->list_vertex;
    i = 0;
    
    while (i != 1)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[1][0] = aux->x;
    matrix_area_house[1][1] = aux->y;
    
    aux = h->living_room->list_vertex;
    i = 0;
    
    while (i != 4)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[5][0] = aux->x;
    matrix_area_house[5][1] = aux->y;
    matrix_area_house[4][1] = matrix_area_house[5][1];
    matrix_area_house[2][1] = matrix_room[1][1];

    aux = h->service_area->list_vertex;
    i = 0;
    
    while (i != 2)
    {
      aux = aux->next;
      i += 1;
    }

    matrix_area_house[2][0] = aux->x;
    matrix_area_house[4][0] = matrix_area_house[2][0];

    matrix_area_house[3][0] = aux->x + 100;
    matrix_area_house[3][1] = MAX_SIZE_WINDOW / 2;


    sum_matrix_area_house[0][0] = 0;
    sum_matrix_area_house[0][1] = 0;
    sum_matrix_area_house[1][0] = 0;
    sum_matrix_area_house[1][1] = 0;
    sum_matrix_area_house[2][0] = -1;
    sum_matrix_area_house[2][1] = 0;
    sum_matrix_area_house[3][0] = -1;
    sum_matrix_area_house[3][1] = 0;
    sum_matrix_area_house[4][0] = -1;
    sum_matrix_area_house[4][1] = 0;
    sum_matrix_area_house[5][0] = 0;
    sum_matrix_area_house[5][1] = 0;

    h->area = build_area_house(matrix_area_house, sum_matrix_area_house, area);
    
  }

  return h;
}

void display(house *h)
{ 
  glClear(GL_COLOR_BUFFER_BIT);

  if (h->bedroom1 != NULL)
  {
    print_lines_vertices(h->bedroom1->list_vertex);
    print_lines_vertices(h->bedroom1->bathroom->list_vertex);
  }

  if (h->bedroom2 != NULL)
  {
    print_lines_vertices(h->bedroom2->list_vertex);
    print_lines_vertices(h->bedroom2->bathroom->list_vertex);
  }

  if (h->bedroom != NULL)
  {
    print_lines_vertices(h->bedroom->list_vertex);
    print_lines_vertices(h->bedroom->closet->list_vertex);
  }

  if (h->gym_room != NULL)
    print_lines_vertices(h->gym_room->list_vertex);

  if (h->dining_room_with_kitchen != NULL)
  {
    print_lines_vertices(h->dining_room_with_kitchen->list_vertex);
    print_lines_vertices(h->dining_room_with_kitchen->kitchen->list_vertex);
  }
  
  if (h->living_room != NULL)
    print_lines_vertices(h->living_room->list_vertex);
  
  if (h->social_bathroom != NULL)
    print_lines_vertices(h->social_bathroom->list_vertex);
  
  if (h->area != NULL)
    print_lines_vertices(h->area);

  if (h->service_area != NULL)
    print_lines_vertices(h->service_area->list_vertex);

}

int main(int argc, char **argv)
{
  int area, pos;

  while (1)
  {
    printf("\nDigite a area da casa (area >= 130000 && area <= 250000): ");
    scanf("%d", &area);
    
    if(area >= 130000 && area <= 250000)
      break;

    printf("Valor da area nao esta no intervalo.\n\n");
  }

  while (1)
  {
    printf("\nMenu:\n");
    printf("1 - Norte para cima;\n");
    printf("2 - Norte para direita;\n");
    printf("3 - Norte para baixo;\n");
    printf("4 - Norte para esquerda;\n");
    printf("Digite uma opcao para definir o norte: ");
    scanf("%d", &pos);
    
    if(pos >= 1 && pos <= 4)
      break;

    printf("Digite uma opcao valida!\n\n");
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(MAX_SIZE_WINDOW, MAX_SIZE_WINDOW);
  glutInitWindowPosition(100, 0);
  glutCreateWindow("Planta baixa de casa");
  gluOrtho2D(0.0, MAX_SIZE_WINDOW, 0.0, MAX_SIZE_WINDOW);

  house *h = build_house(area, pos);
  display(h);
  
  glutMainLoop();

  return 0;
}
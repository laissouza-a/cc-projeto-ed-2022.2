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
  while (head != NULL)
  {
    glVertex2i(head->x, head->y);
    head = head->next;
  }

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

  printf("\nArea inicial = %d\nArea final da casa: %d\n\n", area, area_end);

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

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  printf("\nArea inicial = %d\nArea do quarto com closet: %d\n\n", area, area_end);

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

  if (area > 10000)
    area = 10000;
  

  service_area *s = (service_area *) malloc(sizeof(service_area));

  if (s == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  s->list_vertex = NULL;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  printf("\nArea inicial = %d\nArea do quarto com closet: %d\n\n", area, area_end);

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

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  printf("\nArea inicial = %d\nArea do quarto com closet: %d\n\n", area, area_end);

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

  int area_end = search_of_area_size(matrix, sum_matrix, 5, area);

  printf("\nArea inicial sala = %d\nArea sala: %d\n\n", area, area_end);

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

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  printf("\nArea inicial = %d\nArea do quarto com closet: %d\n\n", area, area_end);

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

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  printf("\nArea inicial = %d\nArea do quarto com closet: %d\n\n", area, area_end);

  for (int i = 0; i < 4; i++)
  {
    c->list_vertex = add_vertex(matrix[i][0], matrix[i][1], c->list_vertex);
    
    if (i + 1 == 4)
      c->list_vertex = add_vertex(matrix[0][0], matrix[0][1], c->list_vertex);
  }

  return c;
}

dining_room_with_kitchen *build_dining_room_with_kitchen (int matrix[][2], int sum_matrix[][2], int area)
{
  dining_room_with_kitchen *r = (dining_room_with_kitchen *) malloc(sizeof(dining_room_with_kitchen));

  if (r == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  r->list_vertex = NULL;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  printf("\nArea teste = %d\nArea do sala com cozinha: %d\n\n", area, area_end);

  for (int i = 0; i < 4; i++)
  {
    r->list_vertex = add_vertex(matrix[i][0], matrix[i][1], r->list_vertex);
    
    if (i + 1 == 4)
      r->list_vertex = add_vertex(matrix[0][0], matrix[0][1], r->list_vertex);
  }
    
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

    int area_kitchen = (int) ((double)area_end * 0.4);
    
    if (area_kitchen > 15000)
      area_kitchen = 15000;

    r->kitchen = build_kitchen(matrix, sum_matrix, area_kitchen);

    return r;

}

bedroom_with_closet *build_beadroom_with_closet(int matrix[][2], int sum_matrix[][2], int area)
{
  bedroom_with_closet *b = (bedroom_with_closet *) malloc(sizeof(bedroom_with_closet));

  if (b == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  b->list_vertex = NULL;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  printf("\nArea inicial = %d\nArea do quarto com closet: %d\n\n", area, area_end);

  for (int i = 0; i < 4; i++)
  {
    b->list_vertex = add_vertex(matrix[i][0], matrix[i][1], b->list_vertex);
    
    if (i + 1 == 4)
      b->list_vertex = add_vertex(matrix[0][0], matrix[0][1], b->list_vertex);
  }

  matrix[1][0] = matrix[0][0];
  matrix[1][1] = matrix[0][1];
  matrix[2][0] = matrix[3][0];
  matrix[2][1] = matrix[3][1];

  sum_matrix[0][0] = 0;
  sum_matrix[0][1] = 0;
  sum_matrix[1][0] = 0;
  sum_matrix[1][1] = -1;
  sum_matrix[2][0] = 0;
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = 0;
  sum_matrix[3][1] = 0; 

  int area_closet = (int) ((double)area_end * 0.2);
  
  if (area_closet > 4000)
    area_closet = 4000;

  b->closet = build_closet(matrix, sum_matrix, area_closet);

  return b;
}

bedroom_with_bathroom *build_beadroom_with_bathroom(int matrix[][2], int sum_matrix[][2], int area, int num_v)
{
  bedroom_with_bathroom *b = (bedroom_with_bathroom *) malloc(sizeof(bedroom_with_bathroom));

  if (b == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  b->list_vertex = NULL;

  int area_end = search_of_area_size(matrix, sum_matrix, 4, area);

  printf("\nArea inicial = %d\nArea do quarto com banheiro: %d\n\n", area, area_end);
  for (int i = 0; i < 4; i++)
  {
    b->list_vertex = add_vertex(matrix[i][0], matrix[i][1], b->list_vertex);

    if (i + 1 == 4)
      b->list_vertex = add_vertex(matrix[0][0], matrix[0][1], b->list_vertex);
  }
  
  
  matrix[0][0] = matrix[num_v][0];
  matrix[0][1] = matrix[num_v][1];

  for (int i = 1; i < 4; i++)
  {
    matrix[i][0] = matrix[0][0];
    matrix[i][1] = matrix[0][1];
  }

  if (num_v == 1)
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
  else if(num_v == 3)
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

  int area_bathroom = (int) ((double)area_end * 0.2);
  
  if (area_bathroom > 8000)
    area_bathroom = 8000;

  area_end = search_of_area_size(matrix, sum_matrix, 4, area_bathroom);

  printf("\nArea inicial banheiro = %d\nArea do banheiro: %d\n\n", area_bathroom, area_end);

  b->bathroom = build_bathroom(matrix, sum_matrix, area_bathroom);

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

  //primeiro quarto com banheiro 
  int area_bedroom = (int) ((double)area * 0.1315);

  if (area_bedroom > 38000)
    area_bedroom = 38000;

  int matrix[4][2], sum_matrix[4][2];

  for (int i = 0; i < 4; i++)
  {
    matrix[i][0] = MAX_SIZE_WINDOW / 2;
    matrix[i][1] = MAX_SIZE_WINDOW / 2;
  }

  sum_matrix[0][0] = 1;
  sum_matrix[0][1] = 1;
  sum_matrix[1][0] = 1;
  sum_matrix[1][1] = -1;
  sum_matrix[2][0] = -1;
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = -1;
  sum_matrix[3][1] = 1; 

  h->bedroom1 = build_beadroom_with_bathroom(matrix, sum_matrix, area_bedroom, 1);

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
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = 0;
  sum_matrix[3][1] = -1; 

  h->bedroom2 = build_beadroom_with_bathroom(matrix, sum_matrix, area_bedroom, 3);

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
  sum_matrix[1][1] = -1;
  sum_matrix[2][0] = -1;
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = -1;
  sum_matrix[3][1] = 0;

  if (area_bedroom > 34000)
    area_bedroom = 34000;

  h->bedroom = build_beadroom_with_closet(matrix, sum_matrix, area_bedroom);



  //sala de ginastica
  int area_gym_room = (int) ((double)area * 0.175);

  aux = h->bedroom2->list_vertex;
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
  sum_matrix[2][0] = -1;
  sum_matrix[2][1] = -1;
  sum_matrix[3][0] = -1;
  sum_matrix[3][1] = 0;

  h->gym_room = build_gym_room(matrix, sum_matrix, area_gym_room);

  //sala de jantar com cozinha
  int area_room_with_kitchen = (int) ((double)area * 0.235);

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

  h->dining_room_with_kitchen = build_dining_room_with_kitchen(matrix, sum_matrix, area_room_with_kitchen);
  
  //banheiro social
  int area_bathroom = (int) ((double)area * 0.0265);

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

  while (i != 2)
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
  

  //sala de estar
  int matrix_room[5][2], sum_matrix_room[5][2];

  matrix_room[0][0] = MAX_SIZE_WINDOW / 2;
  matrix_room[0][1] = h->bedroom1->list_vertex->y + 100;

  aux = h->bedroom2->list_vertex->next;

  matrix_room[1][0] = aux->x;
  matrix_room[1][1] = aux->y;
  matrix_room[2][0] = aux->x;
  matrix_room[2][1] = aux->y;
  
  aux = h->bedroom->list_vertex;
  i = 0;
  
  while (i != 3)
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

  aux = h->area;

  while (aux != NULL)
  {
    printf("(x,y) = (%d,%d)\n", aux->x, aux->y);
    aux = aux->next;
  }

/*
  if (pos == 1)
  {
    printf("%d", (int)((double) area * 0.25));
    int x0 = MAX_SIZE_WINDOW/2, x1 = MAX_SIZE_WINDOW/2, x2 = MAX_SIZE_WINDOW/2, x3 = MAX_SIZE_WINDOW/2, x4 = MAX_SIZE_WINDOW/2, x5 = MAX_SIZE_WINDOW/2;
    int y0 = MAX_SIZE_WINDOW/2 + 100, y1 = MAX_SIZE_WINDOW/2, y2 = MAX_SIZE_WINDOW/2, y3 = MAX_SIZE_WINDOW/2 - 100, y4 = MAX_SIZE_WINDOW/2, y5 = MAX_SIZE_WINDOW/2;

    int d1 = ((x1*y2 + x2*y3 + x2*y4 + x4*y1) - (x1*y2 + x3*y2 + x4*y3 + x1*y4));
    int d2 = ((x0*y1 + x1*y5 + x5*y0) - (x1*y0 + x5*y1 + x0*y5));
    int d3 = ((x3*y2 + x2*y4 + x4*y3) - (x2*y3 + x4*y2 + x3*y4));

    int i = 0;
  
    while (d1 + d2 + d3 < area)
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

      d1 = ((x1*y2 + x2*y4 + x4*y5 + x5*y1) - (x2*y1 + x4*y2 + x5*y4 + x1*y5)) / 2;
      d3 = ((x3*y2 + x2*y4 + x4*y3) - (x2*y3 + x4*y2 + x3*y4)) / 2;
      d2 = ((x0*y1 + x1*y5 + x5*y0) - (x1*y0 + x5*y1 + x0*y5)) / 2;

      if (d2 < 0)
        d2 *= (-1);

      if (d3 < 0)
        d3 *= (-1);

      if (d1 < 0)
        d1 *= (-1);

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
*/

  return h;
}

void display(house *h)
{ 
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINE_STRIP);

  if (h->bedroom1 != NULL)
  {
    print_lines_vertices(h->bedroom1->list_vertex);
    print_lines_vertices(h->bedroom1->bathroom->list_vertex);
  }
  
  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);

  if (h->bedroom2 != NULL)
  {
    print_lines_vertices(h->bedroom2->list_vertex);
    print_lines_vertices(h->bedroom2->bathroom->list_vertex);
  }
  
  glEnd();
  glFlush();
  

  glBegin(GL_LINE_STRIP);

  if (h->bedroom != NULL)
  {
    print_lines_vertices(h->bedroom->list_vertex);
    print_lines_vertices(h->bedroom->closet->list_vertex);
  }
  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);

  if (h->gym_room != NULL)
    print_lines_vertices(h->gym_room->list_vertex);
  
  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);

  if (h->dining_room_with_kitchen != NULL)
  {
    print_lines_vertices(h->dining_room_with_kitchen->list_vertex);
    print_lines_vertices(h->dining_room_with_kitchen->kitchen->list_vertex);
  }
  
  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);
  
  if (h->living_room != NULL)
    print_lines_vertices(h->living_room->list_vertex);
  
  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);
  
  if (h->social_bathroom != NULL)
    print_lines_vertices(h->social_bathroom->list_vertex);
  
  glEnd();
  glFlush();

  glBegin(GL_LINE_STRIP);
  
  if (h->area != NULL)
    print_lines_vertices(h->area);
  
  glEnd();
  glFlush();
  
  glBegin(GL_LINE_STRIP);
  
  if (h->service_area != NULL)
    print_lines_vertices(h->service_area->list_vertex);
  
  glEnd();
  glFlush();

}

int main(int argc, char **argv)
{
  int area;

  while (1)
  {
    printf("Digite a area da casa (area >= 135000 && area <= 250000): ");
    scanf("%d", &area);
    
    if(area >= 130000 && area <= 250000)
      break;

    printf("Valor da area nao esta no intervalo.\n\n");
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(MAX_SIZE_WINDOW, MAX_SIZE_WINDOW);
  glutInitWindowPosition(100, 0);
  glutCreateWindow("Planta baixa de casa");
  gluOrtho2D(0.0, MAX_SIZE_WINDOW, 0.0, MAX_SIZE_WINDOW);

  house *h = build_house(area, 1);
  display(h);
  
  glutMainLoop();

  return 0;
}
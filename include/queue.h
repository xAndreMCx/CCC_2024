#pragma once
#include "lawn.h"

typedef struct node_s {
  int x;
  int y;
  lawn_matrix_t* lawn_matrix;
  direction_t* directions;
  struct node_s* next;
} node_t;

typedef struct {
  node_t* front;
  node_t* rear;
} queue_t;

queue_t* create_queue();
void free_queue(queue_t* queue);
void enqueue(queue_t* queue, int x, int y, lawn_matrix_t* lawn_matrix);
node_t* dequeue(queue_t* queue);
bool queue_is_empty(queue_t* queue);

node_t* create_node(int x, int y, lawn_matrix_t* lawn_matrix);
void free_node(node_t* node);

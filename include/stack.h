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
  node_t* top;
} stack_t;

stack_t* create_stack();
void free_stack(stack_t* stack);
void stack_push(stack_t* stack, int x, int y, lawn_matrix_t* lawn_matrix);
node_t* stack_pop(stack_t* stack);
bool stack_is_empty(stack_t* stack);

node_t* create_node(int x, int y, lawn_matrix_t* lawn_matrix);
void free_node(node_t* node);

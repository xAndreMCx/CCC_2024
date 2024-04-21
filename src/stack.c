#include "stack.h"

#include <stdlib.h>

stack_t* create_stack() {
  stack_t* stack = malloc(sizeof(stack_t));
  stack->top = NULL;
  return stack;
}

void free_stack(stack_t* stack) {
  while (!stack_is_empty(stack)) {
    node_t* node = stack_pop(stack);
    free_node(node);
  }
  free(stack);
}

void stack_push(stack_t* stack, int x, int y, lawn_matrix_t* lawn_matrix) {
  node_t* node = create_node(x, y, lawn_matrix);
  node->next = stack->top;
  stack->top = node;
}

node_t* stack_pop(stack_t* stack) {
  node_t* node = stack->top;
  stack->top = stack->top->next;
  return node;
}

bool stack_is_empty(stack_t* stack) { return stack->top == NULL; }

node_t* create_node(int x, int y, lawn_matrix_t* lawn_matrix) {
  node_t* node = malloc(sizeof(node_t));
  node->x = x;
  node->y = y;
  node->lawn_matrix = lawn_matrix;
  node->next = NULL;
  return node;
}

void free_node(node_t* node) {
  free_lawn_matrix(node->lawn_matrix);
  free(node);
}
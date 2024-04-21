#include "path.h"

#include <stdlib.h>

#include "stack.h"

path_t lawn_matrix_check_direction(lawn_matrix_t* lawn_matrix, int* x, int* y, direction_t direction) {
  direction_go(x, y, direction);
  // Checks if it is out of bounds
  if ((*x < 0) || (*x >= (int)lawn_matrix->width) || (*y < 0) || (*y >= (int)lawn_matrix->height)) {
    if (lawn_matrix->directions_length == lawn_matrix->max_directions_length) {
      return PATH_VALID;
    }
    return PATH_INVALID;
  }

  // Checks if it is a tree
  if (lawn_matrix->matrix[*y][*x]) {
    if (lawn_matrix->directions_length == lawn_matrix->max_directions_length) {
      return PATH_VALID;
    }
    return PATH_INVALID;
  }
  return PATH_INCOMPLETE;
}

char* generate_path(lawn_t* lawn) {
  stack_t* stack = create_stack();
  lawn_matrix_t* lawn_matrix = lawn_matrix_populate(lawn);
  stack_push(stack, 0, 0, lawn_matrix_copy(lawn_matrix));
  while (!stack_is_empty(stack)) {
    node_t* node = stack_pop(stack);
    for (direction_t direction = 0; direction < TOTAL_DIRECTIONS; direction++) {
      int x = node->x;
      int y = node->y;
      path_t path = lawn_matrix_check_direction(node->lawn_matrix, &x, &y, direction);
      switch (path) {
        case PATH_VALID: {
          char* p = directions_to_string(node->lawn_matrix->directions, node->lawn_matrix->directions_length);
          free_node(node);
          free_lawn_matrix(lawn_matrix);
          free_stack(stack);
          return p;
        }
        case PATH_INVALID:
          continue;
        case PATH_INCOMPLETE: {
          lawn_matrix_t* copy = lawn_matrix_copy(node->lawn_matrix);
          copy->matrix[y][x] = true;
          lawn_matrix_append_direction(copy, direction);
          stack_push(stack, x, y, copy);
          break;
        }
      }
    }
    free_node(node);
  }
  free_stack(stack);
  free_lawn_matrix(lawn_matrix);
  return NULL;
}
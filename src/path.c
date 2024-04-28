#include "path.h"

#include <stdlib.h>

path_t lawn_matrix_check(lawn_matrix_t* lawn_matrix) {
  if (lawn_matrix->directions_length == lawn_matrix->max_directions_length) {
    return PATH_VALID;
  }
  return PATH_INVALID;
}

path_t lawn_matrix_check_direction(lawn_matrix_t* lawn_matrix, int* x, int* y, direction_t direction) {
  direction_go(x, y, direction);
  // Checks if it is out of bounds
  if ((*x < 0) || (*x >= (int)lawn_matrix->width) || (*y < 0) || (*y >= (int)lawn_matrix->height)) {
    return PATH_INVALID;
  }

  // Checks if it is a tree or already visited
  if (lawn_matrix->matrix[*y][*x]) {
    return PATH_INVALID;
  }

  return PATH_INCOMPLETE;
}

char* generate_path(lawn_t* lawn) {
  lawn_matrix_t* lawn_matrix = lawn_matrix_populate(lawn);
  char* path = malloc((lawn_matrix->max_directions_length + 1) * sizeof(char));
  if (path == NULL) {
    fprintf(stderr, "Error: Unable to allocate memory for path\n");
    free_lawn_matrix(lawn_matrix);
    return NULL;
  }

  generate_path_recursive(lawn_matrix, 0, 0, path, 0);
  free_lawn_matrix(lawn_matrix);
  return path;
}

bool generate_path_recursive(lawn_matrix_t* lawn_matrix, int x, int y, char* path, int path_length) {
  if (lawn_matrix_check(lawn_matrix) == PATH_VALID) {
    path[path_length] = '\0';
    return true;
  }

  for (direction_t direction = 0; direction < TOTAL_DIRECTIONS; direction++) {
    int x_copy = x;
    int y_copy = y;
    path_t path_status = lawn_matrix_check_direction(lawn_matrix, &x_copy, &y_copy, direction);
    if (path_status == PATH_INVALID) {
      continue;
    }
    // lawn_matrix_t* copy = lawn_matrix_copy(lawn_matrix);
    lawn_matrix->matrix[y_copy][x_copy] = true;
    lawn_matrix->directions_length++;
    path[path_length] = direction_to_char(direction);
    if (generate_path_recursive(lawn_matrix, x_copy, y_copy, path, path_length + 1)) {
      return true;
    }
    path[path_length] = '_';
    lawn_matrix->matrix[y_copy][x_copy] = false;
    lawn_matrix->directions_length--;
  }
  return false;
}
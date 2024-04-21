#include "lawn.h"

#include <stdlib.h>
#include <string.h>

lawn_t* create_lawn(const unsigned int width, const unsigned int height) {
  lawn_t* lawn = malloc(sizeof(lawn_t));
  lawn->width = width;
  lawn->height = height;
  lawn->lawn = malloc(height * sizeof(char*));
  for (unsigned int i = 0; i < height; i++) {
    lawn->lawn[i] = malloc((width + 1) * sizeof(char));
    memset(lawn->lawn[i], 0, width + 1);
  }
  return lawn;
}

lawn_t* extract_lawn(FILE* file) {
  unsigned int lawn_width, lawn_height;
  fscanf(file, "%d %d", &lawn_width, &lawn_height);

  lawn_t* lawn = create_lawn(lawn_width, lawn_height);
  for (unsigned int y = 0; y < lawn_height; y++) {
    fscanf(file, "%s", lawn->lawn[y]);
  }
  return lawn;
}

lawn_t** extract_lawns(FILE* file, const unsigned int num_lawns) {
  lawn_t** lawns = malloc(num_lawns * sizeof(lawn_t*));
  for (unsigned int i = 0; i < num_lawns; i++) {
    lawns[i] = extract_lawn(file);
  }
  return lawns;
}

void free_lawn(lawn_t* lawn) {
  for (unsigned int i = 0; i < lawn->height; i++) {
    free(lawn->lawn[i]);
  }
  free(lawn->lawn);
  free(lawn);
}

lawn_matrix_t* create_lawn_matrix(const unsigned int width, const unsigned int height) {
  lawn_matrix_t* matrix = malloc(sizeof(lawn_matrix_t));
  matrix->width = width;
  matrix->height = height;
  matrix->directions = malloc((width * height) * sizeof(direction_t));
  matrix->directions_length = 0;
  matrix->max_directions_length = width * height - 2;
  matrix->matrix = malloc(height * sizeof(bool*));

  for (unsigned int i = 0; i < height; i++) {
    matrix->matrix[i] = malloc(width * sizeof(bool));
    memset(matrix->matrix[i], 0, width);
  }
  return matrix;
}

lawn_matrix_t* lawn_matrix_populate(lawn_t* lawn) {
  lawn_matrix_t* lawn_matrix = create_lawn_matrix(lawn->width, lawn->height);
  for (unsigned int y = 0; y < lawn->height; y++) {
    for (unsigned int x = 0; x < lawn->width; x++) {
      lawn_matrix->matrix[y][x] = (lawn->lawn[y][x] == '.') ? false : true;
    }
  }
  lawn_matrix->matrix[0][0] = true;
  return lawn_matrix;
}

lawn_matrix_t* lawn_matrix_copy(lawn_matrix_t* lawn_matrix) {
  lawn_matrix_t* copy = create_lawn_matrix(lawn_matrix->width, lawn_matrix->height);
  copy->directions_length = lawn_matrix->directions_length;
  copy->max_directions_length = lawn_matrix->max_directions_length;
  for (unsigned int direction = 0; direction < lawn_matrix->directions_length; direction++) {
    copy->directions[direction] = lawn_matrix->directions[direction];
  }

  for (unsigned int y = 0; y < lawn_matrix->height; y++) {
    for (unsigned int x = 0; x < lawn_matrix->width; x++) {
      copy->matrix[y][x] = lawn_matrix->matrix[y][x];
    }
  }

  return copy;
}

void lawn_matrix_print(lawn_matrix_t* lawn_matrix) {
  printf("[\n");
  for (unsigned int y = 0; y < lawn_matrix->height; y++) {
    for (unsigned int x = 0; x < lawn_matrix->width; x++) {
      printf("%d ", lawn_matrix->matrix[y][x]);
    }
    printf("\n");
  }
  printf("]\n");
}

void lawn_matrix_append_direction(lawn_matrix_t* lawn_matrix, direction_t direction) {
  if (lawn_matrix->directions_length > lawn_matrix->max_directions_length) {
    fprintf(stderr, "Cannot append more directions\n");
    return;
  }
  lawn_matrix->directions[lawn_matrix->directions_length] = direction;
  lawn_matrix->directions_length++;
}

void free_lawn_matrix(lawn_matrix_t* lawn_matrix) {
  for (unsigned int i = 0; i < lawn_matrix->height; i++) {
    free(lawn_matrix->matrix[i]);
  }
  free(lawn_matrix->matrix);
  free(lawn_matrix->directions);
  free(lawn_matrix);
}

void direction_go(int* x, int* y, direction_t direction) {
  switch (direction) {
    case DIRECTION_UP:
      (*y)--;
      break;
    case DIRECTOIN_RIGHT:
      (*x)++;
      break;
    case DIRECTOIN_DOWN:
      (*y)++;
      break;
    case DIRECTOIN_LEFT:
      (*x)--;
      break;
  }
}

char* directions_to_string(direction_t* directions, unsigned int length) {
  char* string = malloc((length + 1) * sizeof(char));
  for (unsigned int i = 0; i < length; i++) {
    switch (directions[i]) {
      case DIRECTION_UP:
        string[i] = 'W';
        break;
      case DIRECTOIN_RIGHT:
        string[i] = 'D';
        break;
      case DIRECTOIN_DOWN:
        string[i] = 'S';
        break;
      case DIRECTOIN_LEFT:
        string[i] = 'A';
        break;
    }
  }
  string[length] = '\0';
  return string;
}

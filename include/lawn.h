#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef enum { DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_UP } direction_t;
#define TOTAL_DIRECTIONS 4


typedef struct {
  unsigned int width;
  unsigned int height;
  char** lawn;
} lawn_t;

typedef struct {
  unsigned int width;
  unsigned int height;
  unsigned int directions_length;
  unsigned int max_directions_length;
  bool** matrix;
} lawn_matrix_t;


lawn_t* create_lawn(const unsigned int width, const unsigned int height);
lawn_t* extract_lawn(FILE* file);
lawn_t** extract_lawns(FILE* file, const unsigned int num_lawns);
void free_lawn(lawn_t* lawn);

lawn_matrix_t* create_lawn_matrix(const unsigned int width, const unsigned int height);
lawn_matrix_t* lawn_matrix_populate(lawn_t* lawn);
lawn_matrix_t* lawn_matrix_copy(lawn_matrix_t* lawn_matrix);
void lawn_matrix_print(lawn_matrix_t* lawn_matrix);
void free_lawn_matrix(lawn_matrix_t* lawn_matrix);

void direction_go(int* x, int* y, direction_t direction);
char direction_to_char(direction_t direction);
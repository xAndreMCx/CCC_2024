#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef enum { DIRECTION_UP, DIRECTOIN_RIGHT, DIRECTOIN_DOWN, DIRECTOIN_LEFT } direction_t;
#define TOTAL_DIRECTIONS 4


typedef struct {
  unsigned int width;
  unsigned int height;
  char** lawn;
} lawn_t;

typedef struct {
  unsigned int width;
  unsigned int height;
  direction_t* directions;
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
void lawn_matrix_append_direction(lawn_matrix_t* lawn_matrix, direction_t direction);
void free_lawn_matrix(lawn_matrix_t* lawn_matrix);

void direction_go(int* x, int* y, direction_t direction);
char* directions_to_string(direction_t* directions, unsigned int length);
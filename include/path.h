#pragma once
#include "lawn.h"

typedef enum { PATH_VALID, PATH_INVALID, PATH_INCOMPLETE } path_t;

path_t lawn_matrix_check(lawn_matrix_t* lawn_matrix);
path_t lawn_matrix_check_direction(lawn_matrix_t* lawn_matrix, int* x, int* y, direction_t direction);
char* generate_path(lawn_t* lawn);
bool generate_path_recursive(lawn_matrix_t* lawn_matrix, int x, int y, char* path, int path_length);
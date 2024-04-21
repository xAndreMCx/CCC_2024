#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lawn.h"
#include "path.h"

int main(int argc, const char** argv) {
  if (argc != 3) {
    printf("Usage: %s <input_file> <output_file>\n", argv[0]);
    return 1;
  }
  const char* input_file_path = argv[1];
  const char* output_file_path = argv[2];

  FILE* file_input = fopen(input_file_path, "r");
  if (file_input == NULL) {
    printf("Could not open file %s\n", input_file_path);
    return 1;
  }

  unsigned int num_lawns = 0;
  fscanf(file_input, "%d\n", &num_lawns);
  lawn_t** lawns = extract_lawns(file_input, num_lawns);
  fclose(file_input);

  FILE* file_output = fopen(output_file_path, "w");
  if (file_output == NULL) {
    printf("Could not open file %s\n", output_file_path);
    return 1;
  }
  for (unsigned int i = 0; i < num_lawns; i++) {
    char* path = generate_path(lawns[i]);
    if (path == NULL) {
      fprintf(stderr, "Case #%d: IMPOSSIBLE\n", i + 1);
      continue;
    }
    fprintf(file_output, "%s\n", path);
    free(path);
  }
  fclose(file_output);
  for (unsigned int i = 0; i < num_lawns; i++) {
    free_lawn(lawns[i]);
  }
  free(lawns);

  printf("Output written to %s\n", output_file_path);
  return 0;
}

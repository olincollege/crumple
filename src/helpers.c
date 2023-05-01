#include "helpers.h"

#include <stdio.h>   // perror
#include <stdlib.h>  // exit, EXIT_FAILURE

void error_and_exit(const char* error_msg) {
  perror(error_msg);
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  exit(EXIT_FAILURE);
}

tile* get_collapsed_tile(matrix* cells, coords loc) {
  cell* collapsed_cell = &cells->array[loc.x][loc.y];

  if (collapsed_cell->entropy != 1) {
    error_and_exit("Tried to get tile from non-collapsed cell");
  }
  
  for (size_t i = 0; i < cells->num_tiles; i++) {
    if (collapsed_cell->possibilities[i] != NULL) {
      return collapsed_cell->possibilities[i];
    }
  }

  error_and_exit("No possibilities were found");
}

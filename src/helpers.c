#include "helpers.h"

#include <stddef.h>
#include <stdio.h>   // perror
#include <stdlib.h>  // exit, EXIT_FAILURE

void error_and_exit(const char* error_msg) {
  printf("ERROR in function: %s at line %d\n", __func__, __LINE__);
  perror(error_msg);
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  exit(EXIT_FAILURE);
}

tile* get_collapsed_tile(matrix* cells, coords loc) {
  cell* collapsed_cell = &cells->array[loc.y][loc.x];

  if (collapsed_cell->entropy != 1) {
    error_and_exit("Tried to get tile from non-collapsed cell\n");
  }

  for (size_t i = 0; i < cells->num_tiles; i++) {
    if (collapsed_cell->possibilities[i] != NULL) {
      return collapsed_cell->possibilities[i];
    }
  }

  error_and_exit("No possibilities were found\n");
}

cell** make_cell_array(size_t height, size_t width, size_t num_tiles,
                       tile** tile_possibilities) {
  cell** cells = malloc(sizeof(cell*) * height);
  for (size_t i = 0; i < height; i++) {
    cells[i] = malloc(sizeof(cell) * width);
    for (size_t j = 0; j < width; j++) {
      cell* cell_ = make_cell(tile_possibilities, num_tiles);
      cells[i][j] = *cell_;
    }
  }
  return cells;
}

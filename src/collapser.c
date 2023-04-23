#include "collapser.h"

coords find_lowest_entropy(matrix* cells, size_t num_tiles) {
  coords lowest_loc = {.x = 0, .y = 0};
  size_t lowest_entropy = num_tiles;
  for (size_t col = 0; col < cells->width; col++) {
    for (size_t row = 0; row < cells->height; row++) {
      if (cells->array[col][row].entropy < lowest_entropy) {
        lowest_loc.x = col;
        lowest_loc.y = row;
      }
    }
  }

  return lowest_loc;
}
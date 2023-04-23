#include "collapser.h"

coords find_lowest_entropy(matrix* cells, size_t num_tiles) {
  coords lowest_loc = {.x = 0, .y = 0};
  size_t lowest_entropy = num_tiles;
  //NOLINTBEGIN(readability-identifier-length)
  for (size_t x = 0; x < cells->width; x++) {
    for (size_t y = 0; y < cells->height; y++) {
      if (cells->array[x][y].entropy < lowest_entropy) {
        lowest_loc.x = x;
        lowest_loc.y = y;
      }
    }
  }

  //NOLINTEND(readability-identifier-length)
  return lowest_loc;
}
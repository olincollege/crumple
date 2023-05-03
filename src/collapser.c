#include "collapser.h"
#include "helpers.h"

coords find_lowest_entropy(matrix* cells) {
  coords lowest_loc = {.x = 0, .y = 0};
  size_t lowest_entropy = cells->num_tiles;
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

void update_neighbors(matrix* cells, coords loc) {
  tile* self_tile = get_collapsed_tile(cells, loc);

  for (size_t dir = 0; dir < 4; dir++) {
    // make sure we're not looking out of bounds
    int x_diff = X_OFFSET[dir];
      // potential ulong underflow error -- deal with this
    if (loc.x + x_diff < 0 || loc.x + x_diff > cells->width) { continue; }
    
    int y_diff = Y_OFFSET[dir];
    if (loc.y + y_diff < 0 || loc.y + y_diff > cells->height) { continue; }

    // define the edge to check on the neighbor-tile
    size_t check_dir = (dir + 2) % 4;

    cell* neighbor = &cells->array[loc.x + x_diff][loc.y + y_diff];

    for (size_t poss_num = 0; poss_num < cells->num_tiles; poss_num++) {
      // check if the tile is possible or not
      if (neighbor->possibilities + poss_num == NULL) { continue; }

      tile* check_tile = neighbor->possibilities[poss_num];
      if (check_tile->edges[check_dir] != self_tile->edges[dir]) {
        neighbor->possibilities[poss_num] = NULL;
      }
    }
  }
}
#include "collapser.h"
#include "helpers.h"

coords find_lowest_entropy(matrix* cells) {
  coords lowest_loc = {.x = 0, .y = 0};
  size_t lowest_entropy = cells->num_tiles;
  for (size_t row = 0; row < cells->height; row++) {
    for (size_t col = 0; col < cells->width; col++) {
      if (cells->array[row][col].entropy <= lowest_entropy && cells->array[row][col].entropy != 1) {
        lowest_loc.y = row;
        lowest_loc.x = col;
      }
    }
  }

  return lowest_loc;
}

coords collapse_lowest_entropy(matrix *cells, unsigned int* seed) {
  coords lowest_loc = find_lowest_entropy(cells);

  printf("attempting to collapse cell at (%zu, %zu)\n", lowest_loc.x, lowest_loc.y);
  cell* collapse_cell = &cells->array[lowest_loc.y][lowest_loc.x];
  printf("found cell with with entropy of %zu\n", collapse_cell->entropy);

  if (collapse_cell->entropy == 0) {
    error_and_exit("Attempt to modulate by zero\n");
  }
  int selected_tile = rand_r(seed) % (int) collapse_cell->entropy;
  int valid_tile_num = 0;

  printf("selected random tile %d out of %zu\n", selected_tile, collapse_cell->entropy);

  for (int i = 0; i < cells->num_tiles; i++) {
    if (collapse_cell->possibilities[i] != NULL) {
      if (valid_tile_num != selected_tile) {
        collapse_cell->possibilities[i] = NULL;
      }

      valid_tile_num++;
    }
  }

  collapse_cell->entropy = 1;
  return lowest_loc;
}

void update_neighbors(matrix* cells, coords loc) {
  tile* self_tile = get_collapsed_tile(cells, loc);

  for (size_t dir = 0; dir < 4; dir++) {
    // make sure we're not looking out of bounds
    int x_diff = X_OFFSET[dir];
      // potential ulong underflow error -- deal with this
    if (loc.x == 0 && x_diff < 0) { continue; }
    if (loc.x + x_diff >= cells->width) { continue; }
    
    int y_diff = Y_OFFSET[dir];
    if (loc.y == 0 && y_diff < 0) { continue; }
    if (loc.y + y_diff >= cells->height) { continue; }

    // define the edge to check on the neighbor-tile
    size_t check_dir = (dir + 2) % 4;

    printf("(%zu, %zu) checking neighbor (%zu, %zu)\n", loc.x, loc.y, loc.x+x_diff, loc.y+y_diff);
    cell* neighbor = &cells->array[loc.y + y_diff][loc.x + x_diff];

    for (size_t poss_num = 0; poss_num < cells->num_tiles; poss_num++) {
      // check if the tile is possible or not
      if (neighbor->possibilities[poss_num] == NULL) { continue; }

      tile* check_tile = neighbor->possibilities[poss_num];
      if (check_tile->edges[check_dir] != self_tile->edges[dir]) {
        neighbor->possibilities[poss_num] = NULL;
        neighbor->entropy -= 1;
      }
    }
  }
}

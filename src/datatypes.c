#include "datatypes.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

tile* make_tile(FILE* image_file, size_t rotation, edge_t* edges_) {
  tile* tile_ = malloc(sizeof(tile));
  tile_->image = image_file;
  tile_->rotation = rotation;
  tile_->edges = edges_;
  return tile_;
}

int free_tile(tile* tile_) {
  free(tile_->edges);
  free(tile_);
  return 0;
}

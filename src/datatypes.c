#include "datatypes.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

edge_t* make_edges(char* all_edges, size_t rotation) {
  char rotated[4];
  memcpy(rotated + rotation, all_edges, 4 - rotation);
  memcpy(rotated, all_edges + 4 - rotation, rotation);
  edge_t edges = {rotated};
  return &edges;
}

#include <stdio.h>

#include "parser.h"

int main(void) {
  size_t tiles_len = 0;
  tile** tiles = generate_tiles("src/input.yaml", &tiles_len);
  for (size_t j = 0; j < tiles_len; j++) {
    printf("%s\n", tiles[j]->edges);
  }
}

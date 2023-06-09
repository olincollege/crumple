#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "collapser.h"
#include "datatypes.h"
#include "helpers.h"
#include "imgen.h"
#include "parser.h"

unsigned int seed = 111111;

static char* handle_args(int argc, char* argv[]) {
  if (argc != 2) {
    error_and_exit("invalid number of args passed");
  }
  return argv[1];
}

int main(int argc, char* argv[]) {
  char* config_file = handle_args(argc, argv);
  printf("%s\n", config_file);
  matrix* mat = generate_matrix(config_file);
  for (size_t j = 0; j < mat->num_tiles; j++) {
    printf("Edges: %s\n", mat->all_tiles[j]->edges);
    printf("Image filepath: %s\n", mat->all_tiles[j]->image);
  }
  for (size_t a = 0; a < mat->height; a++) {
    for (size_t b = 0; b < mat->width; b++) {
      printf("ypos: %zu, xpos: %zu, entropy: %zu\n", a, b,
             mat->array[a][b].entropy);
    }
  }
  // parse yaml
  // generate matrix struct
  // printf("%zu",mat->array[3][0].entropy);

  printf("height:%zu\n width:%zu\nnumtiles: %zu\n", mat->height, mat->width,
         mat->num_tiles);
  while (1) {
    size_t ced = 1;
    for (size_t xloc = 0; xloc < mat->width; ++xloc) {
      for (size_t yloc = 0; yloc < mat->height; ++yloc) {
        if (mat->array[yloc][xloc].entropy != 1) {
          ced = 0;
        }
      }
    }
    printf("CHECKED ALL CELLS\n");
    if (ced != 1) {
      printf("matrix not collapsed. repeating...\n");
      coords c_low_ent = collapse_lowest_entropy(mat, &seed);
      printf("collapsed (%zu,%zu) to %s rotated %zu times\n", c_low_ent.x, c_low_ent.y, get_collapsed_tile(mat, c_low_ent)->image, get_collapsed_tile(mat, c_low_ent)->rotation);
      printf("updating neighbors to (%zu, %zu)\n", c_low_ent.x, c_low_ent.y);
      update_neighbors(mat, c_low_ent);
    } else {
      break;
    }
  }
  make_output(mat);
}

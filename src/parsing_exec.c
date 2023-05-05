#include <stdio.h>

#include "parser.h"

int main(void) {
  matrix* matrix_ = generate_matrix("legit_images.yaml");
  for (size_t j = 0; j < matrix_->num_tiles; j++) {
    printf("Edges: %s\n", matrix_->all_tiles[j]->edges);
    printf("Image filepath: %s\n", matrix_->all_tiles[j]->image);
  }
  for (size_t a = 0; a < matrix_->height; a++) {
    for (size_t b = 0; b < matrix_->width; b++) {
      printf("ypos: %zu, xpos: %zu, entropy: %zu\n", a, b,
             matrix_->array[a][b].entropy);
    }
  }
}

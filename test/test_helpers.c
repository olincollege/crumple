#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/helpers.h"
#include "../src/parser.h"

Test(get_collapsed_tile, simple_success) {
  // honestly this could easily be a test of generate_matrix too...
  printf("\n");
  matrix* test_matrix = generate_matrix("../../test/test_yamls/two_no.yaml");

  // "collapse" the tile we care about
  test_matrix->array[1][1].entropy = 1;
  for (size_t i = 1; i < test_matrix->num_tiles; i++) {
    test_matrix->array[1][1].possibilities[i] = NULL;
  }

  coords test_tile_coords = {.x = 1, .y = 1};
  tile* test_tile = get_collapsed_tile(test_matrix, test_tile_coords);

  cr_assert_str_eq(test_tile->image, "blank.png");
}
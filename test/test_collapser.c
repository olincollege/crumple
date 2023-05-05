#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/collapser.h"
#include "../src/parser.h"

Test(find_lowest_entropy, skip_entropy_of_one) {
  printf("\n");
  matrix* test_matrix = generate_matrix("../../test/test_yamls/two_all.yaml");

  for (size_t row = 0; row < test_matrix->height; row++) {
    for (size_t col = 0; col < test_matrix->width; col++) {
      if (row != 1 && col != 1) {
        test_matrix->array[col][row].entropy = 1;
      }
    }
  }

  cr_assert_eq(find_lowest_entropy(test_matrix).x, 1);
  cr_assert_eq(find_lowest_entropy(test_matrix).y, 1);
}

Test(find_lowest_entropy, multiple_equal_entropies) {
  printf("\n");
  matrix* test_matrix = generate_matrix("../../test/test_yamls/two_all.yaml");

  for (size_t col = 0; col < test_matrix->height; col++) {
    for (size_t row = 0; row < test_matrix->width; row++) {
      if (row != col) {
        test_matrix->array[col][row].entropy = 1;
      }
    }
  }

  coords lowest = find_lowest_entropy(test_matrix);

  cr_assert_eq(lowest.x, 2);
  cr_assert_eq(lowest.y, 2);
}

Test(collapse_lowest_entropy, successfully_collapse) {
  printf("\n");
  matrix* test_matrix = generate_matrix("../../test/test_yamls/two_no.yaml");

  for (size_t col = 0; col < test_matrix->height; col++) {
    for (size_t row = 0; row < test_matrix->width; row++) {
      if (row != 1 && col != 1) {
        test_matrix->array[col][row].entropy = 1;
      }
    }
  }

  //NOLINTNEXTLINE(*-magic-numbers)
  unsigned int seed = 111;
  coords lowest = collapse_lowest_entropy(test_matrix, &seed);
  cell* collapsed_cell = &test_matrix->array[lowest.y][lowest.x];

  cr_assert_eq(lowest.x, 1);
  cr_assert_eq(lowest.y, 1);
  cr_assert_eq(collapsed_cell->entropy, 1);
  cr_assert_str_eq(get_collapsed_tile(test_matrix, lowest)->image, "blank.png");
}

Test(update_neighbors, edge_case) {
  printf("\n");
  matrix* test_matrix = generate_matrix("../../test/test_yamls/two_no.yaml");

  // "collapse" the tile we care about
  test_matrix->array[0][2].entropy = 1;
  test_matrix->array[0][2].possibilities[1] = NULL;
  test_matrix->array[0][2].possibilities[2] = NULL;

  coords test_tile_coords = {.x = 0, .y = 2};
  update_neighbors(test_matrix, test_tile_coords);

  // since we remove a tile that has 'c' as the bottom edge
  // this cell cannot be the tile that has 'c' as the top edge
  cell* updated_cell = &test_matrix->array[1][2];

  cr_assert_eq(updated_cell->entropy, 2);
  cr_assert_eq(updated_cell->possibilities[2], NULL);
}

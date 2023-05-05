#include <criterion/criterion.h>
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
  matrix* test_matrix = generate_matrix("../../test/test_yamls/one_90.yaml");

  test_matrix->array[1][1].entropy = 1;

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

  cr_assert_eq(lowest.x, 1);
  cr_assert_eq(lowest.y, 1);
  cr_assert_eq(test_matrix->array[1][1].entropy, 1);
}

Test(collapse_lowest_entropy, edge_case) {
  printf("\n");
  matrix* test_matrix = generate_matrix("../../test/test_yamls/two_all.yaml");

  for (size_t col = 0; col < test_matrix->height; col++) {
    for (size_t row = 0; row < test_matrix->width; row++) {
      if (row != col) {
        test_matrix->array[col][row].entropy = 1;
      }
    }
  }

  cr_assert_eq(find_lowest_entropy(test_matrix).x, 2);
  cr_assert_eq(find_lowest_entropy(test_matrix).y, 2);
}

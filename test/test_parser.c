#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/parser.h"

/**
 * NOTE: The tests crash when the name is too long or the filename is too long,
 * I'm not sure why. The test and file names have accordingly been heavily
 * abbreviated, with clarifying comments above each test
 */

/**
 * Checking: the correct number of tiles are generated
 * Input: No tile configurations provided
 */
Test(generate_matrix, num_tiles_no_conf) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/no_configs.yaml");
  size_t expected = 0;
  cr_assert_eq(expected, mat->num_tiles);
}

/**
 * Checking: the correct number of tiles are generated
 * Input: One configuration provided, no rotations allowed
 */
Test(generate_matrix, num_one_no) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/one_no.yaml");
  size_t expected = 1;
  cr_assert_eq(expected, mat->num_tiles);
}

/**
 * Checking: the correct number of tiles are generated
 * Input: One configuration provided, 90 degree rotations allowed
 */
Test(generate_matrix, num_one_90) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/one_90.yaml");
  size_t expected = 3;
  cr_assert_eq(expected, mat->num_tiles);
}

/**
 * Checking: the correct number of tiles are generated
 * Input: One configuration provided, 180 degree rotations allowed
 */
Test(generate_matrix, num_one_180) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/one_180.yaml");
  // printf("b\n");
  size_t expected = 2;
  cr_assert_eq(expected, mat->num_tiles);
}

/**
 * Checking: the correct number of tiles are generated
 * Input: One configuration provided, all rotations allowed
 */
Test(generate_matrix, num_one_all) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/one_all.yaml");
  size_t expected = 4;
  cr_assert_eq(expected, mat->num_tiles);
}

/**
 * Checking: the correct number of tiles are generated
 * Input: Two configurations provided, no degree rotations allowed
 */
Test(generate_matrix, num_two_no) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/two_no.yaml");
  size_t expected = 2;
  cr_assert_eq(expected, mat->num_tiles);
}

/**
 * Checking: the correct number of tiles are generated
 * Input: Two configurations provided, all degree rotations allowed
 */
Test(generate_matrix, num_two_all) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/two_all.yaml");
  size_t expected = 8;
  cr_assert_eq(expected, mat->num_tiles);
}

/**
 * Checking: rotations are all done correctly
 * Input: One "aabb" configuration tile is provided
 */
Test(generate_matrix, aabb_one) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/one_all.yaml");
  for (size_t i = 0; i < mat->num_tiles; i++) {
    printf("edges for tile no. %zu: %s\n", i, mat->all_tiles[i]->edges);
  }
  size_t expected = 9;
  cr_assert_eq(expected, mat->num_tiles);
}

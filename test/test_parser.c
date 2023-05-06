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
  char* expected_edges[4];
  expected_edges[0] = "aabb";
  expected_edges[1] = "abba";
  expected_edges[2] = "baab";
  expected_edges[3] = "bbaa";

  for (size_t i = 0; i < mat->num_tiles; i++) {
    char* exp_edg = expected_edges[i];
    char* actual_edg = mat->all_tiles[i]->edges;
    cr_assert_str_eq(exp_edg, actual_edg);
  }
}

/**
 * Checking: image name is generated correctly
 * Input: Two tiles with different image names are provided
 */
Test(generate_matrix, two_ims) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/two_no.yaml");
  char* expected_im_paths[2];
  expected_im_paths[0] = "../../test/test_img/blank.png";
  expected_im_paths[1] = "../../test/test_img/tile1.png";
  for (size_t i = 0; i < mat->num_tiles; i++) {
    printf("i: %zu\n", i);
    char* exp_im_path = expected_im_paths[i];
    char* actual_im_path = mat->all_tiles[i]->image;
    cr_assert_str_eq(exp_im_path, actual_im_path);
  }
}

Test(generate_matrix, corr_height) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/two_no.yaml");
  size_t exp_height = 10;
  size_t actual_height = mat->height;
  cr_assert_eq(exp_height, actual_height);
}

Test(generate_matrix, corr_width) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/two_no.yaml");
  size_t exp_width = 12;
  size_t actual_width = mat->width;
  cr_assert_eq(exp_width, actual_width);
}

Test(generate_matrix, array_not_null) {
  printf("\n");
  matrix* mat = generate_matrix("../../test/test_yamls/two_no.yaml");
  size_t expected_entropy = mat->num_tiles;
  for (size_t i = 0; i < mat->height; i++) {
    for (size_t j = 0; j < mat->width; j++) {
      size_t actual_entropy = mat->array[i][j].entropy;
      cr_assert_eq(expected_entropy, actual_entropy);
    }
  }
}

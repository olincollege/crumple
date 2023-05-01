#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/parser.h"

Test(generate_tiles, no_conf) {
  size_t num_gen = 0;
  size_t expected_num_gen = 0;
  generate_tiles("../../test/test_yamls/no_configs.yaml", &num_gen);
  cr_assert_eq(expected_num_gen, num_gen);
}

Test(generate_tiles, one_conf_no_rot) {
  size_t num_gen = 0;
  size_t expected_num_gen = 1;
  tile** tiles = generate_tiles("../../test/test_yamls/one_no.yaml", &num_gen);
  cr_assert_eq(expected_num_gen, num_gen);
}

Test(generate_tiles, one_conf_90_rot) {
  size_t num_gen = 0;
  size_t expected_num_gen = 3;
  tile** tiles = generate_tiles("../../test/test_yamls/one_90.yaml", &num_gen);
  cr_assert_eq(expected_num_gen, num_gen);
}

Test(generate_tiles, one_conf_180_rot) {
  size_t num_gen = 0;
  size_t expected_num_gen = 2;
  tile** tiles = generate_tiles("../../test/test_yamls/one_180.yaml", &num_gen);
  cr_assert_eq(expected_num_gen, num_gen);
}

Test(generate_tiles, one_conf_all_rot) {
  size_t num_gen = 0;
  size_t expected_num_gen = 4;
  tile** tiles = generate_tiles("../../test/test_yamls/one_all.yaml", &num_gen);
  cr_assert_eq(expected_num_gen, num_gen);
}

Test(generate_tiles, two_conf_no_rot) {
  size_t num_gen = 0;
  size_t expected_num_gen = 2;
  generate_tiles("../../test/test_yamls/two_no.yaml", &num_gen);
  cr_assert_eq(expected_num_gen, num_gen);
}

Test(generate_tiles, two_conf_all_rot) {
  size_t num_gen = 0;
  size_t expected_num_gen = 8;
  generate_tiles("../../test/test_yamls/two_all.yaml", &num_gen);
  cr_assert_eq(expected_num_gen, num_gen);
}

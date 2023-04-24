#include "parser.h"

#include "helpers.h"

char*** get_text_split_sections(FILE* input_yaml_file) {}

int* parse_rules(char** rules_text) {}

char* parse_imdir(char** image_location_text) {}

char*** parse_tile_section(char** tile_text, int* num_tile_configs) {}

char** parse_individual_tile_config_textblock(char** tile_config_text,
                                              char* image_location) {}

tile** generate_tile_rotations(char* edges_, int* rules, char* im_name,
                               size_t* num_generated) {
  FILE* image_file = fopen(im_name, "r");
  size_t arr_index = 0;
  size_t num_rots = 1 + rules[0] * 2 + rules[1];
  tile** tiles = malloc(sizeof(tile*) * num_rots);
  edge_t* rot_0_edges = make_edges(edges_, 0);
  tiles[arr_index] = make_tile(image_file, 0, rot_0_edges);
  ++arr_index;
  if (rules[0]) {  // 90 degree rotations
    edge_t* rot_1_edges = make_edges(edges_, 1);
    tiles[arr_index] = make_tile(image_file, 0, rot_1_edges);
    ++arr_index;
    edge_t* rot_3_edges = make_edges(edges_, 3);
    tiles[arr_index] = make_tile(image_file, 0, rot_3_edges);
    ++arr_index;
  }
  if (rules[1]) {  // 180 degree rotations
    edge_t* rot_2_edges = make_edges(edges_, 2);
    tiles[arr_index] = make_tile(image_file, 0, rot_2_edges);
  }
  return tiles;
}

tile** add_to_tile_pointer_array(tile** current_array, size_t num_added_tiles,
                                 tile** array_to_add, size_t* curr_len) {
  tile** updated_array =
      realloc(current_array, sizeof(tile*) * (*curr_len + num_added_tiles));
  for (size_t i = 0; i < num_added_tiles; i++) {
    updated_array[*curr_len + i] = array_to_add[i];
  }
  *curr_len += num_added_tiles;
  free(array_to_add);
  return updated_array;
}

tile** generate_tiles(char* input_yaml_filename) {
  FILE* input_yaml = fopen(input_yaml_filename, "r");
  char*** sectioned_text = get_text_split_sections(input_yaml);
  int* rules = parse_rules(sectioned_text[0]);
  char* im_location = parse_imdir(sectioned_text[1]);
  int tile_config_num = 0;
  char*** tile_config_blocks =
      parse_tile_section(sectioned_text[2], &tile_config_num);
  char** parsed_tile_config;
  tile** tiles_from_config;
  size_t num_gen;
  tile** tiles = malloc(sizeof(tile*));
  size_t tiles_len = 0;
  for (int i = 0; i < tile_config_num; i++) {
    parsed_tile_config = parse_individual_tile_config_textblock(
        tile_config_blocks[i], im_location);

    tiles_from_config = generate_tile_rotations(parsed_tile_config[0], rules,
                                                im_location, num_gen);
    tiles =
        add_to_tile_pointer_array(tiles, num_gen, tiles_from_config, tiles_len);
  }
}

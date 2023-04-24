#include "parser.h"

char*** get_text_split_sections(FILE* input_yaml_file) {}

int* parse_rules(char** rules_text) {}

char* parse_imdir(char** image_location_text) {}

char*** parse_tile_section(char** tile_text, int* num_tile_configs) {}

char** parse_individual_tile_config_textblock(char** tile_config_text,
                                              char* image_location) {}

tile** generate_tile_rotations(char* edges_, int* rules, char* im_name,
                               size_t* num_generated) {}

tile** add_to_tile_pointer_array(tile** current_array, size_t num_added_tiles,
                                 tile** array_to_add, size_t* curr_len) {
  current_array =
      realloc(current_array, sizeof(tile*) * (*curr_len + num_added_tiles));
  for (size_t i = 0; i < num_added_tiles; i++) {
    current_array[*curr_len + i] = array_to_add[i];
  }
  *curr_len += num_added_tiles;
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

#include "parser.h"

split_yaml* get_text_split_sections(FILE* input_yaml_file) {}

int* parse_rules_section(char** rules_text) {}

char* parse_im_location_section(char** image_location_text) {
  char* line = image_location_text[0];
  while (line) {
    if (strncmp(line, YAML_IM_LOCATION_START, strlen(YAML_IM_LOCATION_START)) ==
        0) {
      size_t im_location_line_len = (size_t)strlen(line);
      size_t image_dir_len =
          im_location_line_len - strlen(YAML_IM_LOCATION_START);
      char* im_location =
          malloc(sizeof(char) *
                 (image_dir_len + 2));  // +1 for "/", +1 for null termination
      strncpy(im_location, *(line) + strlen(YAML_IM_LOCATION_START),
              im_location_line_len - strlen(YAML_IM_LOCATION_START));
      strncpy(im_location + image_dir_len, "/",
              2);  // should result in null termination
    } else {
      ++line;
    }
  }
  // should have hit the image_location line before getting to the end of the
  // text, error and exit here
}

tile_textblock** add_to_tile_textblock_array(tile_textblock** current_array,
                                             tile_textblock* block_to_add,
                                             size_t* curr_len) {
  tile_textblock** updated_array =
      realloc(current_array, sizeof(tile_textblock*) * (*curr_len + 1));

  memcpy(updated_array[*curr_len], block_to_add);
  *curr_len++;
  free_tile_textblock(block_to_add);
  return updated_array;
}

tile_textblock** parse_tiles_section(char** tile_text,
                                     size_t* num_tile_configs) {
  tile_textblock** tile_textblock_arr = malloc(sizeof(tile_textblock*));
  char* line = tile_text[0];
  while (line) {
    if (*line == YAML_TILE_START) {
      // throw some logic in here to check that the lines we're putting into
      // this textblock are right format, error if not
      tile_textblock* textblock = make_tile_textblock(*(line + 1), *(line + 2));
      tile_textblock_arr = add_to_tile_textblock_array(
          tile_textblock_arr, textblock, num_tile_configs);
      line += 3;
    } else {
      ++line;
    }
  }
  return tile_textblock_arr;
}

parsed_tile_textblock* parse_individual_tile_config_textblock(
    tile_textblock* textblock, char* image_location) {
  parsed_tile_textblock* parsed_block =
      make_parsed_tile_textblock(textblock, image_location);
  free_tile_textblock(textblock);
  return parsed_block;
}

tile** generate_tile_rotations(parsed_tile_textblock* parsed_block, int* rules,
                               size_t* num_generated) {
  FILE* image_file = fopen(parsed_block->im_name, "r");
  size_t arr_index = 0;
  size_t num_rots = 1 + rules[0] * 2 + rules[1];
  tile** tiles = malloc(sizeof(tile*) * num_rots);
  edge_t* rot_0_edges = make_edges(parsed_block->edges, 0);
  tiles[arr_index] = make_tile(image_file, 0, rot_0_edges);
  ++arr_index;
  if (rules[0]) {  // 90 degree rotations
    edge_t* rot_1_edges = make_edges(parsed_block->edges, 1);
    tiles[arr_index] = make_tile(image_file, 0, rot_1_edges);
    ++arr_index;
    edge_t* rot_3_edges = make_edges(parsed_block->edges, 3);
    tiles[arr_index] = make_tile(image_file, 0, rot_3_edges);
    ++arr_index;
  }
  if (rules[1]) {  // 180 degree rotations
    edge_t* rot_2_edges = make_edges(parsed_block->edges, 2);
    tiles[arr_index] = make_tile(image_file, 0, rot_2_edges);
  }
  return tiles;
}

tile** add_to_tile_pointer_array(tile** current_array, size_t num_added_tiles,
                                 tile** array_to_add, size_t* curr_len) {
  tile** updated_array =
      realloc(current_array, sizeof(tile*) * (*curr_len + num_added_tiles));
  for (size_t i = 0; i < num_added_tiles; i++) {
    memcpy(updated_array[*curr_len + i], array_to_add[i]);
  }
  *curr_len += num_added_tiles;
  free(array_to_add);
  return updated_array;
}

tile** generate_tiles(char* input_yaml_filename) {
  FILE* input_yaml = fopen(input_yaml_filename, "r");
  split_yaml* sectioned_yaml = get_text_split_sections(input_yaml);
  int* rules = parse_rules(sectioned_yaml->rules_section);
  char* im_location = parse_imdir(sectioned_yaml->imdir_section);
  int tile_config_num = 0;
  tile_textblock** tile_config_blocks =
      parse_tile_section(sectioned_yaml->tiles_section, &tile_config_num);
  parsed_tile_textblock* parsed_tile;
  tile** tiles_from_config;
  size_t num_gen;
  tile** tiles = malloc(sizeof(tile*));
  size_t tiles_len = 0;
  for (int i = 0; i < tile_config_num; i++) {
    parsed_tile = parse_individual_tile_config_textblock(tile_config_blocks[i],
                                                         im_location);

    tiles_from_config = generate_tile_rotations(parsed_tile, rules, num_gen);
    tiles =
        add_to_tile_pointer_array(tiles, num_gen, tiles_from_config, tiles_len);
  }
}

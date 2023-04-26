#include "parser.h"

split_yaml* get_text_split_sections(FILE* input_yaml_file) {
  char** rules_section = malloc(sizeof(char*) * MAX_YAML_RULES_SECTION_LINES);
  char** imdir_section =
      malloc(sizeof(char*) * MAX_YAML_IM_LOCATION_SECTION_LINES);
  char** tiles_section = malloc(sizeof(char*) * MAX_YAML_TILES_SECTION_LINES);
  char buffer[MAX_YAML_LINE_LENGTH];
  size_t line_count = 0;
  size_t line_count_in_arr = 0;
  char** active_section = NULL;
  while (fgets(buffer, MAX_YAML_LINE_LENGTH, input_yaml_file) != NULL &&
         line_count < MAX_YAML_NUM_LINES) {
    size_t line_length = (size_t)strlen(buffer);
    if (line_length == 1) {
      line_count++;
      continue;
    }
    if (strncmp(buffer, YAML_RULES_HEADER, strlen(YAML_RULES_HEADER)) == 0) {
      active_section = rules_section;
      line_count_in_arr = 0;
    } else if (strncmp(buffer, YAML_IM_LOCATION_HEADER,
                       strlen(YAML_IM_LOCATION_HEADER)) == 0) {
      active_section = imdir_section;
      line_count_in_arr = 0;
    } else if (strncmp(buffer, YAML_TILES_HEADER, strlen(YAML_TILES_HEADER)) ==
               0) {
      active_section = tiles_section;
      line_count_in_arr = 0;
    } else if (strncmp(buffer, YAML_END_MARKER, strlen(YAML_END_MARKER)) == 0) {
      break;
    } else if (active_section != NULL) {
      active_section[line_count_in_arr] =
          (char*)malloc(line_length * sizeof(char));
      strncpy(active_section[line_count_in_arr], buffer, line_length + 1);
      active_section[line_count_in_arr][line_length - 1] = '\0';
      line_count_in_arr++;
    }
    line_count++;
  }
  split_yaml* split_yaml_ =
      make_split_yaml(rules_section, imdir_section, tiles_section);
  return split_yaml_;
}

int* parse_rules_section(char** rules_text) {
  size_t index = 0;
  char* line = rules_text[0];
  int* rules = malloc(sizeof(int) * NUM_RULES);
  for (size_t i = 0; i < NUM_RULES; i++) {
    rules[i] = -1;
  }
  while (line) {
    if (strncmp(line, YAML_180_DEGREE_RULE_START,
                strlen(YAML_180_DEGREE_RULE_START)) == 0) {
      if (strncmp(line + strlen(YAML_180_DEGREE_RULE_START), YAML_TRUE_VAL,
                  strlen(YAML_TRUE_VAL)) == 0) {
        rules[1] = 1;
      } else if (strncmp(line + strlen(YAML_180_DEGREE_RULE_START),
                         YAML_FALSE_VAL, strlen(YAML_FALSE_VAL)) == 0) {
        rules[1] = 0;
      } else {
        error_and_exit("error parsing 180 degree rule value");
      }
    } else if (strncmp(line, YAML_90_DEGREE_RULE_START,
                       strlen(YAML_90_DEGREE_RULE_START)) == 0) {
      if (strncmp(line + strlen(YAML_90_DEGREE_RULE_START), YAML_TRUE_VAL,
                  strlen(YAML_TRUE_VAL)) == 0) {
        rules[0] = 1;
      } else if (strncmp(line + strlen(YAML_90_DEGREE_RULE_START),
                         YAML_FALSE_VAL, strlen(YAML_FALSE_VAL)) == 0) {
        rules[0] = 0;
      } else {
        error_and_exit("error parsing 90 degree rule value");
      }
    }
    ++index;
    line = rules_text[index];
  }
  for (size_t i = 0; i < NUM_RULES; i++) {
    if (rules[i] == -1) {
      error_and_exit("one or more rules is unset");
    }
  }
  return rules;
  // if both values are set, return the array
  // else error and exit
}

char* parse_im_location_section(char** image_location_text) {
  size_t index = 0;
  char* line = image_location_text[0];
  while (line) {
    if (strncmp(line, YAML_IM_LOCATION_START, strlen(YAML_IM_LOCATION_START)) ==
        0) {
      size_t im_location_line_len = (size_t)strlen(line);
      size_t image_dir_len = im_location_line_len -
                             strlen(YAML_IM_LOCATION_START) -
                             2;  //-2 to take off quotes
      char* im_location =
          malloc(sizeof(char) * (image_dir_len + 1 +
                                 1));  // +1 for "/", +1 for null termination,
      strncpy(im_location, line + strlen(YAML_IM_LOCATION_START) + 1,
              im_location_line_len - strlen(YAML_IM_LOCATION_START));
      strncpy(im_location + image_dir_len, "/\0",
              2);  // should result in null termination
      return im_location;
    }
    ++index;
    line = image_location_text[index];
  }
  // should have hit the image_location line before getting to the end of the
  // text, error and exit here
  return NULL;
}

tile_textblock** add_to_tile_textblock_array(tile_textblock** current_array,
                                             tile_textblock* block_to_add,
                                             size_t* curr_len) {
  tile_textblock** updated_array =
      realloc(current_array, sizeof(tile_textblock*) * (*curr_len + 1));
  updated_array[*curr_len] = block_to_add;
  (*curr_len)++;
  // need to free the memory in the tile_textblock array
  return updated_array;
}

tile_textblock** parse_tiles_section(char** tile_text,
                                     size_t* num_tile_configs) {
  tile_textblock** tile_textblock_arr = malloc(sizeof(tile_textblock*));
  size_t index = 0;
  char* line = tile_text[index];

  while (line) {
    if (strncmp(line, YAML_TILE_START, strlen(YAML_TILE_START)) == 0) {
      // throw some logic in here to check that the lines we're putting into
      // this textblock are right format, error if not
      tile_textblock* textblock =
          make_tile_textblock(tile_text[index + 1], tile_text[index + 2]);
      tile_textblock_arr = add_to_tile_textblock_array(
          tile_textblock_arr, textblock, num_tile_configs);
      index += 3;
    } else {
      ++index;
    }
    line = tile_text[index];
  }
  return tile_textblock_arr;
}

parsed_tile_textblock* parse_individual_tile_config_textblock(
    tile_textblock* textblock, char* image_location) {
  size_t initial_im_name_line_length = strlen(textblock->im_name_line);
  size_t core_im_filename_length = initial_im_name_line_length -
                                   strlen(YAML_TILE_IM_NAME_START) -
                                   2;  // -2 for quotes
  size_t im_dir_length = strlen(image_location);
  size_t total_im_path_len =
      im_dir_length + core_im_filename_length + 1;  // +1 for null term
  char* im_name_ = malloc(sizeof(char*) * total_im_path_len);
  strncpy(im_name_, image_location, im_dir_length);
  strncpy(im_name_ + im_dir_length,
          textblock->im_name_line + 1 + strlen(YAML_TILE_IM_NAME_START),
          core_im_filename_length);
  strncpy(im_name_ + total_im_path_len, "\0", 1);
  char* edges_ = malloc(sizeof(char) * EDGES_CHAR_ARRAY_LEN);
  strncpy(edges_, textblock->edges_line + 1 + strlen(YAML_TILE_EDGES_START),
          NUM_EDGES);
  strncpy(edges_ + strlen(YAML_TILE_EDGES_START) - 1, "\0", 1);

  parsed_tile_textblock* parsed_block =
      make_parsed_tile_textblock(im_name_, edges_);

  // free_tile_textblock(textblock);
  return parsed_block;
}

tile** generate_tile_rotations(parsed_tile_textblock* parsed_block, int* rules,
                               size_t* num_generated) {
  FILE* image_file = fopen(parsed_block->im_name, "re");
  size_t arr_index = 0;
  size_t num_rots = 1 + (size_t)rules[0] * 2 + (size_t)rules[1];
  tile** tiles = malloc(sizeof(tile*) * num_rots);
  // edge_t* rot_0_edges = make_edges(parsed_block->edges, 0);
  edge_t* rot_0_edges =
      make_edges(parsed_block->edges);  // may need to switch to the above when
                                        // new make_edges gets merged in
  tiles[arr_index] = make_tile(image_file, 0, rot_0_edges);
  ++arr_index;
  ++*num_generated;
  if (rules[0]) {  // 90 degree rotations
                   // edge_t* rot_1_edges = make_edges(parsed_block->edges, 1);
    edge_t* rot_1_edges = make_edges(parsed_block->edges);

    tiles[arr_index] = make_tile(image_file, 0, rot_1_edges);
    ++arr_index;
    // edge_t* rot_3_edges = make_edges(parsed_block->edges, 3);
    edge_t* rot_3_edges = make_edges(parsed_block->edges);

    tiles[arr_index] = make_tile(image_file, 0, rot_3_edges);
    ++arr_index;
    *num_generated += 2;
  }
  if (rules[1]) {  // 180 degree rotations
                   // edge_t* rot_2_edges = make_edges(parsed_block->edges, 2);
    edge_t* rot_2_edges = make_edges(parsed_block->edges);
    tiles[arr_index] = make_tile(image_file, 0, rot_2_edges);
    ++*num_generated;
  }
  free_parsed_tile_textblock(parsed_block);
  return tiles;
}

tile** add_to_tile_pointer_array(tile** current_array, size_t num_added_tiles,
                                 tile** array_to_add, size_t* curr_len) {
  tile** updated_array =
      realloc(current_array, sizeof(tile*) * (*curr_len + num_added_tiles));
  for (size_t i = 0; i < num_added_tiles; i++) {
    memcpy(updated_array[*curr_len + i], array_to_add[i], sizeof(tile*));
  }
  *curr_len += num_added_tiles;
  free(array_to_add);
  return updated_array;
}

tile** generate_tiles(char* input_yaml_filename) {
  FILE* input_yaml = fopen(input_yaml_filename, "re");
  split_yaml* sectioned_yaml = get_text_split_sections(input_yaml);
  int* rules = parse_rules_section(
      sectioned_yaml->rules_section);  // untested also unfinished
  char* im_location = parse_im_location_section(sectioned_yaml->imdir_section);
  size_t tile_config_num = 0;
  tile_textblock** tile_config_blocks =
      parse_tiles_section(sectioned_yaml->tiles_section, &tile_config_num);
  parsed_tile_textblock* parsed_tile;
  tile** tiles_from_config;
  size_t num_gen = 0;
  tile** tiles = malloc(sizeof(tile*));
  size_t tiles_len = 0;
  for (size_t i = 0; i < tile_config_num; i++) {
    parsed_tile = parse_individual_tile_config_textblock(tile_config_blocks[i],
                                                         im_location);

    tiles_from_config =
        generate_tile_rotations(parsed_tile, rules, &num_gen);  // untested
    tiles = add_to_tile_pointer_array(tiles, num_gen, tiles_from_config,
                                      &tiles_len);  // untested
    free_parsed_tile_textblock(parsed_tile);
  }
  free(im_location);
  free(rules);  // gotta valgrind all this shit
  return tiles;
}

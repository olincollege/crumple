#include <stdio.h>

#include "parser.h"

int main(void) {
  FILE* input_yaml = fopen("src/input.yaml", "re");
  split_yaml* sectioned_yaml = get_text_split_sections(input_yaml);
  int* rules = parse_rules_section(sectioned_yaml->rules_section);
  char* im_location = parse_im_location_section(sectioned_yaml->imdir_section);
  size_t tile_config_num = 0;
  tile_textblock** tile_config_blocks =
      parse_tiles_section(sectioned_yaml->tiles_section, &tile_config_num);
  parsed_tile_textblock* parsed_tile;
  tile** tiles_from_config;
  size_t num_gen = 0;
  tile** tiles = malloc(sizeof(tile*));
  size_t tiles_len = 0;
  printf("a\n");
  for (size_t i = 0; i < tile_config_num; i++) {
    printf("b\n");

    parsed_tile = parse_individual_tile_config_textblock(tile_config_blocks[i],
                                                         im_location);
    printf("parsed tile edges: %s\n", parsed_tile->edges);
    printf("parsed tile im_name: %s\n", parsed_tile->im_name);

    printf("c\n");

    tiles_from_config =
        generate_tile_rotations(parsed_tile, rules, &num_gen);  // untested
    // generate_tile_rotations is def fucked up, needs some tlc
    printf("edges: %s\n", tiles_from_config[0]->edges);
    printf("im_pointer: %p\n", tiles_from_config[0]->image);

    printf("d\n");

    // tiles = add_to_tile_pointer_array(tiles, num_gen, tiles_from_config,
    //                                   &tiles_len);  // untested
    // printf("b\n");

    // free_parsed_tile_textblock(parsed_tile);
  }
  free(im_location);
  free(rules);  // gotta valgrind all this shit
}

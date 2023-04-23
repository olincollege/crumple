#include "parser.h"

char*** get_text_split_sections(FILE* input_yaml_file) {}

int* parse_rules(char** rules_text) {}

char* parse_imdir(char** image_location_text) {}

char*** parse_tile_section(char** tile_text, int* num_tile_configs) {}

char** parse_individual_tile_config_textblock(char** tile_config_text) {}

tile** generate_tile_rotations(char* edges_, int* rules, char* im_name,
                               size_t* num_generated) {}

tile** add_to_tile_array(tile** current_array, size_t num_added_tiles,
                         tile** array_to_add) {}

tile** generate_tiles(char* input_yaml_filename) {}

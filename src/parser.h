#pragma once

#include "datatypes.h"

/**
 * Generate tiles from a user submitted yaml input file
 *
 * Given the name of a user submitted yaml file, generate an array of tile
 * struct pointers corresponding to the tiles specified by the input yaml. The
 * parsing is brittle and requires precise formatting. If the tile generation is
 * not successful, error and exit without returning and provide the user as much
 * insight as possible as to why the parsing fails.
 *
 * @param input_yaml_filename The name of the yaml file (or path to it including
 * name)
 *
 * @return The array of tile pointers generated from the yaml
 */
tile* generate_tiles(char* input_yaml_filename);

#pragma once

#include <string.h>

#include "helpers.h"

enum { MAX_YAML_LINE_LENGTH = 64 };
enum { MAX_YAML_NUM_LINES = 1024 };
enum { MAX_YAML_DIMENSIONS_SECTION_LINES = 10 };
enum { MAX_YAML_RULES_SECTION_LINES = 10 };
enum { MAX_YAML_IM_LOCATION_SECTION_LINES = 10 };
enum { MAX_YAML_TILES_SECTION_LINES = 1000 };
enum { NUM_YAML_FILE_SECTIONS = 3 };  // rules, image location, tiles
enum {
  NUM_RULES = 2
};  // allow 90 degree rotations, allow 180 degree
    // rotations

/**
 * Get the text from the input yaml file
 *
 * Given the pointer to the user submitted yaml file, generate a split_yaml
 * struct containing the rules section, imdir section, and tiles sections of the
 * input.
 *
 * Errors and returns nothing if the file is not found, or if the text splitting
 * fails (specifies in error message which).
 *
 * @param input_yaml_file The pointer to the file object representing the input
 * yaml
 *
 * @return The pointer to the split_yaml struct containing the contents of the
 * input yaml split into sections
 */
split_yaml* get_text_split_sections(FILE* input_yaml_file);

/**
 * Parses the "rules" section of the input text.
 *
 * Given the pointer to the rules text, determine the status of the rules
 * (currently if 90 and 180 degree rotations are allowed). Return an array of
 * ints corresponding to the rule statuses.
 *
 * The values in the return array correspond to:
 * [0]: 90 degree rotations
 * [1]: 180 degree rotations
 *
 * Errors and returns nothing if the rules parsing fails (specifies as much as
 * possible in the error message what went wrong).
 *
 * @param rules_text The block of text containing the rules input, no trailing
 * empty lines after it.
 *
 * @return An array of ints corresponding to rules statuses
 */
int* parse_rules_section(char** rules_text);

/**
 * Parses the "image location" section of the input text.
 *
 * Given the pointer to the image location text, determine the location of the
 * images. Return a string corresponding to that location, with a trailing
 * forward slash.
 *
 * Errors and returns nothing if the image location parsing fails (specifies as
 * much as possible in the error message what went wrong).
 *
 * @param image_location_text The section of the text containing the image
 * location text, no trailing lines after it.
 *
 * @return The string corresponding to the location of the images with a
 * trailing forward slash.
 */
char* parse_im_location_section(char** image_location_text);

/**
 * Adds a tile_textblock to a tile textblock pointer array and updates the
 * length of that array.
 *
 * Given an array of tile textblock pointers, a tile texblock pointer to add,
 * and a size_t containing the current length of that array, add the textblock
 * pointer, update the length, deal with resizing the current array and free the
 * memory of the textblock added.
 */
tile_textblock** add_to_tile_textblock_array(tile_textblock** current_array,
                                             tile_textblock* block_to_add,
                                             size_t* curr_len);

/**
 * Parses the "tiles" section of the input text.
 *
 * Given the pointer to the tiles text and an int pointer to be written to,
 * split the tiles text into tile_textblock structs, each of which contain the
 * lines of text corresponding to one tile, unprocessed except for adding a null
 * terminator. Also set num_tile_configs to the number of such tile_textblock
 * structs generated.
 *
 * Errors and returns nothing if the tile section parsing fails (specifies as
 * much as possible in the error message what went wrong).
 *
 * @param tile_text The section of text containing the tiles text.
 * @param num_tile_configs An size_t pointer to be written to with the number of
 * "tile configs"/blocks this function creates
 *
 * @return An array of tile_textblocks pointers, each of the tile_textblocks
 * containing the lines of text from the section of the yaml corresponding to
 * the tile.
 */
tile_textblock** parse_tiles_section(char** tile_text,
                                     size_t* num_tile_configs);

/**
 * Parses a configuration textblock for a tile as returned from
 * parse_tile_section.
 *
 * Given the pointer to an unparsed tile textblock, parse the lines of content
 * and generate a corresponding parsed tile texblock. Frees the input unparsed
 * tile textblock.
 *
 * Errors and returns nothing if the tile parsing fails (specifies as
 * much as possible in the error message what went wrong).
 *
 * @param textblock The pointer to the textblock struct containing the lines
 * from the input yaml file corresponding to the given tile
 * @param image_location The directory (with trailing forward slash) containing
 * the images
 *
 * @return The pointer to the generated parsed tile textblock
 */
parsed_tile_textblock* parse_individual_tile_config_textblock(
    tile_textblock* textblock, char* image_location);

/**
 * Creates tile struct(s) for the given edges based on the defined rules.
 *
 * Creates an array of tile pointers, number depending on rules. All tiles
 * generated by a call of this function have the same im_name and same set of
 * edges (but rotated). Frees the input parsed tile textblock.
 *
 * Errors and returns nothing if the tile generation fails (specifies as
 * much as possible in the error message what went wrong).
 *
 * @param parsed_block The parsed tile textblock containing the information
 * about the tile (currently edges and im_name)
 * @param rules The rules to be followed while generating tiles (such as whether
 * or not rotations are allowed)
 * @param num_generated Written to, the number of tiles this function generates
 *
 * @return An array of tile pointers, generated from the input edges, rules, and
 * image name
 */
tile** generate_tile_rotations(parsed_tile_textblock* parsed_block, int* rules,
                               size_t* num_generated);

/**
 * Add an array of tile pointers to an existing array of tile structs.
 *
 * Extend the array and add the new tile pointers to the end. Also update the
 * variable storing the length of the array. Frees the array that is added.
 *
 * @param current_array The array to extend
 * @param num_added_tiles The number of tiles being added to the array
 * @param array_to_add The array being added to the end of the existing one
 * @param curr_len The current length of current_array, gets updated
 *
 * @return The updated tile array
 */
tile** add_to_tile_pointer_array(tile** current_array, size_t num_added_tiles,
                                 tile** array_to_add, size_t* curr_len);

/**
 * Generates a matrix of cells and their possibilities from the input yaml file
 * name
 *
 * Open and read the contents of the file corresponding to the input filename.
 * Parse out the rules, dimensions, image location, and tile configurations, use
 * those to generate an array of tile pointers corresponding to all the tiles
 * generated for the given configuration and rules. Pack that all up into the
 * starter matrix collapser uses. Wrapper around all other parser functions.
 *
 * @param input_yaml_filename The name of the yaml file (or path to it including
 * name)
 *
 * @return The pointer to the matrix generated from the input yaml.
 */
matrix* generate_matrix(char* input_yaml_filename);

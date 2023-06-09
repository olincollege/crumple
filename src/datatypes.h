#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { EDGES_CHAR_ARRAY_LEN = 5 };  // 4 + 1 for null pointer
enum { NUM_EDGES = 4 };
enum { NUM_DIMENSIONS = 2 };

static const char YAML_START_LINE[] = "---";
static const char YAML_DIMENSIONS_HEADER[] = "#dimensions";
static const char YAML_RULES_HEADER[] = "#rules";
static const char YAML_IM_LOCATION_HEADER[] = "#im_location";
static const char YAML_TILES_HEADER[] = "#tiles";
static const char YAML_END_MARKER[] = "#EOF";

static const char YAML_HEIGHT_DIMENSION_START[] = "height: ";
static const char YAML_WIDTH_DIMENSION_START[] = "width: ";

static const char YAML_90_DEGREE_RULE_START[] = "allow-90-degree-rotations: ";
static const char YAML_180_DEGREE_RULE_START[] = "allow-180-degree-rotations: ";
static const char YAML_TRUE_VAL[] = "true";
static const char YAML_FALSE_VAL[] = "false";

static const char YAML_IM_LOCATION_START[] = "im_location: ";

static const char YAML_TILE_START[] = "tile:";
static const char YAML_TILE_IM_NAME_START[] = " - im_name: ";
static const char YAML_TILE_EDGES_START[] = " - edges: ";

static const int X_OFFSET[] = {0, 1, 0, -1};
static const int Y_OFFSET[] = {1, 0, -1, 0};

typedef struct {
  size_t x;
  size_t y;

} coords;

typedef struct {
  char* image;
  size_t rotation;
  char* edges;

} tile;

typedef struct {
  size_t entropy;
  tile** possibilities;

} cell;

typedef struct {
  size_t height;
  size_t width;
  cell** array;
  size_t num_tiles;
  tile** all_tiles;

} matrix;

enum allocation_type { NO_ALLOCATION, SELF_ALLOCATED, STB_ALLOCATED };

typedef struct {
  int width;
  int height;
  int channels;
  size_t size;
  uint8_t* data;
  enum allocation_type allocation_;

} Image;

typedef struct {
  char** dimensions_section;
  char** rules_section;
  char** imdir_section;
  char** tiles_section;

} split_yaml;

typedef struct {
  char* im_name_line;
  char* edges_line;

} tile_textblock;

tile_textblock* make_tile_textblock(char* im_name_line_, char* edges_line_);

void free_tile_textblock(tile_textblock* tile_textblock_);

typedef struct {
  char* im_name;
  char* edges;

} parsed_tile_textblock;

parsed_tile_textblock* make_parsed_tile_textblock(char* im_name_, char* edges_);

void free_parsed_tile_textblock(parsed_tile_textblock* parsed_tile_textblock_);

int free_matrix(matrix* matp);

cell* make_cell(tile** tiles, size_t num_tiles);
// init entropy upon first cycle of main loop

matrix* make_matrix(cell** cells, size_t height, size_t width, size_t num_tiles,
                    tile** alltiles);

int free_cell(cell* cellp);

/**
 * Makes tile and does all the rotating of the edges
 */
tile* make_tile(char* image_file, size_t rotation, char* edges_orig);

int free_tile(tile* tile_);

split_yaml* make_split_yaml(char** dimensions_section_, char** rules_section_,
                            char** imdir_section_, char** tiles_section_);

int free_split_yaml(split_yaml* split_yaml_);

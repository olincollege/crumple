#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { EDGES_CHAR_ARRAY_LEN = 5 };  // 4 + 1 for null pointer

static const char YAML_START_LINE[] = "---";
static const char YAML_RULES_HEADER[] = "#rules";
static const char YAML_IM_LOCATION_HEADER[] = "#im_location";
static const char YAML_TILES_HEADER[] = "#tiles";
static const char YAML_END_MARKER[] = "#EOF";

static const char YAML_90_DEGREE_RULE_START[] = "allow-90-degree-rotations: ";
static const char YAML_180_DEGREE_RULE_START[] = "allow-180-degree-rotations: ";

static const char YAML_IM_LOCATION_START[] = "im_location: ";

static const char YAML_TILE_START[] = "tile:";
static const char YAML_TILE_IM_NAME_START[] = " - im_name: ";
static const char YAML_TILE_EDGES_START[] = " - edges: ";

typedef struct {
  size_t x;
  size_t y;

} coords;

typedef struct {
  size_t entropy;

} cell;

typedef struct {
  size_t height;
  size_t width;
  cell** array;

} matrix;

typedef struct {
  char* tile_edges;

} edge_t;

typedef struct {
  FILE* image;
  size_t rotation;
  edge_t* edges;
} tile;

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

parsed_tile_textblock* make_parsed_tile_textblock(tile_textblock* textblock_,
                                                  char* image_location);

void free_parsed_tile_textblock(parsed_tile_textblock* parsed_tile_textblock_);

int free_matrix(matrix* matp);

cell* make_cell(tile* tiles);
// init entropy upon first cycle of main loop

int free_cell(cell* cellp);

tile* make_tile(FILE* image_file, size_t rotation, edge_t* edges_);
// check if this is the correct way to change

int free_tile(tile* tile_);

edge_t* make_edges(char* all_edges);

split_yaml* make_split_yaml(char** rules_section_, char** imdir_section_,
                            char** tiles_section_);

int free_split_yaml(split_yaml* split_yaml_);
/**
 * "Rotate" an edge struct tile edges counter clockwise.
 *
 * Given a pointer to an edges struct and a rotation size_t, the program shifts
 * the char string left by the value of the rotation variable.
 *
 * @param *edges A pointer to the edges struct that will be manipulated.
 * @param rotation A size_t variable that defines the shift of chars in the
 * string.
 */
void rotate_edges(edge_t* edges, size_t rotation);

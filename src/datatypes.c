#include "datatypes.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* make_and_rotate_edges(char* edges, size_t rotation) {
  char* new_edges = malloc(sizeof(char) * NUM_EDGES);
  strncpy(new_edges, edges + rotation, NUM_EDGES - rotation);
  strncpy(new_edges + NUM_EDGES - rotation, edges, rotation);
  return new_edges;
}

tile_textblock* make_tile_textblock(char* im_name_line_, char* edges_line_) {
  tile_textblock* textblock = malloc(sizeof(tile_textblock));
  size_t im_name_line_length = strlen(im_name_line_) + 1;

  size_t edges_line_length = strlen(edges_line_) + 1;
  textblock->im_name_line = malloc(sizeof(char) * im_name_line_length);

  textblock->edges_line = malloc(sizeof(char) * edges_line_length);
  strncpy(textblock->im_name_line, im_name_line_, im_name_line_length);
  strncpy(textblock->edges_line, edges_line_, edges_line_length);
  return textblock;
}

void free_tile_textblock(tile_textblock* tile_textblock_) {
  free(tile_textblock_->edges_line);
  free(tile_textblock_->im_name_line);
  free(tile_textblock_);
}

parsed_tile_textblock* make_parsed_tile_textblock(char* im_name_,
                                                  char* edges_) {
  parsed_tile_textblock* parsed_textblock =
      malloc(sizeof(parsed_tile_textblock));
  char* block_edges = malloc(sizeof(char) * strlen(edges_));
  char* block_im_name = malloc(sizeof(char) * strlen(im_name_));
  strncpy(block_edges, edges_, strlen(edges_));
  strncpy(block_edges + strlen(edges_), "\0", 1);
  strncpy(block_im_name, im_name_, strlen(im_name_));
  strncpy(block_im_name + strlen(im_name_), "\0", 1);
  parsed_textblock->im_name = block_im_name;
  parsed_textblock->edges = block_edges;

  return parsed_textblock;
}

void free_parsed_tile_textblock(parsed_tile_textblock* parsed_tile_textblock_) {
  free(parsed_tile_textblock_->edges);
  free(parsed_tile_textblock_->im_name);
  free(parsed_tile_textblock_);
}

cell* make_cell(tile** tiles, size_t num_tiles) {
  cell* cell_ = malloc(sizeof(cell));
  cell_->entropy = num_tiles;
  tile** possp = malloc(sizeof(tile*) * num_tiles);
  for (size_t i = 0; i < num_tiles; ++i) {
    possp[i] = tiles[i];
  }
  cell_->possibilities = possp;
  return cell_;
}

tile* make_tile(char* image_file, size_t rotation, char* edges_orig) {
  tile* tile_ = malloc(sizeof(tile));
  char* tile_image = malloc((strlen(image_file) + 1) * sizeof(char));
  strncpy(tile_image, image_file, strlen(image_file));
  strncpy(tile_image + strlen(image_file), "\0", 1);
  tile_->image = tile_image;
  tile_->rotation = rotation;
  char* new_edges = make_and_rotate_edges(edges_orig, rotation);
  tile_->edges = new_edges;
  return tile_;
}

matrix* make_matrix(cell** cells, size_t height, size_t width, size_t num_tiles,
                    tile** alltiles) {
  matrix* matrix_ = malloc(sizeof(matrix));
  matrix_->array = cells;
  matrix_->height = height;
  matrix_->width = width;
  matrix_->all_tiles = alltiles;
  matrix_->num_tiles = num_tiles;

  return matrix_;
}

int free_tile(tile* tile_) {
  free(tile_->edges);
  free(tile_);
  return 0;
}

split_yaml* make_split_yaml(char** dimensions_section_, char** rules_section_,
                            char** imdir_section_, char** tiles_section_) {
  split_yaml* split_yaml_ = malloc(sizeof(split_yaml));
  split_yaml_->dimensions_section = dimensions_section_;
  split_yaml_->rules_section = rules_section_;
  split_yaml_->imdir_section = imdir_section_;
  split_yaml_->tiles_section = tiles_section_;
  return split_yaml_;
}

int free_split_yaml(split_yaml* split_yaml_) {
  free(split_yaml_->rules_section);
  free(split_yaml_->imdir_section);
  free(split_yaml_->tiles_section);
  free(split_yaml_);
  return 0;
}

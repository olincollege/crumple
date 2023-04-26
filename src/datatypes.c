#include "datatypes.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

edge_t* make_edges(char* all_edges) {
  char* edges_ = malloc(sizeof(char) * 4);
  edges_ = all_edges;
  edge_t* edges = malloc(sizeof(edge_t));
  edges->tile_edges = edges_;
  return edges;
}

void rotate_edges(edge_t* edges, size_t rotation) {
  char* temp = malloc(sizeof(char) * 4);
  memcpy(temp, edges->tile_edges, sizeof(char) * 4);
  memcpy(edges->tile_edges + rotation, edges->tile_edges, 4 - rotation);
  memcpy(edges->tile_edges, temp + 4 - rotation, rotation);
  free(temp);
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

parsed_tile_textblock* make_parsed_tile_textblock(tile_textblock* textblock_,
                                                  char* image_location) {
  parsed_tile_textblock* parsed_textblock = malloc(sizeof(parsed_textblock));
  size_t edges_len = EDGES_CHAR_ARRAY_LEN;
  size_t im_name_len = strlen(textblock_->im_name_line) +
                       strlen(image_location) -
                       strlen(YAML_TILE_IM_NAME_START) + 1;
  parsed_textblock->edges = malloc(sizeof(char) * edges_len);
  parsed_textblock->im_name = malloc(sizeof(char) * im_name_len);
  strncpy(parsed_textblock->edges,
          textblock_->edges_line + strlen(YAML_TILE_EDGES_START), edges_len);
  strncpy(parsed_textblock->im_name, image_location, strlen(image_location));
  strncpy(parsed_textblock->im_name + strlen(image_location),
          textblock_->im_name_line + strlen(YAML_TILE_IM_NAME_START),
          im_name_len);
  return parsed_textblock;
}

void free_parsed_tile_textblock(parsed_tile_textblock* parsed_tile_textblock_) {
  free(parsed_tile_textblock_->edges);
  free(parsed_tile_textblock_->im_name);
  free(parsed_tile_textblock_);
}

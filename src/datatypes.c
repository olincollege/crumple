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

parsed_tile_textblock* make_parsed_tile_textblock(char* im_name_,
                                                  char* edges_) {
  parsed_tile_textblock* parsed_textblock =
      malloc(sizeof(parsed_tile_textblock));
  char* block_edges = malloc(sizeof(char*) * strlen(edges_));
  char* block_im_name = malloc(sizeof(char*) * strlen(im_name_));
  block_edges = edges_;
  block_edges[strlen(edges_)] = '\0';
  block_im_name = im_name_;
  block_im_name[strlen(im_name_)] = '\0';
  parsed_textblock->im_name = block_im_name;
  parsed_textblock->edges = block_edges;

  return parsed_textblock;

  //   size_t edges_len = EDGES_CHAR_ARRAY_LEN;
  //   printf("3\n");
  //   char* size_t im_name_len =
  //       strlen(textblock_->im_name_line) + strlen(image_location) -
  //       strlen(YAML_TILE_IM_NAME_START) + 1 -
  //       2;  // +1 for null termination, -2 for removing quotes
  //   printf("im_name_len: %zu\n", im_name_len);
  //   printf("4\n");
  //   parsed_textblock->edges = malloc(sizeof(char) * edges_len);
  //   printf("5\n");
  //   parsed_textblock->im_name = malloc(sizeof(char) * im_name_len);
  //   printf("6\n");
  //   strncpy(parsed_textblock->edges,
  //           textblock_->edges_line + strlen(YAML_TILE_EDGES_START),
  //           edges_len);
  //   printf("7\n");
  //   strncpy(parsed_textblock->im_name, image_location,
  //   strlen(image_location)); printf("8\n"); strncpy(parsed_textblock->im_name
  //   + strlen(image_location),
  //           textblock_->im_name_line + strlen(YAML_TILE_IM_NAME_START),
  //           im_name_len);
  //   printf("9\n");
  //   return parsed_textblock;
}

void free_parsed_tile_textblock(parsed_tile_textblock* parsed_tile_textblock_) {
  free(parsed_tile_textblock_->edges);
  free(parsed_tile_textblock_->im_name);
  free(parsed_tile_textblock_);
}

tile* make_tile(FILE* image_file, size_t rotation, edge_t* edges_) {
  tile* tile_ = malloc(sizeof(tile));
  tile_->image = image_file;
  tile_->rotation = rotation;
  tile_->edges = edges_;
  return tile_;
}

int free_tile(tile* tile_) {
  free(tile_->edges);
  free(tile_);
  return 0;
}

split_yaml* make_split_yaml(char** rules_section_, char** imdir_section_,
                            char** tiles_section_) {
  split_yaml* split_yaml_ = malloc(sizeof(split_yaml));
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
}

#include "datatypes.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

edge_t* make_edges(char* all_edges) {
  char* edges_ = malloc(sizeof(char) * 4);
  strncpy(edges_, "\0\0\0\0", 4);
  edges_ = all_edges;
  edge_t* edges = malloc(sizeof(edge_t));
  edges->tile_edges = edges_;
  return edges;
}

void rotate_edges(char* edges, size_t rotation) {
  // char* new_tile_edges = malloc(sizeof(char) * NUM_EDGES);
  // strncpy(new_tile_edges, edges->tile_edges, 4);
  // printf("%s\n", new_tile_edges);
  // // strncpy(new_tile_edges, edges->tile_edges + rotation, NUM_EDGES -
  // // rotation); strncpy(new_tile_edges + NUM_EDGES - rotation,
  // // edges->tile_edges, rotation);

  // strncpy(edges->tile_edges, new_tile_edges + rotation, NUM_EDGES -
  // rotation); strncpy(edges->tile_edges + NUM_EDGES - rotation,
  // new_tile_edges, rotation); printf("a\n"); printf("%s\n",
  // edges->tile_edges); free(edges->tile_edges); printf("b\n");
  // edges->tile_edges = new_tile_edges;
  // printf("c\n");
}

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
  char* block_edges = malloc(sizeof(char*) * strlen(edges_));
  char* block_im_name = malloc(sizeof(char*) * strlen(im_name_));
  block_edges = edges_;
  block_edges[strlen(edges_)] = '\0';
  block_im_name = im_name_;
  block_im_name[strlen(im_name_)] = '\0';
  parsed_textblock->im_name = block_im_name;
  parsed_textblock->edges = block_edges;

  return parsed_textblock;
}

void free_parsed_tile_textblock(parsed_tile_textblock* parsed_tile_textblock_) {
  free(parsed_tile_textblock_->edges);
  free(parsed_tile_textblock_->im_name);
  free(parsed_tile_textblock_);
}

tile* make_tile(FILE* image_file, size_t rotation, char* edges_orig) {
  tile* tile_ = malloc(sizeof(tile));
  tile_->image = image_file;
  tile_->rotation = rotation;
  char* new_edges = make_and_rotate_edges(edges_orig, rotation);
  tile_->edges = new_edges;
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

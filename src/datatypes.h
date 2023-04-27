
#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {

  size_t x;
  size_t y;

} coords;

typedef struct {

  char tile_edges[4];

} edge_t;

typedef struct {

  char* img_name;
  size_t rotation;
  edge_t edges;
} tile;

typedef struct {

  size_t entropy;
  tile** possibilities;

} cell;

typedef struct {
  size_t height;
  size_t width;
  cell** array;

} matrix;

enum allocation_type {
    NO_ALLOCATION, SELF_ALLOCATED, STB_ALLOCATED
};

typedef struct {
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;
    enum allocation_type allocation_;
} Image;


int free_matrix(matrix* matp);

cell* make_cell(tile* tiles);
// init entropy upon first cycle of main loop

int free_cell(cell* cellp);

tile* make_tile(FILE* image_file, size_t rotation, edge_t* edges_);
// check if this is the correct way to change 

int free_tile(tile*);

edge_t* make_edges(char* all_edges);


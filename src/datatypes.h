
#pragma once

#include <stdio.h>

typedef struct {

  int x;
  int y;

} coords;

typedef struct {

  int entropy;

} cell;

typedef struct {
  size_t height;
  size_t width;
  cell** array;

} matrix;

typedef struct {

  char tile_edges[4];

} edge_t;

typedef struct {

  char* img_name = "";
  int rotation;
  edge_t edges;
} tile;


matrix* make_matrix(int width, int height);

int free_matrix(matrix* matp);

cell* make_cell(tile* tiles);
// init entropy upon first cycle of main loop

int free_cell(cell* cellp);

tile* make_tile(FILE* image_file, int rotation, edge_t* edges_);
// check if this is the correct way to change 

int free_tile(tile*);

edge_t* make_edges(char* all_edges);




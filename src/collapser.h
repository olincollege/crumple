#pragma once

#include "datatypes.h"
#include "helpers.h"

/* Find the non-collapsed cell with the lowest entropy in a matrix of cells.
* 
* Skips cells with one possibility (i.e. collapsed) because those are already
* determined.
* If multiple cells share the lowest non-one entropy, select the one with the
* highest row/column value.
* 
* @param cells The matrix of cells to be searched.
* @param num_tiles The number of tiles 
* @return The coordinates of the lowest-entropy non-collapsed tile in the input.
*/
coords find_lowest_entropy(matrix *cells, size_t num_tiles);

/* Given the coordinates to a collapsed tile, update its neighbors' possibilities.
*
* First checks if the tile is in fact collapsed, then iterates through neighbors
* in NESW order. For each neighbor, check each possible tile then remove tiles
* that are no longer in accordance with the adjacency rules.

* @param cells The matrix within which loc is located.
* @param loc The location of the tile to update around.
*/
void update_neighbors(matrix* cells, coords loc);
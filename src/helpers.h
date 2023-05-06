#pragma once

#include <stdnoreturn.h>  // noreturn

#include "datatypes.h"

/**
 * Print an error message and exit with a failure status code.
 *
 * Upon an error, print an error message with a desired prefix. The prefix
 * error_msg should describe the context in which the error occurred, followed
 * by a more specific message corresponding to errno set by whatever function or
 * system call that encountered the error. This function exits the program and
 * thus does not return.
 *
 * @param error_msg The error message to print.
 */
noreturn void error_and_exit(const char* error_msg);

/**
 * Return a pointer to the tile object that a collapsed cell has resolved to.
 *
 * Since we're storing invalid tiles within a cell as NULL pointers, we can't
 * just get the first tile in a cell's possibilities. This function goes through
 * the possibilities and returns the non-null tile.
 *
 * Errors and exits if the entropy of the cell isn't exactly 1.
 * Errors and exits if every tile in the cell is NULL.
 *
 * @param cells The matrix of cells to work with.
 * @param loc The coordinates of the specific cell to look at.
 * @return A tile pointer to the remaining valid tile object in the cell.
 */
tile* get_collapsed_tile(matrix* cells, coords loc);

/**
 * Makes an array of cells based on num_tiles and the list of tile
 * possibilities of the given height and width
 *
 * For the given num_tiles and possibilities, makes a cell for each location in
 * the matrix. The initial entropy of the cells is the total number of tiles.
 * The array is an array of "rows", so must be indexed as [y][x] instead of the
 * more intuitive [x][y]. Makes a deep copy of tile possibilities for each cell.
 *
 * @param height The height of the matrix, and therefore cell array
 * @param width The width of the matrix, and therefore cell array
 * @param num_tiles The number of tiles generated during previous parsing
 * @param tile_possibilities The array of tile pointers for all the possible
 * tiles.
 *
 * @return the cell pointer pointer representing the array
 */
cell** make_cell_array(size_t height, size_t width, size_t num_tiles,
                       tile** tile_possibilities);

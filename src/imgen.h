#pragma once

#include "datatypes.h"

/**
 * Places tile image onto background image at specified matrix coords.
 *
 * Given a background image, a tile image, and tile coordinates, the program 
 * beings by converting matrix coords to image coords. Then proceeds to loop 
 * the rows and columns and channels of the tile image, copying channel values 
 * into the background image from the image coords calculated earlier. The program
 * returns nothing on success and failure.
 *
 * @param bkg The background image for the tile to be copied into.
 * @param tile The tile image to be copied. 
 * @param posi The matrix coordinates that the tile image will be copied to.
 *
 */
void place_image(Image *bkg, Image *tile, coords posi);

/**
 * Frees an image struct from memory.
 *
 * Given an Image struct, check that the image has information stored in it. If
 * the image has the STB allocation flag, use the STB image free method, otherwise
 * free the data struct member. Finally, reset all struct member values to defaults.
 * On success or failure, this function returns nothing.
 *
 * @param img The image struct to be freed.
 */

void image_free(Image *img);

/**
 * Create a new image.
 *
 * Given an image struct width, height, boolean flag, and channels; if the flag 
 * is true, allocate new memory for the data array, otherwise ... TODO
 *
 * @param img The image struct to be populated.
 */
void image_create(Image *img, int width, int height, int channels, bool zeroed);

/**
 * Loads image file into memory.
 *
 * Given an image struct pointer and file name, program attempts to open the file with 
 * the listed filename and copy file contents into given image struct. Upon failure, 
 * this function does not copy any values into the struct (img->data ==NULL).
 *
 * @param img Pointer to an image struct where image data will be stored.
 * @param filename String of the file's name that we want to open.
 *
 */

void image_load(Image *img, const char *filename);

/**
 * Loads image file into memory.
 *
 * Given an image struct pointer and file name, program attempts to write the image 
 * struct's contents to the file of the given filename. The program handles common 
 * image formats, specifically, jpg, jpeg, & png.
 *
 * @param img Pointer to an image struct where image data will be copied from.
 * @param filename String of the file's name that we want to write to.
 *
 */

void image_save(Image *img, const char *filename);


/**
 * Assembles final output image from matrix of tiles.
 * 
 * Given a populated matrix struct, the function creates a zeroed output image, and 
 * moves the current working directory into the /img/ directory. The function 
 * then iterates through each cell of the matrix, copies the corresponding 
 * tile (of entropy 1) to the output image at the equivelant cell coordinates 
 * in the image. During each cycle of this loop a new temporary image struct is
 * created, loaded with the appropriate tile, then freed from memory. Once the 
 * loop completes, all tiles will have been placed; the function saves the image
 * then frees it from memory.
 * 
 * @param cells The (assumed to be) populated matrix. 
 *
 */
void make_output(matrix* cells);

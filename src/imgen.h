#pragma once

#include "datatypes.h"


void place_image(Image *bkg, Image *tile, coords posi);

void image_free(Image *img);

void image_create(Image *img, int width, int height, int channels, bool zeroed);

void image_load(Image *img, const char *filename);

void image_save(Image *img, const char *filename);

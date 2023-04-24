#include "datatypes.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

void image_free(Image* img) {
  if (img->allocation_ != NO_ALLOCATION && img->data != NULL) {
    if (img->allocation_ == STB_ALLOCATED) {
      stbi_image_free(img->data);
    } else {
      free(img->data);
    }
    img->data = NULL;
    img->width = 0;
    img->height = 0;
    img->size = 0;
    img->allocation_ = NO_ALLOCATION;
  }
}

void image_create(Image* img, int width, int height, int channels,
                  bool zeroed) {
  size_t size = width * height * channels;
  if (zeroed) {
    img->data = calloc(size, 1);
  } else {
    img->data = malloc(size);
  }
  if (img->data != NULL) {
    img->width = width;
    img->height = height;
    img->channels = channels;
    img->size = size;
    img->allocation_ = SELF_ALLOCATED;
  }
}

void image_load(Image* img, const char* filename) {
  img->data = (uint8_t*)stbi_load(filename, &img->width, &img->height,
                                  &img->channels, 0);

  if ((img->data) != NULL) {
    img->size = img->width * img->height * img->channels;
    img->allocation_ = STB_ALLOCATED;
  }
}

edge_t* make_edges(char* all_edges, size_t rotation) {
  char[4] rotated;
  memcpy(rotated + rotation, all_edges, 4 - rotation);
  memcpy(rotated, all_edges + 4 - rotation, rotation);
  edge_t edges = edge_t{rotated};
  return &edges
}

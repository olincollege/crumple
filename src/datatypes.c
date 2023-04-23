#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "datatypes.h"
#include "helpers.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


void image_free(Image *img){
  if(img->allocation_ != NO_ALLOCATION && img->data !=NULL){
    if(img->allocation_ == STB_ALLOCATED){
      stbi_image_free(img->data);
    }
    else {
      free(img->data);
    }
    img->data = NULL;
    img->width = 0;
    img->height = 0;
    img->size = 0;
    img->allocation_ = NO_ALLOCATION;
    
  }
}

void image_create(Image *img, int width, int height, int channels, bool zeroed){
  size_t size = width * height * channels;
  if (zeroed){
    img->data = calloc(size, 1);
  }
  else{
    img->data = malloc(size);
  }
  if(img->data!=NULL){
    img->width = width;
    img->height = height;
    img->channels = channels;
    img->size = size;
    img->allocation_ = SELF_ALLOCATED;
  }
}

void image_load(Image *img, const char *filename){
  
  img->data = (uint8_t*) stbi_load(filename,&img->width, &img->height, &img->channels, 0);

  if((img->data)!=NULL){
    img->size = img->width * img->height * img->channels; 
    img->allocation_ = STB_ALLOCATED;
  }
}

void image_save(Image *img, const char *filename){
  const int quality_knob = 100;
  
  if(str_ends_in(filename,".jpg") || str_ends_in(filename,".JPG") || \
      str_ends_in(filename,".jpeg") ||str_ends_in(filename,".JPEG")){
    stbi_write_jpg(filename, img->width, img->height, img->channels, img->data,quality_knob);
  } 
  else if(str_ends_in(filename,".png") ||str_ends_in(filename,".PNG")){
    stbi_write_png(filename, img->width, img->height, img->channels, img->data,img->width * img->height);
  } 
  else{
    ON_ERROR_EXIT(false, "Incorrect Image format");
  }
}

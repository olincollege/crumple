#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "datatypes.h"
#include "helpers.h"
#include "imgen.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

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

void place_image(Image *bkg, Image *tile, coords posi){
  // using the (mat) coords, determine the real position (upper left) 
  coords real = {.x = tile->width * posi.x, .y = tile->height * posi.y};  

  size_t tileWlen = (size_t) tile->width*tile->channels;
  size_t rowlen =   (size_t) bkg->width * bkg->channels;

  size_t first_c =  (size_t) real.x * bkg->channels;
  size_t first_r =  real.y * rowlen;

  size_t last_row = first_r * tileWlen * tile->height;
  size_t last_col = first_c * tileWlen;

  size_t tile_offset = 0;

  for (size_t row = first_r; row<last_row; row += (size_t) bkg->width*bkg->channels){
    tile_offset += tile->width;
    for (size_t col = first_c; col<last_col; col += bkg->channels){
//      bkg->data[row+col + 0] = tile->data[tile_offset+col];
//      bkg->data[row+col + 1] = tile->data[tile_offset+col+1];
//      bkg->data[row+col + 2] = tile->data[tile_offset+col+2];
      for(size_t step = 0; step<tile->channels;++step){
        bkg->data[row+col + step] = tile->data[tile_offset+col+step];
      }
    }
  }
}

int main(void) {
  // ...
  Image tile_img, bg_img;

  char* bg_filename = "blank.jpg";
  char* tile_filename = "small.png";
  
  char buf[256];
  
  if (getcwd(buf, sizeof(buf))==NULL){
    printf("ERROR: couldnt get cwd\n");
  }
  // currently running out of src dir
  //backing out from src to toplevel to img/  
  
  chdir("../img/");
  getcwd(buf, sizeof(buf));
  printf(buf); 
  printf("\n");

  image_load(&tile_img,tile_filename);
  ON_ERROR_EXIT(tile_img.data==NULL, "Image couldn't be loaded");
  printf("Success!\nLoaded img (%ix%i), and %i channels\n", tile_img.width, tile_img.height, tile_img.channels);

  image_load(&bg_img,bg_filename);
  ON_ERROR_EXIT(bg_img.data==NULL, "Image couldn't be loaded");
  printf("Success!\nLoaded img (%ix%i), and %i channels\n", bg_img.width, bg_img.height, bg_img.channels);

  image_free(&tile_img);
  image_free(&bg_img);
}

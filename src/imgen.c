#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "datatypes.h"
#include "helpers.h"
#include "imgen.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

// default image width, height
#define DEFAULT_BLOCK 150

static inline bool str_ends_in(const char*str, const char *ends){
  size_t str_len = strlen(str);
  size_t ends_len = strlen(ends);
  char* pos = strstr(str,ends);
  return (pos!=NULL) && (pos+ends_len==str+str_len);

}

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
    error_and_exit("Incorrect Image format");
  }
}

void place_image(Image *bkg, Image *tile, coords posi){
  // using the (mat) coords, determine the real position (upper left) 
  coords real = {.x = tile->width * posi.x, .y = tile->height * posi.y};  

  size_t tileWlen = (size_t) tile->width*tile->channels;
  size_t rowlen =   (size_t) bkg->width * bkg->channels;

  size_t first_c =  real.x * bkg->channels;
  size_t first_r =  real.y * rowlen;

  size_t last_row = first_r + rowlen * tile->height;
  size_t last_col = first_c + tileWlen;

  size_t tile_offset = 0;

  for (size_t row = first_r; row!=last_row; row += rowlen){
    for (size_t col = first_c; col!=last_col; col += bkg->channels){
      size_t t_col = col-first_c;
      bkg->data[row+col] = tile->data[tile_offset+t_col];
      bkg->data[row+col+1] = tile->data[tile_offset+t_col+1];
      bkg->data[row+col+2] = tile->data[tile_offset+t_col+2];
//      for(size_t step = 0; step<tile->channels;++step){
//        bkg->data[row+col + step] = tile->data[tile_offset+col+step];
//        printf("%d\n",tile->data[tile_offset+col+step]);
//      }
    }
    tile_offset += tile->width*tile->channels;
  }
}

void make_output(matrix* cells){
   
  Image tile_img, out_img;

  image_create(&out_img, (size_t)cells->height*DEFAULT_BLOCK, (size_t)cells->width*DEFAULT_BLOCK, 3, true); 
  if (tile_img.data==NULL){
    error_and_exit("Image couldn't be loaded");
  }
  printf("Success!\nCreated BG img (%ix%i), and %i channels\n", out_img.width, out_img.height, out_img.channels);

  // move cwd to img folder or add /img/ to filename 
  // @lxbtlr TODO: check where executable is created and adjust this accordingly
  chdir("./img/");
  
  for ( size_t xloc = 0; xloc<cells->width; ++xloc){
    // temp image
    Image t_img;
    for ( size_t yloc = 0; yloc<cells->height; ++yloc){
      coords t_coords = {.x = xloc, .y = yloc};
      
      // load image into memory
      image_load(&t_img, get_collapsed_tile(cells,t_coords)->image);
      
      // place tile
      place_image(&out_img, &t_img, t_coords);
      // free image from memory
      image_free(&t_img);
    }
    
  }
  // save image
  image_save(&out_img, "Output.jpg");
  image_free(&out_img);
}

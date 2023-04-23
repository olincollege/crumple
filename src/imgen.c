#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "datatypes.h"
#include "helpers.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb/stb_image.h>
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include <stb/stb_image_write.h>

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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

int main(void) {
  // ...
  
  int img_w = 0; 
  int img_h = 0; 
  int img_c = 0;

  char buf[256];
  
  if (getcwd(buf, sizeof(buf))==NULL){
    printf("ERROR: couldnt get cwd\n");
  }
  // currently running out of src dir
  //backing out from src to toplevel  
  
  chdir("..");
  getcwd(buf, sizeof(buf));
  strncat(buf,"/img",(size_t)5);
  // changing cwd to crumple/img
  chdir(buf);
  getcwd(buf, sizeof(buf));
  printf(buf); 
  printf("\n");

  char* filename = "image.jpg";
  unsigned char *img = stbi_load(filename,&img_w, &img_h, &img_c,0);

  if (img == NULL){
    printf("Error loading image file\n");
    exit(1);
  }

  printf("Success!\nLoaded img (%ix%i), and %i channels", img_w, img_h, img_c);



  stbi_image_free(img);
}

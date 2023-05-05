#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "collapser.h"
#include "datatypes.h"
#include "helpers.h"
#include "imgen.h"
#include "parser.h"


int seed = 111111;


static char* handle_args(int argc, char* argv[]){
  
  if (argc != 2){
    error_on_exit("invalid number of args passed");
  } 
  return argv[1];
}

int main(int argc, char* argv[]) {
  
  char* config_file = handle_args(argc, argv);

// parse yaml
// generate matrix struct 
  
  matrix mat;

  while(1){
    size_t pepa = 1;
    for (size_t xloc = 0; xloc<mat.width;++xloc){
      for (size_t yloc = 0; yloc<mat.width;++yloc){
        if( mat.array[xloc][yloc].entropy!= 1){
          pepa =0;
        }
      }
    }
    if (pepa !=1){
      collapse_lowest_entropy(&mat,&seed);
      update_neighbors(&mat, );

    }
  }

// collapser loop
//  check
//  collapse
//  re-eval

// imgen
//
}

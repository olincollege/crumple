#include <stdio.h>

#include "parser.h"

int main(void) {
  printf("Hello world!\n");
  FILE* input_yaml = fopen("input.yaml", "re");
  if (input_yaml == NULL) {
    printf("error with file");
    return 1;
  }
  get_text_split_sections(input_yaml);
}

#include "helpers.h"

#include <stdbool.h>
#include <stdio.h>   // perror
#include <stdlib.h>  // exit, EXIT_FAILURE
#include <string.h>






void error_and_exit(const char* error_msg) {
  perror(error_msg);
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  exit(EXIT_FAILURE);
}

bool str_ends_in(const char *str, const char *end){
  size_t str_len = strlen(str);
  size_t end_len = strlen(end);
  
  char* pos = strstr(str,end);
  
  return (pos != NULL) && (pos + end_len == str + str_len);
}

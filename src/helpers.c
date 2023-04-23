#include "helpers.h"

#include <stdio.h>   // perror
#include <stdlib.h>  // exit, EXIT_FAILURE




void error_and_exit(const char* error_msg) {
  perror(error_msg);
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  exit(EXIT_FAILURE);
}

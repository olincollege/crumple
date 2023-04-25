#pragma once

#include <stdnoreturn.h>  // noreturn

#include "datatypes.h"

// errors if cond passed is true
#define ON_ERROR_EXIT(cond, message) \ 
do{ \
  if(cond){ \ 
    printf("ERROR in function: %s at line %d\n", __func__, __LINE__ ); \
    perror((message)); \ 
    exit(1); \ 
  }\
}while(0)

/**
 * Print an error message and exit with a failure status code.
 *
 * Upon an error, print an error message with a desired prefix. The prefix
 * error_msg should describe the context in which the error occurred, followed
 * by a more specific message corresponding to errno set by whatever function or
 * system call that encountered the error. This function exits the program and
 * thus does not return.
 *
 * @param error_msg The error message to print.
 */
noreturn void error_and_exit(const char* error_msg);

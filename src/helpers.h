#pragma once

#include <stdbool.h>
#include <stdnoreturn.h>  // noreturn


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
 * Determine if string ends in a given substring.
 *
 * Given two strings, the string and the substring, the program determines their 
 * respective lengths, and checks to see if the first string contains the substring.
 * If both the substring is found in the string, and the substring is found to 
 * be at the end of the string, the function returns true. If not the function 
 * returns false.
 *
 * @param str The string we are checking in.
 * @param end The substring we are checking for.
 *
 * @return bool The logical state output of string ending in string.
 */
bool str_ends_in(const char *str, const char *end);
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





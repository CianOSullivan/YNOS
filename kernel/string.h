#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include "../cpu/types.h"
#include "memory.h"
#include "../drivers/screen.h"

/** @brief The String class.
Implements many standard methods for string manipulation
@author Cian O'Sullivan
*/

void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);

/**
Determine length of character pointer

@returns length of char pointer
 */
int str_len(char *pointer);

/**
Reverse the given character pointer
*/
void reverse(char *s);

/**

 */
void int_to_ascii(int n, char str[]);

/**

 */
char* int_to_char(int n);

/**
Compares whether X and Y are the same

@returns status of comparison
*/
int compare(char *X, char *Y);

/**
Get pointer to first occurence of Y in X or a null pointer if it is not
part of X

@returns pointer to first occurent of Y in X
*/
char* strstr(char* X, char* Y);

/**
Convert hex code to ascii
*/
void hex_to_ascii(int n, char str[]);

/**
Tokenize string input.
*/
char* strtok(char* s, char* delm);

#endif

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

/**
Remove last character

@param s the character array to backspace
*/
void backspace(char s[]);

/**
Add character n to char array s

@param s the character array to append the character to
@param n the character to append
 */
void append(char s[], char n);

/**
Compares whether s1 and s2 are the same

@returns status of comparison
@param s1 character array one
@param s2 character array two
*/
int strcmp(char s1[], char s2[]);

/**
Determine length of character pointer

@returns length of char pointer
@param pointer pointer to characters
 */
int str_len(char *pointer);

/**
Reverse the given character pointer

@param s pointer to characters to reverse
*/
void reverse(char *s);

/**
Convert int to ascii character

This implementation changes the given character array
@param n the int to convert
@param str the character array to store the result in
*/
void int_to_ascii(int n, char str[]);

/**
Convert int to ascii character

This implementation returns a pointer to a character
@return character pointer to converted char
@param n the int to convert
*/
char* int_to_char(int n);


/**
Get pointer to first occurence of Y in X or a null pointer if it is not
part of X

@returns pointer to first occurent of Y in X
@param X character pointer 1
@param Y character pointer 2
*/
char* strstr(char* X, char* Y);

/**
Convert hex code to ascii

@param n the hex code
@param str the ascii character(s)
*/
void hex_to_ascii(int n, char str[]);

/**
Tokenize string input.

@return character pointer to tokenized string
@param s the string to tokenize
@param delm the string delimiter
*/
char* strtok(char* s, char* delm);

#endif

#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include "../cpu/types.h"
#include "memory.h"
#include "../drivers/screen.h"
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
int str_len(char *pointer);
void reverse(char *s);
void int_to_ascii(int n, char str[]);
char* int_to_char(int n);

int compare(char *X, char *Y);
char* strstr(char* X, char* Y);

void hex_to_ascii(int n, char str[]);

char* strtok(char* s, char* delm);

#endif

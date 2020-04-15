#include "string.h"

int str_len(char *pointer)
{
   int c = 0;
 
   while( *(pointer + c) != '\0' )
      c++;
 
   return c;
}

void reverse(char *s)
{
   int length, c;
   char *begin, *end, temp;
 
   length = str_len(s);
   begin  = s;
   end    = s;
 
   for (c = 0; c < length - 1; c++)
      end++;
 
   for (c = 0; c < length/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
}

void append(char s[], char n) {
    int len = str_len(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = str_len(s);
    s[len-1] = '\0';
}

/* K&R 
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}


char* int_to_char(int num) {
    char* str;
    int i = 0;
    int sign = num;
    if (num == 0) {
        return "0";
    }
    if (sign < 0){
        num = -num;
    }

    while (num > 0) {
        str[i] = num % 10 + '0';
        i++;
        num /= 10;
    }
    if (sign < 0){
        str[i++] = '-';
    }
    str[i] = '\0';
    reverse(str);
    return str;
}

// returns true if X and Y are same
int compare(char *X, char *Y)
{
	while (*X && *Y)
	{
		if (*X != *Y)
			return 0;

		X++;
		Y++;
	}

	return (*Y == '\0');
}

// Function to implement strstr() function
char* strstr(char* X, char* Y)
{
	while (*X != '\0')
	{
		if ((*X == *Y) && compare(X, Y))
			return X;
		X++;
	}

	return NULL;
}

// Implement strsep function

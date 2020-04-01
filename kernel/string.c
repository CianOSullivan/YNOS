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
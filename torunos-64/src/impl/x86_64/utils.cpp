#include "sys/utils.h"

uint32 strlen(const char* str)
{
  uint32 length = 0;
  while(str[length])
    length++;
  return length;
}

int atoi(const char* str)
{
    int sign = 1, base = 0, i = 0;
     
    // if whitespaces then ignore.
    while (str[i] == ' ')
    {
        i++;
    }
     
    // sign of number
    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-');
    }
   
    // checking for valid input
    while (str[i] >= '0' && str[i] <= '9')
    {
        // handling overflow test case
        if (base > 2147483647 / 10
            || (base == 2147483647 / 10
            && str[i] - '0' > 7))
        {
            if (sign == 1)
                return 2147483647;
            else
                return 0;
        }
        base = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}
 

uint32 digit_count(int num)
{
  return (uint32)digit_countl(num);
}

uint64 digit_countl(long num)
{
  uint64 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  ltoa(num, number);
}
void ltoa(long num, char *number)
{
  long dgcount = digit_countl(num);
  long index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}
int strncmp(char *a, char *b, int len) {
    for (int i = 0; i < len; i++) {
        if (*(a+i) != *(b+i)) {
            return 1;
        }

    }
    return 0;
}

int strcmp(char *a, char *b) {
    int len = strlen(a);
    if (len != strlen(b)) {
        return 1;
    }
    
    return strncmp(a, b, len);
}
void strcpy(char *des, char *src) {
  int len = strlen(src);
  for (int i = 0; i <= len; i++) {
    *(des+i) = *(src+i);
  }
}
void clear_string(char *c, int ren) {
    for (int i = 0; i < ren; i++) {
        *(c+i) = 0;
    }
}
void fill(char *c, int ren, char col) {
    for (int i = 0; i < ren; i++) {
        *(c+i) = col;
    }
}
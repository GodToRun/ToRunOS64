#ifndef STDIO_H
#define STDIO_H
#include "sys/types.h"
#include <stdlib.h>
#include "sys/utils.h"
#include "sys/io/print.h"
#include "sys/chars.h"
#include <stdio.h>

typedef __builtin_va_list va_list;
#define va_start(ap, X) __builtin_va_start(ap, X)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)

void puts(char *s) {
    print_str(s);
}
void sleep_sec(uint32 count) {
    while (count > 0) {
        count--;
    }
}
int putchar(int c) {
    printf("%c", c);
    return c;
}
int getchar() {
    return get_ascii_char_lower(get_input_keycode());
}
char *gets(char *str) {
    int i;
    char ch;
    while (ch != '\n') {
        ch = getchar();
        putchar(ch);
        *(str+i) = ch;
        *(str+i+1) = 0;
        i++;
        sleep_sec(0x02FFFFFF);
    }
    return str;
}

int scanf(char * str, ...)
{
    va_list vl;
    int i = 0, j=0, ret = 0;
    char buff[100] = {0}, tmp[20], c = 2;
    char *out_loc;
    while(c != '\n') 
    {
        c = getchar();
        putchar(c);
        sleep_sec(0x02FFFFFF);
        buff[i] = c;
        i++;
 	}
 	va_start( vl, str );
 	i = 0;
 	while (str && str[i])
 	{
 	    if (str[i] == '%') 
 	    {
 	       i++;
 	       switch (str[i]) 
 	       {
 	           case 'c': 
 	           {
	 	           *(char *)va_arg( vl, char* ) = buff[j];
	 	           j++;
	 	           ret ++;
	 	           break;
 	           }
 	           case 'd': 
 	           {
                    char string[30];
                    for (int i = 0;; i++) {
                        string[i] = buff[j+i];
                        string[i+1] = 0;
                        if (buff[j+i] == 0 || buff[j+i] == ' ') {
                            break;
                        }
                    }
                    printf("str: %s", string);
	 	           *(int *)va_arg( vl, int* ) = atoi(string);
	 	           j+=out_loc -&buff[j];
	 	           ret++;
	 	           break;
 	            }
 	            case 'x': 
 	            {
	 	           *(int *)va_arg( vl, int* ) =strtol(&buff[j], &out_loc, 16);
	 	           j+=out_loc -&buff[j];
	 	           ret++;
	 	           break;
 	            }
                case 's':
                {
                    char *ptr = (char *)va_arg( vl, char * );
                    for (int i = 0;; i++) {
                        if (buff[j+i] == 0 || buff[j+i] == ' ')
                            break;
                        *(ptr+i) = buff[j+i];
                    }
                   ret++;
                   break;
                }
 	        }
 	    } 
 	    else 
 	    {
 	        buff[j] =str[i];
            j++;
        }
        i++;
    }
    va_end(vl);
    return ret;
}
#endif
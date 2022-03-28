#ifndef STDIO_H
#define STDIO_H
#include "sys/types.h"
#include "stdlib.h"

void puts(char *s);
void sleep_sec(uint32 count);
int putchar(int c);
char *gets(char *str);
void printf(const char *fmt, ...);

int getchar();
int scanf(char * str, ...);
#endif
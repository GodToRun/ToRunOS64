#ifndef UTILS_H
#define UTILS_H

#include "types.h"

uint32 strlen(const char*);
uint32 digit_count(int);
uint64 digit_countl(long);
void itoa(int, char *);
void ltoa(long, char *);
int strcmp(char *, char *);
int strncmp(char *, char *, int);
void strcpy(char *, char *);
void clear_string(char *, int);
void fill(char *, int, char);
int atoi(const char* str);

#endif

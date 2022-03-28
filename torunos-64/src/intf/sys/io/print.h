#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>
#include <stddef.h>
#include "../types.h"

extern size_t col;
extern size_t row;
extern struct Char *buffer;

enum {
    PRINT_COLOR_BLACK = 0,
    PRINT_COLOR_BLUE = 1,
    PRINT_COLOR_GREEN = 2,
    PRINT_COLOR_CYAN = 3,
    PRINT_COLOR_RED = 4,
    PRINT_COLOR_MAGENTA = 5,
    PRINT_COLOR_BROWN = 6,
    PRINT_COLOR_LIGHT_GRAY = 7,
    PRINT_COLOR_DARK_GRAY = 8,
    PRINT_COLOR_LIGHT_BLUE = 9,
    PRINT_COLOR_LIGHT_GREEN = 10,
    PRINT_COLOR_LIGHT_CYAN = 11,
    PRINT_COLOR_LIGHT_RED = 12,
    PRINT_COLOR_PINK = 13,
    PRINT_COLOR_YELLOW = 14,
    PRINT_COLOR_WHITE = 15,
};

enum sprintf_mode {
  HEX_ZERO_COUNTS = 0,
  NONE = 1
};

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char
{
  uint8_t character;
  uint8_t color;
};

void sleep(uint32 timer_count);
void printf_set_mode(int mode, int value);
void print_clear();
void print_char(char character);
void print_str(char* string);
void set_char(uint32_t, uint32_t, struct Char);
void set_string(uint32_t, uint32_t, char *, uint8_t, uint8_t);
void print_set_color(uint8_t foreground, uint8_t background);
extern size_t input_pos;
extern size_t block_del_pos;
void printf(const char *fmt, ...);
void sprintf(char *buf, const char *exp, ...);
void getstring(char *);
void print_int(int num);
void print_long(long num);
char get_input_keycode();

#endif
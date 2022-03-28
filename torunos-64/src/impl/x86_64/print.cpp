#include "sys/io/print.h"
#include "sys/utils.h"
#include "sys/chars.h"
#include <stdbool.h>

bool capslock = false;
bool shift = false;
bool alt = false;
bool ctrl = false;
bool numlock = true;
bool scrolllock = false;

size_t input_pos;
size_t block_del_pos;

struct Char* buffer = (struct Char *)0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;
char *char_mem;
int printf_mode;
int printf_mode_value;
void clear_row(size_t row)
{
  struct Char empty = (struct Char){
    character : ' ',
    color : color,
  };

  for (size_t col = 0; col < NUM_COLS; col++)
  {
    buffer[col + NUM_COLS * row] = empty;
  }
}
void printf_set_mode(int mode, int value) {
  printf_mode = mode;
  printf_mode_value = value;
}
void clear_col(size_t column)
{
  column--;
  if(input_pos<=block_del_pos){

  }else{
  col--;
  struct Char empty = (struct Char){
    character : ' ',
    color : color,
  };
    buffer[column + NUM_COLS * row] = empty;
    input_pos--;
    }
}

void print_clear()
{
  for (size_t i = 0; i < NUM_ROWS; i++)
  {
    clear_row(i);
  }
  char title[NUM_COLS+1];
  fill(title, NUM_COLS, 0x20);
  title[0] = 's';
  title[1] = 'h';
  title[2] = 'e';
  title[3] = 'l';
  title[4] = 'l';

  title[32] = 'T';
  title[33] = 'o';
  title[34] = 'R';
  title[35] = 'u';
  title[36] = 'n';
  title[37] = 'O';
  title[38] = 'S';
  title[39] = '6';
  title[40] = '4';
  title[NUM_COLS] = 0;
  set_string(0, 0, title, PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLUE);
  row = 1;
}

void print_newline()
{
  col = 0;

  if (row < NUM_ROWS-1)
  {
    row++;
    return;
  }

  for (size_t row = 2; row < NUM_ROWS; row++)
  {
    for (size_t col = 0; col < NUM_COLS; col++)
    {
      struct Char character = buffer[col + NUM_COLS * row];
      buffer[col + NUM_COLS * (row - 1)] = character;
    }
  }

  clear_row(NUM_ROWS - 1);
}

void set_char(uint32_t x, uint32_t y, struct Char c) {
  buffer[x + (NUM_COLS * y)] = c;
}
void set_string(uint32_t x, uint32_t y, char *str, uint8_t col, uint8_t back_col) {
  for (int i = 0; i < strlen(str); i++) {
    struct Char c;
    c.character = *(str+i);
    c.color = col + (back_col << 4);
    set_char(x+i, y, c);
  }
}

void print_char(char character)
{
  if (character == '\n')
  {
    print_newline();
    return;
  }

  if (col >= NUM_COLS)
  {
    print_newline();
  }

  buffer[col + NUM_COLS * row] = (struct Char){
    character : (uint8_t)character,
    color : color,
  };
  input_pos = col + NUM_COLS * row;
  col++;
}

void print_str(char *str)
{
  for (size_t i = 0; 1; i++)
  {
    *(char_mem+1) = 0;
    char character = (uint8_t)str[i];

    if (character == '\0')
    {
      return;
    }
    print_char(character);
  }
}

void print_int(int num)
{
  char str_num[digit_count(num) + 1];
  itoa(num, str_num);
  print_str(str_num);
}

void print_long(long num)
{
  char str_num[digit_count(num) + 1];
  ltoa(num, str_num);
  print_str(str_num);
}

uint8 inb(uint16 port)
{
  uint8 ret;
  asm volatile("inb %1, %0"
               : "=a"(ret)
               : "d"(port));
  return ret;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1"
               : "=a"(data)
               : "d"(port));
}

char get_input_keycode()
{
  char ch = 0;
  while ((ch = inb(KEYBOARD_PORT)) != 0)
  {
    if (ch > 0)
      return ch;
  }
  return ch;
}
/*
keep the cpu busy for doing nothing(nop)
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void wait_for_io(uint32 timer_count)
{
  while (1)
  {
    asm volatile("nop");
    timer_count--;
    if (timer_count <= 0)
      break;
  }
}
void sleep(uint32 timer_count)
{
  wait_for_io(timer_count);
}
void getstring(char *buf)
{
  int i = 0;
  char ch = 0;
  char keycode = 0;
  do
  {
    keycode = get_input_keycode();
    if (keycode == KEY_ENTER)
    {
      print_newline();
      *(buf+i) = 0;
      sleep(0x02FFFFFF);
      return;
    }else if (keycode == KEY_BACKSPACE){
      clear_col(col);
    }
    else if (keycode == KEY_LEFT_ALT_PRESS)
    {
      //print_str("LEFT ALT");
      alt = true;
    }
    else if (keycode == KEY_LEFT_SHIFT_PRESS)
    {
      //print_str("LEFT SHIFT");
      shift = !shift;
    }
    else if (keycode == KEY_LEFT_CTRL_PRESS)
    {
      //print_str("LEFT CTRL");
      ctrl = true;
    }
    else if (keycode == KEY_LEFT_ALT_RELEASE)
    {
      //print_str("LEFT ALT UP");
      alt = false;
    }
    else if (keycode == KEY_LEFT_SHIFT_RELEASE)
    {
      //print_str("LEFT SHIFT UP");
      shift = false;
    }
    else if (keycode == KEY_LEFT_CTRL_RELEASE)
    {
      //print_str("LEFT ALT UP");
      ctrl = false;
    }
    else if (keycode == KEY_CAPS_LOCK_PRESS)
    {
      //print_str("CAPS LOCK");
      capslock = !capslock;
    }
    else
    {
      if (capslock || shift)
      {
        //we're capitalized
        ch = get_ascii_char(keycode);
      }
      else
      {
        ch = get_ascii_char_lower(keycode);
      }
      print_char(ch);
      *(buf+i) = ch;
      i++;
    }
    sleep(0x02FFFFFF);
  } while (ch > 0);
}

void print_set_color(uint8_t foreground, uint8_t background)
{
  color = foreground + (background << 4);
}

typedef __builtin_va_list va_list;
#define va_start(ap, X) __builtin_va_start(ap, X)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)

void _putc(unsigned char c) { print_char((char)c); }

void printf(const char *fmt, ...) {
const char digits[] = "0123456789abcdef";
    va_list ap;
    char buf[10];
    char* s;
    unsigned char u;
    int c, i, pad;

    va_start(ap, fmt);
    while ((c = *fmt++) != 0) {
        if (c == '%') {
            c = *fmt++;
            if (c == 'l')
                c = *fmt++;
            switch (c) {
            case 'c':
                _putc(va_arg(ap, int));
                continue;
            case 's':
                s = va_arg(ap, char*);
                if (s == (void*)0)
                    s = (char*)"<NULL>";
                for (; *s; s++)
                    _putc((int)*s);
                continue;
            case '%':
                _putc('%');
                continue;
            case 'd':
            case 'i':
                c = 'u';
            case 'u':
            case 'x':
            case 'X':
                u = va_arg(ap, unsigned);
                s = buf;
                if (c == 'u') {
                    do
                        *s++ = digits[u % 10U];
                    while (u /= 10U);
                } else {
                    pad = 0;
                    for (i = 0; i < 8; i++) {
                        if (pad)
                            *s++ = '0';
                        else {
                            
                            *s++ = digits[u % 16U];
                            if ((u /= 16U) == false)
                                pad = 1;
                        }
                    }
                }
                bool doVal = false;
                while (--s >= buf) {
                    if (*s != '0') {
                      doVal = true;
                    }
                    if (doVal)
                      _putc((int)*s);
                }
                continue;
            }
        }
        _putc((int)c);
    }
    va_end(ap);
}
void sprintf_addi(unsigned char c, int *i, char *buf) {
    *(buf+(*i)) = c;
    (*i)++;
}


void sprintf(char *tbuf, const char* fmt, ...)
{
    const char digits[] = "0123456789abcdef";
    va_list ap;
    char buf[10];
    char* s;
    unsigned char u;
    int c, i, pad;
    int bi = 0;
    int zero_counts = 8;
    if (printf_mode == HEX_ZERO_COUNTS)
      zero_counts = printf_mode_value;

    va_start(ap, fmt);
    while ((c = *fmt++) != 0) {
        if (c == '%') {
            c = *fmt++;
            if (c == 'l')
                c = *fmt++;
            switch (c) {
            case 'c':
                sprintf_addi(va_arg(ap, int), &bi, tbuf);
                continue;
            case 's':
                s = va_arg(ap, char*);
                if (s == (void*)0)
                    s = (char*)"<NULL>";
                for (; *s; s++)
                    sprintf_addi((int)*s, &bi, tbuf);
                continue;
            case '%':
                _putc('%');
                continue;
            case 'd':
            case 'i':
                c = 'u';
            case 'u':
            case 'x':
            case 'X':
                u = va_arg(ap, unsigned long);
                s = buf;
                if (c == 'u') {
                    do
                        *s++ = digits[u % 10U];
                    while (u /= 10U);
                } else {
                    pad = 0;
                    for (i = 0; i < zero_counts; i++) {
                        if (pad)
                            *s++ = '0';
                        else {
                            *s++ = digits[u % 16U];
                            if ((u /= 16U) == false)
                                pad = 1;
                        }
                    }
                }
                while (--s >= buf)
                    sprintf_addi((int)*s, &bi, tbuf);
                continue;
            }
        }
        sprintf_addi((int)c, &bi, tbuf);
    }
    va_end(ap);
}
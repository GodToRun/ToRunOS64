#include "sys/graphics.h"
#include "sys/io/print.h"
void draw_box(int x, int y, int width, int height, uint8_t col) {
    for (int _x = x; _x < x+width; _x++) {
        for (int _y = y; _y < y+height; _y++) {
            struct Char ch = {
                character : ' ',
                color : PRINT_COLOR_BLACK + (col << 4)
            };
            set_char(_x, _y, ch);
        }
    }
}
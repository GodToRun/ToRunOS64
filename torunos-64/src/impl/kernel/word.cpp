#include "programs/word.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdcpp.hpp>
#include "sys/io/print.h"
#include "sys/graphics.h"
#include "sys/chars.h"
struct Char cursor = (struct Char){
    character : ' ',
    color : PRINT_COLOR_BLACK + (PRINT_COLOR_LIGHT_GRAY << 4)
};
struct Char empty = (struct Char){
            character : ' ',
            color : PRINT_COLOR_LIGHT_GRAY + (PRINT_COLOR_BLACK << 4),
};
char *buf = new char(50);
char textbuf[NUM_ROWS][NUM_COLS];
char saved_char = ' ';
int bufcol = 0;
int bufrow = 0;
bool capsrock = false;
void get_input(word *w) {    
    int ch;
    int keycode = get_input_keycode();
    if (!capsrock)
        ch = get_ascii_char_lower(keycode);
    else
        ch = get_ascii_char(keycode);
    if (ch == 27) {
        w->mode = 0;
        return;
    }
    else if (keycode == KEY_LEFT_SHIFT_PRESS) {
        capsrock = !capsrock;
        sleep(0x2FFFFFF);
    }
    else if (keycode == KEY_CAPS_LOCK_PRESS) {
        capsrock = !capsrock;
        sleep(0x2FFFFFF);
    }
    else if (ch == 8) {
        if (col > 0)
            col--;
        
        set_char(col, row, cursor);
        buffer[col+1 + NUM_COLS * row] = empty;
        input_pos--;
        sleep(0x2FFFFFF);
        return;
    }
    else if (ch == 40) {
        empty.character = saved_char;
        set_char(col, row, empty);
        row++;
        saved_char = buffer[col + NUM_COLS * row].character;
        cursor.character = saved_char;
        set_char(col, row, cursor);
        sleep(0x2FFFFFF);
        return;
    }
    else if (ch == 38) {
        empty.character = saved_char;
        set_char(col, row, empty);
        row--;
        saved_char = buffer[col + NUM_COLS * row].character;
        cursor.character = saved_char;
        set_char(col, row, cursor);
        sleep(0x2FFFFFF);
        return;
    }
    else if (ch == 39) {
        empty.character = saved_char;
        set_char(col, row, empty);
        col++;
        saved_char = buffer[col + NUM_COLS * row].character;
        cursor.character = saved_char;
        set_char(col, row, cursor);
        sleep(0x2FFFFFF);
        return;
    }
    else if (ch == 37) {
        empty.character = saved_char;
        set_char(col, row, empty);
        col--;
        saved_char = buffer[col + NUM_COLS * row].character;
        cursor.character = saved_char;
        set_char(col, row, cursor);
        sleep(0x2FFFFFF);
        return;
    }
    else if (ch == 16) {
        empty.character = saved_char;
        set_char(col, row, empty);
        col = 0;
        saved_char = buffer[col + NUM_COLS * row].character;
        cursor.character = saved_char;
        set_char(col, row, cursor);
        sleep(0x2FFFFFF);
        return;
    }
    else if (ch == '\n') {
        empty.character = saved_char;
        set_char(col, row, empty);
        row++;
        col = 0;
        saved_char = buffer[col + NUM_COLS * row].character;
        cursor.character = saved_char;
        set_char(col, row, cursor);
        sleep(0x2FFFFFF);
        return;
    }
    bufcol = col;
    bufrow = row - 1;
    textbuf[0][bufcol] = ch;
    std::cout << (char)ch;
    set_char(col, row, cursor);
    sleep(0x2FFFFFF);
}
void select_mode(word *w) {
    int ch = getchar();
    if (ch == 'e') {
        w->mode = 1;
    }
    else if (ch == 'q') {
        w->mode = 2;
    }
    else if (ch == 'r') {
        bufcol = col;
        bufrow = row - 1;
        textbuf[0][bufcol] = 0;
        int precol = col;
        int prerow = row;
        col = 0;
        row = NUM_ROWS - 6;
        printf("------ output ---------------------------------------------------\n");
        draw_box(0, NUM_ROWS - 5, NUM_COLS, 2, PRINT_COLOR_BLACK);
        for (int i = 0; i < NUM_ROWS; i++) {
            if (buffer[NUM_COLS * i].character != ' ') {
                system(textbuf[i]);
            }
            
        }
        col = precol;
        row = prerow;
    }
    sleep(0x2FFFFFF);
}
void get_string_form_screen(int icol, int irow, int len) {
    for (int i = 0; i < len; i++) {
        buf[i] = buffer[icol + i + (NUM_COLS * irow)].character;
    }
    buf[len] = 0;
}
void update_highlighting() {
    for (int icol = 0; icol < NUM_COLS; icol++) {
        get_string_form_screen(icol, row, 30);
        if (strncmp(buf, "echo", 4) == 0) {
            set_string(icol, row, "echo", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "./", 2) == 0) {
            set_string(icol, row, "./", PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "$", 2) == 0) {
            set_string(icol, row, "$", PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "mkdir", 5) == 0) {
            set_string(icol, row, "mkdir", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "touch", 5) == 0) {
            set_string(icol, row, "touch", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "dir", 3) == 0) {
            set_string(icol, row, "dir", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "dump", 4) == 0) {
            set_string(icol, row, "dump", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "cat", 3) == 0) {
            set_string(icol, row, "cat", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "cd", 2) == 0) {
            set_string(icol, row, "cd", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "cls", 3) == 0) {
            set_string(icol, row, "cls", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
        else if (strncmp(buf, "ver", 3) == 0) {
            set_string(icol, row, "ver", PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
        }
    }
}
void word::main() {
    mode = 0;
    system("cls");
    draw_box(NUM_COLS / 2 - 20, NUM_ROWS / 2 - 7, 40, 12, PRINT_COLOR_LIGHT_GRAY);
    set_string(NUM_COLS / 2 - 11, NUM_ROWS / 2 - 5, "Word 2022 for ToRunOS64", PRINT_COLOR_BLACK, PRINT_COLOR_LIGHT_GRAY);

    set_string(NUM_COLS / 2 - 13, NUM_ROWS / 2, "Press any key to continue...", PRINT_COLOR_BLACK, PRINT_COLOR_LIGHT_GRAY);
    getchar();
    sleep(0x2FFFFFF);
    system("cls");
    while (1) {
        if (mode == 0) {
            set_string(0, NUM_ROWS - 1, "[e] edit [r] run bash [q] exit", PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
            select_mode(this);
        }
        else if (mode == 1) {
            set_string(0, NUM_ROWS - 1, "[esc] exit text mode          ", PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
            get_input(this);
        }
        else if (mode == 2) {
            system("cls");
            break;
        }
        update_highlighting();
    }
}
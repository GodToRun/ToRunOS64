#include "programs/tic_tac_toe.h"
#include "sys/io/print.h"
#include <iostream>
#include <stdio.h>
#include <stdcpp.hpp>

void sleep(uint32 timer_count);

int isfree(int x, int y, tictactoe *h) {
    return h->board[y][x] != 'O' && h->board[y][x] != 'X';
}

void draw_board(tictactoe *h) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            struct Char ch;
            ch.character = h->board[y][x];
            int col = PRINT_COLOR_WHITE;
            if (ch.character == 'O')
                col = PRINT_COLOR_LIGHT_BLUE;
            else if (ch.character == 'X')
                col = PRINT_COLOR_LIGHT_RED;
            ch.color = col + (PRINT_COLOR_BLACK << 4);
            set_char((NUM_COLS / 2 - 4) + x * 3, (NUM_ROWS / 2 - 3) + y * 3, ch);
        }
    }
}

void ai_set_board(tictactoe *h) {
    sleep(130331647);
    for (int y = 0; y < 3; y++) {
        if (!isfree(0, y, h) &&
            !isfree(1, y, h) &&
            isfree(2, y, h)) {
            h->board[y][2] = 'X';
            draw_board(h);
            return;
        }
        else if (!isfree(0, y, h) &&
            isfree(1, y, h) &&
            !isfree(2, y, h)) {
            h->board[y][1] = 'X';
            draw_board(h);
            return;
        }
        else if (isfree(0, y, h) &&
            !isfree(1, y, h) &&
            !isfree(2, y, h)) {
            h->board[y][0] = 'X';
            draw_board(h);
            return;
        }
    }
    for (int x = 0; x < 3; x++) {
        if (!isfree(x, 0, h) &&
            !isfree(x, 1, h) &&
            isfree(x, 2, h)) {
            h->board[2][x] = 'X';
            draw_board(h);
            return;
        }
        else if (!isfree(x, 0, h) &&
            isfree(x, 1, h) &&
            !isfree(x, 2, h)) {
            h->board[1][x] = 'X';
            draw_board(h);
            return;
        }
        else if (isfree(x, 0, h) &&
            !isfree(x, 1, h) &&
            !isfree(x, 2, h)) {
            h->board[0][x] = 'X';
            draw_board(h);
            return;
        }
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (isfree(x, y, h)) {
                h->board[y][x] = 'X';
                draw_board(h);
                return;
            }
        }
    }
}
void tictactoe::main() {
    print_clear();
    draw_board(this);
    while (1) {
        int ch = getchar();
        if (ch == '1') {
            if (isfree(0, 0, this))
                board[0][0] = 'O';
            draw_board(this);
        }
        else if (ch == '2') {
            if (isfree(1, 0, this))
                board[0][1] = 'O';
            draw_board(this);
        }
        else if (ch == '3') {
            if (isfree(2, 0, this))
                board[0][2] = 'O';
            draw_board(this);
        }
        else if (ch == '4') {
            if (isfree(0, 1, this)) {
                board[1][0] = 'O';
            }
            draw_board(this);
        }
        else if (ch == '5') {
            if (isfree(1, 1, this))
                board[1][1] = 'O';
            draw_board(this);
        }
        else if (ch == '6') {
            if (isfree(2, 1, this))
                board[1][2] = 'O';
            draw_board(this);
        }
        else if (ch == '7') {
            if (isfree(0, 2, this))
                board[2][0] = 'O';
            draw_board(this);
        }
        else if (ch == '8') {
            if (isfree(1, 2, this))
                board[2][1] = 'O';
            draw_board(this);
        }
        else if (ch == '9') {
            if (isfree(2, 2, this))
                board[2][2] = 'O';
            draw_board(this);
        }
        ai_set_board(this);
        int win = 0;
        int computer_win = 0;
        for (int x = 0; x < 3; x++) {
            if (board[x][0] == 'O' &&
                board[x][1] == 'O' &&
                board[x][2] == 'O'  ) {
                win = 1;
                break;
            }

            if (board[x][0] == 'X' &&
                board[x][1] == 'X' &&
                board[x][2] == 'X'  ) {
                computer_win = 1;
                break;
            }
        }
        
        for (int y = 0; y < 3; y++) {
            if (board[0][y] == 'O' &&
                board[1][y] == 'O' &&
                board[2][y] == 'O'  ) {
                win = 1;
                break;
            }
            else if (board[0][0] == 'O' &&
                board[1][1] == 'O' &&
                board[2][2] == 'O'  ) {
                win = 1;
                break;
            }
            else if (board[2][2] == 'O' &&
                board[1][1] == 'O' &&
                board[0][0] == 'O'  ) {
                win = 1;
                break;
            }

            else if (board[0][2] == 'O' &&
                board[1][1] == 'O' &&
                board[2][0] == 'O'  ) {
                win = 1;
                break;
            }

            if (board[0][y] == 'X' &&
                board[1][y] == 'X' &&
                board[2][y] == 'X'  ) {
                computer_win = 1;
                break;
            }
            else if (board[0][0] == 'X' &&
                board[1][1] == 'X' &&
                board[2][2] == 'X'  ) {
                computer_win = 1;
                break;
            }
            else if (board[2][2] == 'X' &&
                board[1][1] == 'X' &&
                board[0][0] == 'X'  ) {
                computer_win = 1;
                break;
            }

            else if (board[0][2] == 'X' &&
                board[1][1] == 'X' &&
                board[2][0] == 'X'  ) {
                computer_win = 1;
                break;
            }
        }

        int tie = 1;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (isfree(x, y, this))
                    tie = 0;
            }
        }
        
        if (win) {
            print_clear();
            printf("tic tac toe: player win");
            break;
        }
        else if (tie) {
            print_clear();
            printf("tic tac toe: tie");
            break;
        }
        else if (computer_win) {
            print_clear();
            printf("tic tac toe: computer win");
            break;
        }
    }
}
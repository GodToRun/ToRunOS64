#ifndef HELLO_H
#define HELLO_H
#include "program.h"

class tictactoe : public program64 {
    public:
        tictactoe() : program64("tictactoe") {

        }
        char board[3][3] = 
        { '1', '2', '3',
         '4', '5', '6',
        '7', '8', '9', };
        void main();
};
#endif
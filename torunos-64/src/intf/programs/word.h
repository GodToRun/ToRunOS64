#ifndef WORD_H
#define WORD_H
#include "program.h"

class word : public program64 {
    public:
        int mode;
        word() : program64("word") {

        }
        void main();
};
#endif
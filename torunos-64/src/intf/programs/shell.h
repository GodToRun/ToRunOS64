#ifndef SHELL_H
#define SHELL_H
#include "../programs/program.h"

class shell : public program64 {
    public:
        char cmd[100];
        shell() : program64("shell") {

        }
        void main();
        static void command(char *);
};
#endif
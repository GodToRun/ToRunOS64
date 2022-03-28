#ifndef PROGRAM_H
#define PROGRAM_H
#include "../sys/utils.h"
class program64 {
    public:
        char name[60];
        program64(char *name) {
            strcpy(this->name, name);
        }
        void main();
};
#endif
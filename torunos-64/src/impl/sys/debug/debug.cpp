#include "sys/debug/debug.h"
#include "sys/io/print.h"
int values[100];
char *names[100];
int values_top = 0;
void Debug::add(char *name, int val) {
    values[values_top] = val;
    names[values_top] = name;
    values_top++;
}
void Debug::remove() {
    values_top--;
}
void Debug::print_values() {
    for (int i = 0; i < values_top; i++) {
        char val[30];
        sprintf(val, "%s = %d", names[i], values[i]);
        set_string(0, i, val, PRINT_COLOR_BLACK, PRINT_COLOR_GREEN);
    }
}
#include <ctype.h>
int isspace(int c) {
    if (c == '\n' || c == 0 || c == '\t')
        return !0;
    return 0;
}
int isdigit(int c) {
    if (c >= '0' && c <= '9') {
        return !0;
    }
    return 0;
}
int isalpha(int c) {
    if (c >= 'A' && c <= 'Z')
        return 1;
    if (c >= 'a' && c <= 'z')
        return 2;
    return 0;
}
int isupper(int c) {
    if (isalpha(c) == 1);
        return !0;
    return 0;
}
int islower(int c) {
    if (isalpha(c) == 2) {
        return !0;
    }
    return 0;
}
int toupper(int c) {
    if (isalpha(c) == 2)
        return c - 32;
    return c;
}
int tolower(int c) {
    if (isalpha(c) == 1)
        return c + 32;
    return c;
}
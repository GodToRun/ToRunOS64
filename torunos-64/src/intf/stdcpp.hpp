#pragma once
#ifndef STDCPP_HPP
#include <stddef.h>
#define STDCPP_HPP
extern char heap[4096];
extern int heap_top;
int strcmp(char *, char *);
int strlen(char *);
void *operator new(size_t size);
void operator delete(void *ptr, size_t size);
class string {
    char *arr;
    int length;
    public:
        string &operator=(char *str) {
            this->arr = str;
            this->length = strlen(str);
        }
        bool operator==(char *str) {
            return strcmp(this->arr, str) == 0;
        }
        bool operator==(string &str) {
            return strcmp(this->arr, str.arr) == 0;
        }
        int size() {
            return length;
        }
        int get_length() {
            return length;
        }
        bool compare(char *str) {
            return this->arr == str;
        }
};
#endif
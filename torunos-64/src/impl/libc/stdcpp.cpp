#include "stdcpp.hpp"
#include <stddef.h>
char heap[4096];
int heap_top = 0;
void *operator new(size_t size) {
    char *val = &heap[heap_top];
    heap_top += size;
    return val;
}
void operator delete(void *ptr, size_t size) {
    int find_index = 0;
    for (int i = find_index;; find_index++) {
        if (&heap[i] == ptr) {
            break;
        }
    }
    for (int i = find_index+size; i < heap_top; i++) {
        heap[i-size] = heap[i];
    }
    heap_top -= size;
}
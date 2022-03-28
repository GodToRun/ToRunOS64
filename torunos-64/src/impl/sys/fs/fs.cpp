#include "sys/fs/fs.h"
#include "sys/io/print.h"
#include <iostream>
#include <stdio.h>
#include <stdcpp.hpp>
DIRECTORY *DIRECTORY::working_directory = nullptr;
DIRECTORY *DIRECTORY::my_pc = nullptr;
DIRECTORY *DIRECTORY::fs_directory = nullptr;
int ERROR_CODE = 0;
void add_node_to_directory(DIRECTORY *dir, NODE *node) {
    dir->in_nodes[dir->node_top] = node;
    dir->node_top++;
}
void check_fs() {
    if (DIRECTORY::working_directory == nullptr) {
        ERROR_CODE = 0;
        fs_error();
        return;
    }
    else if (DIRECTORY::fs_directory == nullptr) {
        ERROR_CODE = 1;
        fs_error();
        return;
    }
    else if (DIRECTORY::fs_directory->in_nodes == nullptr) {
        ERROR_CODE = 2;
        fs_error();
        return;
    }
    else if (DIRECTORY::working_directory->in_nodes == nullptr) {
        ERROR_CODE = 3;
        fs_error();
        return;
    }
}
char *ERROR_CODE_TO_STRING() {
    if (!ERROR_CODE) {
        return "WORKING_DIRECTORY_NOT_FOUND";
    }
    else if (ERROR_CODE == 1) {
        return "FILESYSTEM_NOT_FOUND";
    }
    else if (ERROR_CODE == 2) {
        return "FILESYSTEM_NODE_ARRAY_NOT_FOUND";
    }
    else if (ERROR_CODE == 3) {
        return "WORKING_DIRECTORY_NODE_ARRAY_NOT_FOUND";
    }
    else {
        return "UNKNOWN";
    }
}
void fs_repair() {
    DIRECTORY dir = DIRECTORY(nullptr, "fs:");
    DIRECTORY::fs_directory = &dir;
    check_fs();
}
void fs_error() {
    print_clear();
    std::cout << "filesystem error" << std::endl << "press any key to try repair"
    << std::endl << "error code: " << ERROR_CODE << std::endl << "(" <<
    ERROR_CODE_TO_STRING() << ")" << std::endl;
    getchar();
    fs_repair();
}
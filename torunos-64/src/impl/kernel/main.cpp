#include "programs/shell.h"
#include "sys/io/print.h"
#include "sys/utils.h"
#include "sys/kernel.h"
#include "sys/fs/fs.h"
#include "sys/debug/debug.h"

void init_fs() {
    DIRECTORY::fs_directory->filename = "fs:";
}

void kernel_main()
{
    DIRECTORY my_pc_dir = DIRECTORY(nullptr, "pc");
    DIRECTORY fs_dir = DIRECTORY(&my_pc_dir, "fs:");
    DIRECTORY system_dir = DIRECTORY(&my_pc_dir, "system");
    DIRECTORY::my_pc = &my_pc_dir;
    DIRECTORY::fs_directory = &fs_dir;
    DIRECTORY::working_directory = &fs_dir;
    init_fs();
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("Welcome to ToRunOS64\n");
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    printf("%s>", DIRECTORY::working_directory->filename);
    DIRECTORY bin = DIRECTORY(DIRECTORY::working_directory, "bin");
    DIRECTORY usr = DIRECTORY(DIRECTORY::working_directory, "usr");
    DIRECTORY home = DIRECTORY(DIRECTORY::working_directory, "home");
    DIRECTORY boot = DIRECTORY(DIRECTORY::working_directory, "boot");
    DIRECTORY etc = DIRECTORY(DIRECTORY::working_directory, "etc");
    DIRECTORY dev = DIRECTORY(DIRECTORY::working_directory, "dev");
    DIRECTORY sys = DIRECTORY(DIRECTORY::working_directory, "sys");
    DIRECTORY temp = DIRECTORY(DIRECTORY::working_directory, "temp");
    DIRECTORY var = DIRECTORY(DIRECTORY::working_directory, "var");
    DIRECTORY root = DIRECTORY(DIRECTORY::working_directory, "root");
    DIRECTORY usrbin = DIRECTORY(&usr, "bin");
    DIRECTORY usrlib = DIRECTORY(&usr, "lib");
    NODE raminfo = NODE(&system_dir, "raminfo", "\0");
    //DIRECTORY::working_directory = (DIRECTORY *)DIRECTORY::find("usr", DIRECTORY::working_directory->in_nodes);
    if (DIRECTORY::fs_directory == nullptr) {
        printf("NULLPTR");
    }
    shell().main();
}
#include "sys/io/print.h"
#include "sys/utils.h"
#include "sys/kernel.h"
#include "sys/debug/debug.h"
#include "sys/fs/fs.h"

#include "programs/program.h"
#include "programs/tic_tac_toe.h"
#include "programs/shell.h"
#include "programs/word.h"

void *__gxx_personality_v0;
void *_Unwind_Resume;
void shell::main() {
    while (1) {
    	getstring(cmd);
    	command(cmd);
    	printf("\n%s>", DIRECTORY::working_directory->filename);
    	clear_string(cmd, 100);
    }
}

void shell::command(char *cmd) {
    if (strcmp(cmd, "ver") == 0) {
        printf("ToRunOS64 Version: %s", KERNEL_VERSION);
    }
    else if (strcmp(cmd, "debug print") == 0) {
        Debug::print_values();
    }
    else if (strcmp(cmd, "dir") == 0) {
        check_fs();
        int size = 0;
        for (int i = 0; i < 100; i++) {
            if (DIRECTORY::working_directory->in_nodes[i] != nullptr) {
                if (DIRECTORY::working_directory->in_nodes[i]->is_directory)
                    print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLACK);
                else
                    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
                printf("%s\n", DIRECTORY::working_directory->in_nodes[i]->filename);
                size += DIRECTORY::working_directory->in_nodes[i]->size;
            }
        }
        print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
        printf("\nTotal bytes: %d", size);
        
    }
    else if (strcmp(cmd, DIRECTORY::fs_directory->filename) == 0) {
        DIRECTORY::working_directory = DIRECTORY::fs_directory;
    }
    else if (strncmp(cmd, "cd ", 3) == 0) {
        NODE *node = DIRECTORY::find(&cmd[3], DIRECTORY::working_directory->in_nodes);
        if (node != nullptr) {
            DIRECTORY *dir = static_cast<DIRECTORY *>(node);
            if (dir->is_directory)
                DIRECTORY::working_directory = dir;
            else
                printf("The file is not a directory.");
        }
        else
            printf("Directory not found");
    }
    else if (strncmp(cmd, "dump ", 5) == 0) {
        char *filename = &cmd[5];
        NODE *node = NODE::find(filename, DIRECTORY::working_directory->in_nodes);
        if (node == 0)
            printf("File not found");
        else {
            int newline = 102;
            int address = 0;
            char chview[30];
            int chview_index = 0;
            for (int i = 0; i < node->size; i++) {
                char ch = node->stream[i];
                char addr[20];
                printf_set_mode(HEX_ZERO_COUNTS, 8);
                sprintf(addr, "%x\0", address);
                newline++;
                if (newline > 15) {
                    newline = 0;
                    if (newline != 102) {
                        if (chview_index > 0)
                            printf("|%s|", chview);
                        print_char('\n');
                        printf("%s: ", addr);
                        chview_index = 0;
                    }
                    else
                        printf("%s: ", addr);
                    address += 0x10;
                }
                printf_set_mode(HEX_ZERO_COUNTS, 2);
                char byte[5];
                sprintf(byte, "%x ", ch);
                printf(byte);

                if (ch != 0 && ch < 128 && ch != '\n' && ch != 0x20)
                    chview[chview_index] = ch;
                else
                    chview[chview_index] = '.';
                chview_index++;
                chview[chview_index+1] = 0;
            }
        }
        clear_string(cmd, 100);
    }
    else if (strncmp(cmd, "cat ", 4) == 0) {
    
        char *filename = &cmd[4];
        NODE *node = NODE::find(filename, DIRECTORY::working_directory->in_nodes);
        if (node == 0)
            printf("File not found");
        else
            printf(node->stream);
        clear_string(cmd, 100);
    }
    else if (strcmp(cmd, "cls") == 0) {
        print_clear();
    }
    else if (strcmp(cmd, "pc") == 0) {
        DIRECTORY::working_directory = DIRECTORY::my_pc;
    }
    else if (strncmp(cmd, "createfs ", 8) == 0) {
        char *filename = new char(70);
        strcpy(filename, cmd);
        DIRECTORY dir = DIRECTORY(DIRECTORY::my_pc, &filename[9]);
    }
    else if (strncmp(cmd, "./", 2) == 0) {
        if (strcmp(&cmd[2], "tictactoe") == 0) {
            tictactoe *prg = new tictactoe();
            prg->main();
            delete prg;
        }
        else if (strcmp(&cmd[2], "word") == 0) {
            word *prg = new word();
            prg->main();
            delete prg;
        }
        clear_string(cmd, 100);
    }
    else if (strncmp(cmd, "mkdir ", 6) == 0) {
        char *filename = new char(70);
        strcpy(filename, cmd);
        DIRECTORY dir = DIRECTORY(DIRECTORY::working_directory, &filename[6]);
    }
    else if (strncmp(cmd, "touch ", 6) == 0) {
        char *filename = new char(70);
        strcpy(filename, cmd);
        NODE dir = NODE(DIRECTORY::working_directory, &filename[6], "\0");
    }
    else if (strncmp(cmd, "echo ", 5) == 0) {
        char str[60];
        bool found = false;
        int fi = 0;
        for (int i = 5;; i++) {
            if (cmd[i] == '\"') {
                if (!found)
                    found = true;
                else {
                    str[fi] = 0;
                    break;
                }
            }
            else if (found) {
                str[fi] = cmd[i];
                fi++;
            }
        }
        printf(str);
    }
    else if (cmd[0] == 0) {

    }
    else {
        printf("Unknown command");
    }
}
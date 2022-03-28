#ifndef FS_H
#include "sys/utils.h"
#define FS_H
class NODE;
class DIRECTORY;
void add_node_to_directory(DIRECTORY *dir, NODE *node);
void fs_error();
void check_fs();
void update_system();
class NODE {
    public:
        bool is_directory = false;
        char *stream;
        char *filename;
        int size;
        NODE(DIRECTORY *dir, char *filename, char *stream) : NODE(dir, filename, stream, strlen(stream)) {

        }
        NODE(DIRECTORY *dir, char *filename, char *stream, int size) {
            this->filename = filename;
            this->stream = stream;
            this->size = size;
            if (dir != nullptr)
                add_node_to_directory(dir, this);
        }
        static NODE *find(char *filename, NODE *dir[100]) {
            if (dir == nullptr || !filename || filename == nullptr) {
                fs_error();
            }
            for (int i = 0; i < 100; i++) {
                if (dir[i] != nullptr && strcmp(filename, dir[i]->filename) == 0) {
                    return dir[i];
                }
            }
            return 0;
        }
};
class DIRECTORY : public NODE {
    public:
        static DIRECTORY *working_directory;
        static DIRECTORY *fs_directory;
        static DIRECTORY *my_pc;
        NODE *in_nodes[100];
        int node_top = 0;
        DIRECTORY(DIRECTORY *dir, char *dir_name) : NODE(dir, dir_name, "directory") {
            is_directory = true;
        }
};
#endif
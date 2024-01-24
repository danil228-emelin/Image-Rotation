#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


struct file{
    FILE *open_file;
    bool valid;
};
struct file new_empty_file();
struct file new_file(char *fileName,char * privileges);
bool fclose_file(struct file file);
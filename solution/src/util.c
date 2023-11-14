//working with file 
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
 char* argv[];
struct file{
    FILE *open_file;
    bool valid;
};

struct file new_empty_file(){
    return (struct file){0};
}
struct file new_file(char *fileName,char * privileges){
    struct file file=new_empty_file();
    file.open_file=fopen(argv[1], privileges);
    if(file.open_file) file.valid=true; 
}
#include <stdio.h>
#include <errno.h>
#include "../include/util.h"
#include <string.h>
int main( int argc, char* argv[] ) {
   if (argc!=4)
      {
        fprintf(stderr," current argc-%d \n necessary format: ./image-transformer <source-image> <transformed-image> <angle>\n",argc);
        return 1;
      }
    
struct file file=new_file(argv[1],"rb");
 if (!file.valid){
fprintf(stderr,"Error code-%d.\nExplanation:",errno); 
fprintf(stderr,strerror(errno));
fprintf(stderr, "\nCannot open file %s\n",argv[1]);
        return 1;
 }  

    return 0;
}

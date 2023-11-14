#include "../include/bpm.h"
#include "../include/image.h"
#include "../include/rotation.h"
#include "../include/util.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr,
            " current argc-%d \n necessary format: ./image-transformer "
            "<source-image> <transformed-image> <angle>\n",
            argc);
    return 1;
  }

  struct file file = new_file(argv[1], "rb");
  if (!file.valid) {
    fprintf(stderr, "Error code-%d.\nExplanation:", errno);
    fprintf(stderr, strerror(errno));
    fprintf(stderr, "\nCannot open source bmp file %s\n", argv[1]);
    return 1;
  }

  struct image image = {0};
  if (from_bmp(in, &image) != READ_OK) {
    fprintf(stderr, "\n Error during reading source bpm file\n");
    image_destroy(&image);
    fclose_file(file);
    return 1;
  }
   uint64_t angle = (atoi(argv[3]) + 360) % 360;
    if (angle != 0 && angle != 90 && angle != 180 && angle != 270) {
        image_destroy(&image);
        fprintf(stderr, "Invalid angel. Accepted only: 0, 90, -90, 180, -180, 270, -270\n");
        return 1;
    }
 uint64_t rotations = (4 - angle / 90) % 4;
    for (uint64_t i = 0; i < rotations; i++) {
        struct image rotated = rotate(image);
        image_destroy(&image);
        image = rotated;
    }
       struct file file_write = new_file(argv[2], "wb");
  if (!file_write.valid) {
    fprintf(stderr, "Error code-%d.\nExplanation:", errno);
    fprintf(stderr, strerror(errno));
    fprintf(stderr, "\nCannot open file %s\n", argv[1]);
        image_destroy(&image);
    return 1;
  }

    if (to_bmp(file_write.open_file, &image) != WRITE_OK) {
        fprintf(stderr, "Error during writing\n");
        image_destroy(&image);
            fclose_file(file_write);
        return 1;
    }

    image_destroy(&image);
              fclose_file(file_write);
    fprintf(stdout, "Image has been rotated\n");
    return 0;
}



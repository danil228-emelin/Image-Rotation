#include "../include/image.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct image image_create(const uint64_t width, const uint64_t height) {
  return (struct image){.height = height,
                        .width = width,
                        .data = calloc(sizeof(struct pixel) * width * height)};
}

bool image_destroy(struct image *image) {
  if (image->data == NULL) {
    return false;
  }
  free(image->data);
  return true;
}

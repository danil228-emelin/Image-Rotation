#include "../include/rotation.h"
#include "../include/image.h"
#include <stdint.h>

struct image rotate(struct image const source) {
  struct image image = image_create(source.height, source.width);
  for (uint64_t i = 0; i < source.height; i++) {
    for (uint64_t j = 0; j < source.width; j++) {
      image.data[source.height * (j + 1) - i - 1] =
          source.data[source.width * i + j];
    }
  }
  return image;
}

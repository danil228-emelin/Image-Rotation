#include <stdint.h>
#include <stdbool.h>

struct __attribute__((packed)) pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel *data;
};

struct image image_create(const uint64_t width, const uint64_t height);

bool image_destroy(struct image *image);

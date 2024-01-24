#include "../include/bpm.h"
#include "../include/image.h"
#include <stdint.h>
#include <stdio.h>

#define BFtype 19778
#define BFBITCount 24
#define BFReserved 0
#define BOffBits 54
#define BISize 40
#define BIPlanes 1
#define BICompression 0
#define BIXPelsPerMetr 2834
#define BIYPelsPerMetr 2834
#define BIClrUsed 0
#define BIClrImportant 0

static uint64_t get_padding(const uint64_t width) {
  return (4 - (width * 3) % 4) % 4;
}

enum read_status from_bmp(FILE *in, struct image *img) {
  struct bmp_header bmp = {0};
  if (!fread(&bmp, sizeof(struct bmp_header), 1, in)) {
    return READ_INVALID_HEADER;
  }
  if (bmp.bfType != BFtype) {
    return READ_INVALID_SIGNATURE;
  }
  if (bmp.biBitCount != BFBITCount) {
    return READ_INVALID_BITS;
  }
  *img = image_create(bmp.biWidth, bmp.biHeight);
  uint32_t padding = get_padding(img->width);
  for (uint32_t i = 0; i < bmp.biHeight; i++) {
    if (fread(img->data + i * bmp.biWidth, sizeof(struct pixel), bmp.biWidth,
              in) != bmp.biWidth) {
      return READ_INVALID_PIXEL_LINE;
    }
    if (fseek(in, (long)padding, SEEK_CUR) != 0) {
      return FAILED_TO_SKIP_TRASH;
    }
  }
  return READ_OK;
}

enum write_status to_bmp(FILE *out, struct image const *img) {
  uint64_t padding = get_padding(img->width);
  struct bmp_header bmp_header = {0};
  bmp_header.bfType = BFtype;
  bmp_header.biSizeImage =
      (uint64_t)((sizeof(struct pixel) * img->width + padding) * img->height);
  bmp_header.bfileSize = bmp_header.biSizeImage + sizeof(struct bmp_header);
  bmp_header.bfReserved = BFReserved;
  bmp_header.bOffBits = BOffBits;
  bmp_header.biSize = BISize;
  bmp_header.biWidth = (uint64_t)img->width;
  bmp_header.biHeight = (uint64_t)img->height;
  bmp_header.biPlanes = BIPlanes;
  bmp_header.biBitCount = BFBITCount;
  bmp_header.biCompression = BICompression;
  bmp_header.biXPelsPerMeter = BIXPelsPerMetr;
  bmp_header.biYPelsPerMeter = BIYPelsPerMetr;
  bmp_header.biClrUsed = BIClrUsed;
  bmp_header.biClrImportant = BIClrImportant;
  if (fwrite(&bmp_header, sizeof(bmp_header), 1, out) != 1) {
    return WRITE_ERROR;
  }

  for (uint64_t i = 0; i < img->height; i++) {
    if (fwrite(img->data + i * (img->width), 3, img->width, out) !=
        img->width) {
      return WRITE_ERROR;
    }
    uint64_t remains[] = {0, 0, 0, 0};
    fwrite(remains, 1, padding, out);
  }
  return WRITE_OK;
}

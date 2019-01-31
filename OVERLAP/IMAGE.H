#ifndef IMAGE_H
#define IMAGE_H
#include "types.h"

void image_put(image_t *image, byte_t *dest);
void image_put_colorkey(image_t *image, byte_t *dest, byte_t color_key);
#endif
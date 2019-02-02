#ifndef SPRITE_H
#define SPRITE_H

#include "types.h"

void sprite_init(sprite_t *sprite, word_t w,
word_t h, word_t x, word_t y);
void sprite_delete(sprite_t *sprite);
void sprite_get(sprite_t *sprite, image_t *image, word_t frame);
void sprite_draw(sprite_t *sprite, byte_t *dest);
#endif
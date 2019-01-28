#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

#define VIDEO_INT          0x10
#define SET_MODE           0x00
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE          0x03
#define SCREEN_WIDTH       320
#define SCREEN_HEIGHT      200
#define NUM_COLORS         256
#define PALETTE_INDEX      0x03C8
#define PALETTE_DATA       0x03C9

void setmode(byte_t mode);
void setpixel(int x, int y, byte_t color);
void setpalette(byte_t *palette);
void vgacpy(byte_t *src, word_t offset, int len);
void vgaset(word_t offset, byte_t value, int len);
void vgafill(word_t color);
#endif
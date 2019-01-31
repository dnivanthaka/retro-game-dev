#ifndef TYPES_H
#define TYPES_H
typedef unsigned char  byte_t;
typedef unsigned short word_t;
typedef unsigned int   dword_t;
typedef struct xy{
	unsigned short x, y;
} xy_t;
typedef struct rgb{
	byte_t r, g, b;
} rgb_t;
typedef struct palette{
	word_t start_reg, end_reg;
	rgb_t colors[256];
} rgb_palette_t;

typedef struct image{
	word_t x, y, width, height;
	byte_t *data;
} image_t;

#endif

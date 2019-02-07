#ifndef TYPES_H
#define TYPES_H

#define MAX_SPRITE_FRAMES 4

typedef unsigned char  byte_t;
typedef unsigned short word_t;
typedef unsigned int   dword_t;
typedef unsigned long  qword_t;

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
	//bool is_transparent;
	byte_t colorkey;
	byte_t *data;
} image_t;

typedef enum sp_state {
	DEAD, MOVING, STANDING
} sp_state_t;

typedef struct sprite{
	word_t width, height, x, y;
	byte_t num_frames;
	byte_t current_frame;
	sp_state_t state;
	word_t counter_1;
	byte_t *background;
	byte_t *frames[MAX_SPRITE_FRAMES];
} sprite_t;

#endif

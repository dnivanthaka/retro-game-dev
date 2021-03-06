#include <stdlib.h>
#include <mem.h>
#include "screen.h"
#include "sprite.h"

void sprite_init(
sprite_t *sprite, word_t w,
word_t h, word_t x, word_t y)
{
	int i;

	sprite->width  = w;
	sprite->height = h;
	sprite->x = x;
	sprite->y = y;
	sprite->num_frames    = 0;
	sprite->current_frame = 0;
	sprite->state         = DEAD;
	sprite->counter_1     = 0;
	sprite->background    = (byte_t *)malloc(w * h);
	for(i=0;i<MAX_SPRITE_FRAMES;i++){
		sprite->frames[i] = NULL;
	}
}

void sprite_delete(sprite_t *sprite)
{
	int i;

	free(sprite->background);
	for(i=0;i<MAX_SPRITE_FRAMES;i++){
		free(sprite->frames[i]);
	}
}

void sprite_get(
sprite_t *sprite, image_t *image, word_t frame)
{
	int i;
	dword_t offset = image->width * frame + 1;

	byte_t *sprite_data;

	sprite_data = sprite->frames[frame];
	byte_t *src_data = &image->data[image->width * (frame + 1)];

	sprite->frames[frame] = (byte_t *)malloc(sprite->width * sprite->height + 1);
	for(i=0;i<sprite->height;i++){
		//memcpy(&sprite_data[sprite->width * i], &image->data[offset], sprite->width);
		//memcpy(sprite->frames[0], src_data + offset, sprite->width * sprite->height);
		memcpy(VGAMEM + (image->width * i), src_data + offset, sprite->width);
		offset += image->width;
	}

	sprite->num_frames++;

	//memcpy(VGAMEM, sprite->frames[0], sprite->width * sprite->height);
}

void sprite_draw(sprite_t *sprite, byte_t *dest)
{
	int i;
	dword_t offset = sprite->y * SCREEN_WIDTH + sprite->x;
	byte_t *dest_buffer = (byte_t *)dest[offset];
	byte_t *src_buffer = sprite->frames[sprite->current_frame];

	for(i=0;i<sprite->height;i++){
		memcpy(dest_buffer, src_buffer, sprite->width);
		dest_buffer += SCREEN_WIDTH;
		src_buffer += sprite->width;
	}
}
#include <mem.h>
#include <stdio.h>
#include "types.h"
#include "screen.h"

void image_put(image_t *image, byte_t *dest)
{
	int i, j;

	long dest_offset = image->y * SCREEN_WIDTH + image->x;
	long offset = 0;
	for(i=0;i<image->height;i++){
		memcpy((byte_t *)&dest[dest_offset], (byte_t *)&image->data[offset],
		image->width);
		offset += image->width;
		dest_offset += SCREEN_WIDTH;
	}
}

void image_put_colorkey(image_t *image, byte_t *dest, byte_t color_key)
{
	int i, j;

	long dest_offset = image->y * SCREEN_WIDTH + image->x;
	long offset = 0;
	for(i=0;i<image->height;i++){
		for(j=0;j<image->width;j++){
			if(image->data[offset + j] != color_key)
				dest[dest_offset + j] = image->data[offset + j];
		}
		offset += image->width;
		dest_offset += SCREEN_WIDTH;
	}
}
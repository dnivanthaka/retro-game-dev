#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include "screen.h"
#include "pcx.h"
#include "image.h"

int main(int argc, char *argv[])
{
	pcx_picture_t background, worm;
	read_pcx("mushroom.pcx",  &background);
	read_pcx("wormimg.pcx", &worm);

	setmode(VGA_256_COLOR_MODE);

	setpalette(0, 255, &background.palette);

	image_t back_image, worm_image;

	pcx_to_image(&background, &back_image);
	pcx_to_image(&worm, &worm_image);

	image_put(&back_image, VGAMEM);
	image_put_colorkey(&worm_image, VGAMEM, 0);
	word_t offset = 100 * SCREEN_WIDTH + 100; //y * width + x

	while(!kbhit());

	setmode(TEXT_MODE);
	pcx_delete(&background);

	return 0;
}
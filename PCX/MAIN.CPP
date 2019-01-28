#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include "screen.h"
#include "pcx.h"

int main(void)
{
	pcx_picture_t image;

	read_pcx("alienimg.pcx",  &image);

	printf("%d\n", image.header.pcx_window.x_max);

	setmode(VGA_256_COLOR_MODE);

	setpalette((byte_t *)&image.palette.triples);

	vgacpy(image.buffer, 0, image.header.pcx_window.x_max * image.header.pcx_window.y_max);

	while(!kbhit());

	setmode(TEXT_MODE);
	return 0;
}
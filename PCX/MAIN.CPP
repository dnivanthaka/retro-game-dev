#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include "screen.h"
#include "pcx.h"

int main(int argc, char *argv[])
{
	if(argc == 1){
		printf("Usage : %s [file name]\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	pcx_picture_t image;
	read_pcx(argv[1],  &image);
	setmode(VGA_256_COLOR_MODE);

	setpalette((byte_t *)&image.palette.triples[0]);

	vgacpy(image.buffer, 0, image.header.pcx_window.x_max * image.header.pcx_window.y_max);

	while(!kbhit());

	setmode(TEXT_MODE);
	printf("\n");
	printf("Width = %d\n", (int)image.header.pcx_window.x_max);
	printf("Height = %d\n", (int)image.header.pcx_window.y_max);
	printf("Bits per Pixel : %d\n", image.header.bitsperpixel);
	printf("\n");
	return 0;
}
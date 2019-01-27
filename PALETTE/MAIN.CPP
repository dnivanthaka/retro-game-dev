#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "screen.h"

word_t *sys_clock = (word_t *)0x0000046C;

int main(void)
{
	int i, j;

	srand(*sys_clock);
	setmode(VGA_256_COLOR_MODE);

	for(i=0;i<256;i++){
		setpixel(10 + i, 10, i);
	}
	while(!kbhit());
	setmode(TEXT_MODE);

	return 0;
}
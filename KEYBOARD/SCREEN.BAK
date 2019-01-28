#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include "screen.h"

byte_t *VGAMEM = (byte_t *)0xA0000000L;


void setmode(byte_t mode)
{
	union REGS regs;
	regs.h.ah = SET_MODE;
	regs.h.al = mode;
	int86(VIDEO_INT, &regs, &regs);
}

void setpixel(int x, int y, byte_t color)
{
	VGAMEM[y * SCREEN_WIDTH + x] = color;
}

void setpalette(byte_t *palette)
{
	int i;

	outp(PALETTE_INDEX, 0);
	for(i = 0; i < 256*3; i++){
		outp(PALETTE_DATA, *(palette + i));
	}
}

void vgacpy(byte_t *src, word_t offset, int len)
{
	memcpy(&VGAMEM[offset], src, len);
}

void vgaset(word_t offset, byte_t value, int len)
{
	memset(&VGAMEM[offset], value, len);
}

void vgafill(word_t color)
{
	/*asm {
		push bp
		mov bp, sp
		push di
		les di, VGAMEM
		mov cx, SCREEN_WIDTH/4 * SCREEN_HEIGHT
		mov ax, color
		rep stosw
		pop di
		pop bp
	};*/
	memset(VGAMEM, color, SCREEN_WIDTH * SCREEN_HEIGHT);
}
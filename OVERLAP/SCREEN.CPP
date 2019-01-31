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

byte_t getpixel(int x, int y)
{
	return VGAMEM[y * SCREEN_WIDTH + x];
}

void setpalette(int start_reg,int end_reg, rgb_palette_t *palette)
{
	int i;

	for(i = start_reg; i <= end_reg; i++){
		write_color_reg(i, &palette->colors[i]);
	}
}

void getpalette(int start_reg,int end_reg, rgb_palette_t *palette)
{
	int i;
	rgb_t color;

	for(i = start_reg; i <= end_reg; i++){
		read_color_reg(i, (rgb_t *)&color);

		palette->colors[i].r = color.r;
		palette->colors[i].g = color.g;
		palette->colors[i].b = color.b;
	}

	palette->start_reg = start_reg;
	palette->end_reg = end_reg;
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
	asm {
		les di, VGAMEM
		mov cx, SCREEN_WIDTH * SCREEN_HEIGHT / 2
		mov al, BYTE PTR color
		mov ah, al
		rep stosw
	};
}

void read_color_reg(int index, rgb_t *color)
{
	outp(COLOR_REGISTER_RD, index);

	color->r = (byte_t)inp(PALETTE_DATA);
	color->g = (byte_t)inp(PALETTE_DATA);
	color->b = (byte_t)inp(PALETTE_DATA);
}

void write_color_reg(int index, rgb_t *color)
{
	outp(COLOR_REGISTER_WR, index);

	outp(PALETTE_DATA, color->r);
	outp(PALETTE_DATA, color->g);
	outp(PALETTE_DATA, color->b);
}

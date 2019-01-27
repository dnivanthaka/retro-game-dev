#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include "screen.h"

typedef struct tabBITMAP {
	word_t width;
	word_t height;
	byte_t palette[256 * 3];
	byte_t *data;
} BITMAP;

void fskip(FILE *fp, int num_bytes)
{
	int i;
	for(i=0;i<num_bytes;i++){
		fgetc(fp);
	}
}

void load_bmp(char *file, BITMAP *b)
{
	FILE *fp;
	long index;
	word_t num_colors;
	int x;

	if((fp = fopen(file, "rb")) == NULL){
		printf("Error opening file %s.\n", file);
		exit(EXIT_FAILURE);
	}

	if(fgetc(fp) != 'B' || fgetc(fp) != 'M'){
		fclose(fp);
		printf("%s is not a bitmap file.\n", file);
		exit(EXIT_FAILURE);
	}

	fskip(fp, 16);
	fread(&b->width, sizeof(word_t), 1, fp);
	fskip(fp, 2);
	fread(&b->height, sizeof(word_t), 1, fp);
	fskip(fp, 22);
	fread(&num_colors, sizeof(word_t), 1, fp);
	fskip(fp, 6);

	if(num_colors == 0) num_colors = 256;

	if((b->data = (byte_t *)malloc((word_t)(b->width * b->height))) == NULL){
		fclose(fp);
		printf("Error allocating memory for file %s.\n", file);
		exit(EXIT_FAILURE);
	}

	//Reading palette info
	for(index = 0; index < num_colors; index++){
		b->palette[(int)(index * 3 + 2)] = fgetc(fp) >> 2;
		b->palette[(int)(index * 3 + 1)] = fgetc(fp) >> 2;
		b->palette[(int)(index * 3 + 0)] = fgetc(fp) >> 2;
		x = fgetc(fp);
	}

	//Reading bitmap data
	for(index=(b->height-1)*b->width;index>=0;index-=b->width){
		for(x=0;x<b->width;x++){
			b->data[(word_t)index + x] = (byte_t)fgetc(fp);
		}
	}

	fclose(fp);
}

void draw_bitmap(BITMAP *bmp, int x, int y)
{
	int j;
	word_t screen_offset = (y << 8) + (y << 6) + x;
	word_t bitmap_offset = 0;

	for(j=0;j<bmp->height;j++){
		vgacpy(&bmp->data[bitmap_offset], screen_offset, bmp->width);
		bitmap_offset += bmp->width;
		screen_offset += SCREEN_WIDTH;
	}
}

void draw_bitmap_wcolorkey(BITMAP *bmp, byte_t key, int x, int y)
{
	int j, i;
	word_t screen_offset = (y << 8) + (y << 6) + x;
	word_t bitmap_offset = 0;

	for(j=0;j<bmp->height;j++){
		for(i=0;i<bmp->width;i++, bitmap_offset++){
			if(key != bmp->data[bitmap_offset]){
				vgaset(screen_offset + i, bmp->data[bitmap_offset], 1);
			}
		}
		screen_offset += SCREEN_WIDTH;
	}

}

int main(void){
	int i;
	BITMAP bmp;

	load_bmp("rocket.bmp", &bmp);

	setmode(VGA_256_COLOR_MODE);

	//drawing a pattern
	/*for(i=0;i<SCREEN_HEIGHT;i++){
		vgaset(SCREEN_WIDTH * i, i, SCREEN_WIDTH);
	}*/
	//set palette
	setpalette(bmp.palette);
	draw_bitmap_wcolorkey(&bmp, 0, 100, 100);

	while(!kbhit());

	free(bmp.data);

	setmode(TEXT_MODE);

	return 0;
}


#ifndef TYPES_H
#define TYPES_H
typedef unsigned char  byte_t;
typedef unsigned short word_t;
typedef unsigned long  qword_t;
typedef struct xy{
	unsigned short x, y;
} xy_t;
typedef struct color{
	byte_t r, g, b;
} color_t;
#endif
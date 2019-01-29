#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

word_t far *clock = (word_t *)0x0000046C;
qword_t start_time = 0;

void timer_start()
{
	start_time = *clock;
}

qword_t timer_getticks()
{
	return *clock - start_time;
}

void timer_delay(word_t ticks)
{
	while((*clock - start_time) < ticks){
	}
}

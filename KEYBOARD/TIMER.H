#ifndef TIMER_H
#define TIMER_H
#include "types.h"

//extern dword_t *clock;
//qword_t start_time;

void timer_start();
qword_t timer_getticks();
void timer_delay(word_t ticks);
#endif
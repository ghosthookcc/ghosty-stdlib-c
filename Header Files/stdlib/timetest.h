#ifndef TIMETEST_H
#define TIMETEST_H

#include <time.h>
#include <stdio.h>

struct timer_t
{
	clock_t start;
	clock_t stop;
	clock_t (*time)(void);
	double delta;
};
typedef struct timer_t timer;

static const timer TimerDefault = { .start = 0, .stop = 0, .time = clock, .delta = 0.0 };

void timerStart(timer* timed);
void timerStop(timer* timed);

double timerDelta(timer* timed);
void timerPrintDelta(timer timed);

#endif
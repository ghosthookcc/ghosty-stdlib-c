#include "../../Header Files/stdlib/timetest.h"

void timerStart(timer* timed)
{
	timed->start = timed->time();
}

void timerStop(timer* timed)
{
	timed->stop = timed->time();
}

double timerDelta(timer* timed)
{
	double deltaInSeconds = (double)(timed->stop - timed->start) / CLOCKS_PER_SEC;
	timed->delta = deltaInSeconds;
	return deltaInSeconds;
}

void timerPrintDelta(timer timed, const char* header)
{
	printf("\n%sTimer delta is %.16f seconds . . .\n", header, timerDelta(&timed));
}
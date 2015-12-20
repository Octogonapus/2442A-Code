#ifndef TIMER_C_INCLUDED
#define TIMER_C_INCLUDED

#include "timer.h"

long timer_GetDT(timer* timer)
{
	long dt = time1[T1] - timer->lastCalled;
	timer->lastCalled = time1[T1];
	return dt;
}

long timer_GetStartingTime(timer* timer)
{
	return timer->firstCalled;
}

long timer_GetDTFromStart(timer* timer)
{
	return time1[T1] - timer->firstCalled;
}

void timer_Initialize(timer* timer)
{
	timer->firstCalled = time1[T1];
	timer->lastCalled = 0;
}

#endif //TIMER_C_INCLUDED

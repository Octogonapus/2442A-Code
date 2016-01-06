#ifndef TIMER_C_INCLUDED
#define TIMER_C_INCLUDED

#include "timer.h"

void timer_Initialize(timer* timer)
{
	timer->firstCalled = nSysTime;
	timer->lastCalled = 0;
}

long timer_GetDT(timer* timer)
{
	long dt = nSysTime - timer->lastCalled;
	timer->lastCalled = nSysTime;
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

#endif //TIMER_C_INCLUDED

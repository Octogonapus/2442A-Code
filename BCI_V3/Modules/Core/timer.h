#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

//Timer struct
typedef struct timer
{
  long firstCalled; //Time the timer was initialzied
  long lastCalled;  //Last time in ms the timer was called
} timer;

//Intiialize a timer
void timer_Intialize(timer* timer);

//Get time passed in ms since previous call of this function
long timer_GetDT(timer* timer);

//Get the timer the timer was first initialized
long timer_GetStartingTime(timer* timer);

//Get the time since the timer was first initialized
long timer_GetDTFromStart(timer* timer);

#endif //TIMER_H_INCLUDED

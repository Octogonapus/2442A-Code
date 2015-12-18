#ifndef REDLEFTAUTONTERTIARY_H_INCLUDED
#define REDLEFTAUTONTERTIARY_H_INCLUDED

#include "..\autonFunctions.c"

void redLeftAutonTertiary()
{
	startTask(motorSlewRateTask);

	//Robot starts pointing at the center of the high goal
	//Shoot all 4 preloads
	//Turn left and point at the stack offset from the field wall
	//Drive forward and pick up the stack
	//Turn right and point at an area offset from the stack on top of the vertex of the blue team's triangle
	//Drive forward to the other side of the field
}

#endif

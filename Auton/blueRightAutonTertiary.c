#ifndef BLUERIGHTAUTONTERTIARY_H_INCLUDED
#define BLUERIGHTAUTONTERTIARY_H_INCLUDED

#include "..\autonFunctions.c"

void blueRightAutonTertiary()
{
	startTask(motorSlewRateTask);

	//Robot starts pointing at the center of the high goal
	//Shoot all 4 preloads
	//Turn right and point at the stack offset from the field wall
	//Drive forward and pick up the stack
	//Turn left and point at an area offset from the stack on top of the vertex of the red team's triangle
	//Drive forward to the other side of the field
}

#endif

#ifndef REDRIGHTAUTONTERTIARY_H_INCLUDED
#define REDRIGHTAUTONTERTIARY_H_INCLUDED

#include "..\autonFunctions.c"

void redRightAutonTertiary()
{
	startTask(motorSlewRateTask);

	//Robot starts pointing at the center of the high goal
	//Shoot all 4 preloads
	//Turn right slightly
	//Drive forward so that the center of rotation of the robot is inline with the horizontal line intersecting the two stacks in the middle of the field on opposite sides
	//Turn left and point at the stack in the middle of the field against the field wall on the blue team's side
	//Drive forward and pick up that stack
}

#endif

#ifndef BLUELEFTAUTONTERTIARY_H_INCLUDED
#define BLUELEFTAUTONTERTIARY_H_INCLUDED

#include "..\autonFunctions.c"

void blueLeftAutonTertiary()
{
	startTask(motorSlewRateTask);

	//Robot starts pointing at the center of the high goal
	//Shoot all 4 preloads
	//Turn left slightly
	//Drive forward so that the center of rotation of the robot is inline with the horizontal line intersecting the two stacks in the middle of the field on opposite sides
	//Turn right and point at the stack in the middle of the field against the field wall on the red team's side
	//Drive forward and pick up that stack
}

#endif

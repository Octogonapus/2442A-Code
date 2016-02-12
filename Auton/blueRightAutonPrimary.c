#ifndef BLUERIGHTAUTONPRIMARY_H_INCLUDED
#define BLUERIGHTAUTONPRIMARY_H_INCLUDED

#include "..\autonFunctions.c"

void blueRightAutonPrimary()
{
	//Launch four preloads
	launchFourBalls(95);

	////Turn and face the stack offset from the wall
	//turnGyro(60, 35);

	////Drive forward and pick up the stack
	//setIntakeMotors(127);
	//driveQuad(127, 650);
	//driveQuad(40, 350);
	//setIntakeMotors(0);

	////Turn slightly left to avoid hitting the wall at the starting tile
	//turnGyro(60, 1);

	////Drive back to the starting tile
	//driveQuad(-127, 970);
}

#endif

#ifndef BLUELEFTAUTONPRIMARY_H_INCLUDED
#define BLUELEFTAUTONPRIMARY_H_INCLUDED

#include "..\autonFunctions.c"

void blueLeftAutonPrimary()
{
	//Launch four preloads
	launchFourBalls(90);

	////Turn and face near the stack against the wall
	//turnGyro(-60, 30);

	////Drive forward to be on top of the point in front of that stack
	//driveQuad(127, 1100);

	////Turn left and face the stack against the wall
	//turnGyro(-80, 125);

	////Drive forward and intake the stack
	//setIntakeMotors(127);
	//driveTime(60, 60, 3000);
	//setIntakeMotors(0);

	////Drive back from the wall
	//driveQuad(-127, 200);

	////Turn right and have back face the starting tile
	//turnGyro(80, 130);

	////Drive back onto the starting tile
	//driveQuad(-127, 900);
}

#endif

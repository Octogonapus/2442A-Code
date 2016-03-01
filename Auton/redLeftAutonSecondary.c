#ifndef REDLEFTAUTONSECONDARY_H_INCLUDED
#define REDLEFTAUTONSECONDARY_H_INCLUDED

#include "..\autonFunctions.c"

void redLeftAutonSecondary()
{
	//Launch four preloads
	launchFourBalls(195);

	//Turn and face the stack offset from the wall
	turnGyro(-30);

	//Drive forward to be on top of the stack offset from the wall
	driveQuad(127, 1100);

	//Turn left and face the stack against the wall
	turnGyro(-100);

	//Drive forward and intake the stack
	setIntakeMotors(127);
	driveTime(40, 40, 3500);
	setIntakeMotors(0);

	//Drive back from the wall
	driveQuad(-127, 200);

	//Turn right and have back face the starting tile
	turnGyro(120);

	//Drive back onto the starting tile
	driveQuad(-127, 900);
}

#endif

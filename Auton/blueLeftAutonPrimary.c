#ifndef BLUELEFTAUTONPRIMARY_H_INCLUDED
#define BLUELEFTAUTONPRIMARY_H_INCLUDED

#include "..\autonFunctions.c"

void blueLeftAutonPrimary()
{
	launchFourBalls(85);

	//Drive forward out from starting tile
	driveQuad(110, 300);

	//Turn left to be parallel with the field wall
	turnGyro(100, 46);

	//Drive forward to be next to stack against field wall
	driveQuad(110, 600);

	//Turn right to point at the stack against the field wall
	turnGyro(100, 96);

	//Intake the stack
	driveQuad(110, 150);
	driveAndIntakeTime(30, 30, 2000);
	wait1Msec(500);
	driveAndIntakeTime(30, 30, 1000);

	//Drive back from wall
	driveQuad(-110, 200);

	//Turn right to face net
	turnGyro(-100, -175);
}

#endif

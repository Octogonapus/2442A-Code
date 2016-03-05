#ifndef REDRIGHTAUTONPRIMARY_H_INCLUDED
#define REDRIGHTAUTONPRIMARY_H_INCLUDED

#include "..\autonFunctions.c"

void redRightAutonPrimary()
{
	//Launch four preloads
	launchFourBalls(91);

	//Drive forward out from starting tile
	driveQuad(110, 300);

	//Turn left to be parallel with the field wall
	turnGyro(-46);

	//Drive forward to be next to stack against field wall
	driveQuad(110, 600);

	//Turn right to point at the stack against the field wall
	turnGyro(-90);

	//Intake the stack
	driveQuad(110, 150);
	driveAndIntakeTime(30, 30, 2250);
	wait1Msec(500);
	driveAndIntakeTime(30, 30, 1000);

	//Drive back from wall
	driveQuad(-110, 200);

	//Turn right to face net
	turnGyro(175);
}

#endif

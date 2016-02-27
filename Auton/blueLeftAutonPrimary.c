#ifndef BLUELEFTAUTONPRIMARY_H_INCLUDED
#define BLUELEFTAUTONPRIMARY_H_INCLUDED

#include "..\autonFunctions.c"

void blueLeftAutonPrimary()
{
	//Launch four preloads
	launchFourBalls(90);

	//Drive forward out from starting tile
	driveQuad(110, 200);

	//Turn left to be parallel with the field wall
	turnGyro(-100, 43);

	//Drive forward to be next to stack against field wall
	driveQuad(110, 100);

	//Turn left to be pointed at stack against field wall
	turnGyro(-100, 90);

	//Drive forward and intake stack
	driveQuad(110, 80);
	driveAndIntakeTime(90, 90, 3000);
}

#endif

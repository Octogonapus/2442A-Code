#ifndef PROGRAMMINGSKILLS_H_INCLUDED
#define PROGRAMMINGSKILLS_H_INCLUDED

#include "..\autonFunctions.c"

//Blue left
void programmingSkills()
{
	//Driver loads
	launchThirtyTwoBalls();

	//Turn right and point at the red tile
	turnGyro(-91);

	//Drive onto the red tile
	//driveQuad(110, 3000);
	driveTime(127, 80, 3500);

	//Turn left and point at the red high goal
	turnGyro(90);

	//Driver loads
	launchThirtyTwoBalls();
}

#endif //PROGRAMMINGSKILLS_H_INCLUDED

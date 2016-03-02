#ifndef PROGRAMMINGSKILLS_H_INCLUDED
#define PROGRAMMINGSKILLS_H_INCLUDED

#include "..\autonFunctions.c"

//Blue left
void programmingSkills()
{
	//Driver loads
	launchThirtyTwoBalls(76);

	//Turn right and point at the red tile
	turnGyro(-90);

	//Drive onto the red tile
	driveQuad(110, 3000);

	//Turn left and point at the red high goal
	turnGyro(90);

	//Driver loads
	launchThirtyTwoBalls(76);
}

#endif //PROGRAMMINGSKILLS_H_INCLUDED

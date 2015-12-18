#ifndef PROGRAMMINGSKILLS_H_INCLUDED
#define PROGRAMMINGSKILLS_H_INCLUDED

#include "..\autonFunctions.c"

//Blue left
void programmingSkills()
{
	//Driver loads
	startTask(maintainLauncherForAuton);
	setIntakeMotors(127);
	wait1Msec(50000);

	//Turn right and point at the red tile
	turnGyro(80, 20);

	//Drive onto the red tile
	driveQuad(127, 3000);

	//Turn left and point at the red high goal

	//Driver loads
}

#endif

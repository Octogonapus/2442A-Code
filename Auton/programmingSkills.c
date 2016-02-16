#ifndef PROGRAMMINGSKILLS_H_INCLUDED
#define PROGRAMMINGSKILLS_H_INCLUDED

#include "..\autonFunctions.c"

//Red right
void programmingSkills()
{
	//Driver loads
	auton_maintainLauncher_target = 76;
	startTask(maintainLauncherForAuton);
	setIntakeMotors(127);
	wait1Msec(60000);

	//Turn right and point at the red tile
	//turnGyro(80, 20);

	//Drive onto the red tile
	//driveQuad(127, 3000);

	//Turn left and point at the red high goal

	//Driver loads
}

#endif //PROGRAMMINGSKILLS_H_INCLUDED

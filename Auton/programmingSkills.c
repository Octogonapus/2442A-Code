#ifndef PROGRAMMINGSKILLS_H_INCLUDED
#define PROGRAMMINGSKILLS_H_INCLUDED

#include "..\autonFunctions.c"

//Red right
void programmingSkills()
{
	//Drive forward out from starting tile
	driveQuad(110, 300);

	//Turn left to be parallel with the field wall
	turnGyro(-100, 46);

	//Drive forward to be next to stack against field wall
	driveQuad(110, 600);

	//Turn right to point at the stack against the field wall
	turnGyro(-100, 96);

	//Intake the stack
	driveQuad(110, 150);
	driveAndIntakeTime(30, 30, 2300);

	//Drive back from wall
	driveQuad(-110, 200);

	//Turn to face net
	turnGyro(100, 170);

	//----------------------------------------

	////Driver loads
	//auton_maintainLauncher_target = 76;
	//startTask(maintainLauncherForAuton);
	//setIntakeMotors(127);
	//wait1Msec(60000);

	////Turn right and point at the red tile
	//turnGyro(100, 90);

	////Drive onto the red tile
	//driveQuad(127, 3000);

	//Turn left and point at the red high goal

	//Driver loads
}

#endif //PROGRAMMINGSKILLS_H_INCLUDED

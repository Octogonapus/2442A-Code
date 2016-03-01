#ifndef PROGRAMMINGSKILLS_H_INCLUDED
#define PROGRAMMINGSKILLS_H_INCLUDED

#include "..\autonFunctions.c"

//Blue left
void programmingSkills()
{
	launchFourBalls(85);

	//Drive forward out from starting tile
	driveQuad(110, 300);

	//Turn left to be parallel with the field wall
	turnGyro(-46);

	//Drive forward to be next to stack against field wall
	driveQuad(110, 650);

	//Turn right to point at the stack against the field wall
	turnGyro(-86);

	//Intake the stack
	driveQuad(110, 150);
	driveAndIntakeTime(30, 30, 2500);
	wait1Msec(500);
	driveAndIntakeTime(30, 30, 1000);

	//Drive back from wall
	driveQuad(-110, 200);

	//Turn to face net
	turnGyro(175);

	////Driver loads
	//auton_maintainLauncher_target = 76;
	//startTask(maintainLauncherForAuton);
	//setIntakeMotors(127);
	//wait1Msec(60000);

	////Turn right and point at the red tile
	//turnGyro(100, 90);

	////Drive onto the red tile
	//driveQuad(127, 3000);

	////Turn left and point at the red high goal

	////Driver loads
}

#endif //PROGRAMMINGSKILLS_H_INCLUDED

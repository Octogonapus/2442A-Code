#pragma config(Motor,  port1,           testMotor,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#include "Bulldog_Core_includes.h"

void pre_auton()
{
  bStopTasksBetweenModes = true;

  addMotor(testMotor);
}

task autonomous()
{
}

task usercontrol()
{
	startTask(motorSlewRateTask);

	while (true)
	{
		setMotorSpeed(testMotor, 100);

		wait1Msec(25);
	}
}

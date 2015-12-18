#pragma config(Motor,  port1,           testMotor,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Bulldog_Core_includes.h"

int i = 0;

task main()
{
	//Simulate pre-auton
	if (i == 0)
	{
		addMotor(testMotor, 0.5);
		i = 1;
	}

	startTask(motorSlewRateTask);

	while (true)
	{
		setMotorSpeed(testMotor, 100);

		wait1Msec(25);
	}
}

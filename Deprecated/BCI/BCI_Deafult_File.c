#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

//Defines here

#include "Bulldog_Competition_Includes.c"

void pre_auton() {}

void invoke(int func)
{
	switch (func)
	{
		default:
			break;
	}
}

task autonomous() {}

task usercontrol() {}
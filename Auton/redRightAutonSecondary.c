#ifndef REDRIGHTAUTONSECONDARY_H_INCLUDED
#define REDRIGHTAUTONSECONDARY_H_INCLUDED

#include "..\autonFunctions.c"

void redRightAutonSecondary()
{
	startTask(motorSlewRateTask);

	//Robot starts pointing at the center of the high goal
	//Shoot all 4 preloads
	//Turn right and point at the stack north of the stack on the vertex of the triangle
	//Drive forward and pick up that stack
	//Drive backward to where the robot was previously
	//Turn left and point at the ceneter of the high goal
	//Shoot all 4 preloads
}

#endif

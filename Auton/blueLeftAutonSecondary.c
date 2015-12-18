#ifndef BLUELEFTAUTONSECONDARY_H_INCLUDED
#define BLUELEFTAUTONSECONDARY_H_INCLUDED

#include "..\autonFunctions.c"

void blueLeftAutonSecondary()
{
	startTask(motorSlewRateTask);

	//Robot starts pointing at the center of the high goal
	//Shoot all 4 preloads
	//Turn left and point at the stack north of the stack on the vertex of the triangle
	//Drive forward and pick up that stack
	//Drive backward to where the robot was previously
	//Turn right and point at the ceneter of the high goal
	//Shoot all 4 preloads
}

#endif

#ifndef VELOCITYTBH_H_INCLUDED
#define VELOCITYTBH_H_INCLUDED

//This scale relates degrees per millisecond to rpm
#define TBH_DEGPMS_TO_RPM 166.7

//A velocity TBH controller
typedef struct vel_TBH
{
	//TBH constants
	float gain;

	//TBH calculations
	float currentVelocity;
	int prevPosition;
	int error;
	int prevError;
	bool firstCross;
	float outValApprox; //Output value at zero error for a given target velocity
	float outValAtZero;

	//Timestep
	float dt;
	int prevTime;

	//Input
	tSensors sensor;
	int currentPosition;
	float targetVelocity;

	//Output
	float outVal;
} vel_TBH;

//Initializes a velocity TBH controller
void vel_TBH_InitController(vel_TBH* tbh, tSensors sensor, float gain, float outValApprox);

//Sets the target velocity
void vel_TBH_SetTargetVelocity(vel_TBH* tbh, int targetVelocity, float outValApprox = -1010);

//Steps the controller calculations (velocity based)
int vel_TBH_StepController_VEL(vel_TBH* tbh);

#endif

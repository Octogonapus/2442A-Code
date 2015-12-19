#ifndef VELOCITYTBH_H_INCLUDED
#define VELOCITYTBH_H_INCLUDED

//This scale constant relates mesured ticks per second to motor power
#define PID_SCALE 2.67

//This scale relates degrees per millisecond to rpm
#define DEGPMS_TO_RPM 166.7

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
} vel_PID;

#endif

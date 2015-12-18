#ifndef PIDCONTROLLER_C_INCLUDED
#define PIDCONTROLLER_C_INCLUDED

//Do nothing with no PID Controllers
#ifdef PID_NUM
#if PID_NUM > 0

#ifndef PIDCONTROL_H_INCLUDED
#include "pidControl.h"
#endif

#ifndef MATH_H_INCLUDED
#include "math.h"
#endif

//Array for pidControllers
static pidController pidControllers[PID_NUM];
static int nextPIDController = 0;

/*
* Adds and initializes a PID Controller
*/
pidController* newPIDController(tSensors sensor, float kP, float kI, float kD, float kBias, int errorThreshold, int integralLimit, bool isEnabled)
{
	//Bounds check
	if (nextPIDController == PID_NUM)
	{
		return NULL;
	}

	//Grab the next pidController slot
	pidController *p = &(pidControllers[nextPIDController]);
	nextPIDController++;

	//PID constants
	p->kP = kP;
	p->kI = kI;
	p->kD = kD;
	p->kBias = kBias;

	//PID calculation
	p->error = 0;
	p->prevError = 0;
	p->integral = 0;
	p->derivative = 0;

	//PID limits
	p->errorThreshold = errorThreshold;
	p->integralLimit = integralLimit;

	//Input
	p->sensor = sensor;
	p->targetPos = SensorValue[sensor];

	//Output
	p->outVal = 0;

	//Extra control
	p->isEnabled = isEnabled;

	return p;
}

/*
* Steps all enabled PID Controller's calculations
*/
task UpdatePIDControllersTask()
{
	pidController *p = NULL;
	int currentPIDController = 0;

	while (true)
	{
		p = &(pidControllers[currentPIDController]);

		if (p != NULL && p->isEnabled)
		{
			//Calculate error
			//Error is positive when approaching target
			p->error = p->targetPos - SensorValue[p->sensor];

			//Limit error
			if (abs(p->error) < p->errorThreshold)
			{
				p->error = 0;
			}

			//Calculate integral and limit to avoid windup
			p->integral += p->error;
			if (abs(p->integral) > p->integralLimit)
			{
				p->integral = sign(p->integral) * p->integralLimit;
			}

			//Calculate derivative
			p->derivative = p->error - p->prevError;
			p->prevError = p->error;

			//Calculate and send motor power
			p->outVal = (p->error * p->kP) + (p->integral * p->kI) + (p->derivative * p->kD) + p->kBias;
		}

		currentPIDController = (currentPIDController + 1) == PID_NUM ? 0 : currentPIDController + 1;
		wait1Msec(25);
	}
}

#endif //#if PID_NUM > 0
#endif //#ifdef PID_NUM

#endif //#ifndef PIDCONTROLLER_C_INCLUDED

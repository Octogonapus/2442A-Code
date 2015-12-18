#ifndef PIDCONTROL_H_INCLUDED
#define PIDCONTROL_H_INCLUDED

#include "StatusCodes.c"
#include "Math.c"
#include "MotorControl.c"

/***************************************************************************/
/*                                                                         */
/* Struct to represent a PID Controller                                    */
/*                                                                         */
/***************************************************************************/
typedef struct pidController
{
	//PID constants
	float kP;
	float kI;
	float kD;
	float kBias;

	//PID calculation
	int error;
	int prevError;
	int integral;
	int derivative;

	//PID limits
	int errorThreshold;
	int integralLimit;

	//Input
	tSensors sensor;
	driveMotor* motor;
	int targetPos;

	//Extra control
	bool isEnabled;
} pidController;

/***************************************************************************/
/*                                                                         */
/* PID control definitions                                                 */
/*                                                                         */
/***************************************************************************/
#define PID_CONTROLLER_MAX 4
#define _SetTargetPosition(controller, pos) controller->targetPos = pos
#define _ClearPIDControllers() nextPIDController = 0

//Array for allocation
static pidController pidControllers[PID_CONTROLLER_MAX];
static short nextPIDController = 0;

/***************************************************************************/
/*                                                                         */
/* Subroutine - Initializes a PID Controller                               */
/*                                                                         */
/***************************************************************************/
pidController* newPIDController(tSensors sensor, driveMotor* motor, float kP, float kI, float kD, float kBias = 0.0, int errorThreshold = 15, int integralLimit = 15, bool isEnabled = true)
{
	//Bounds check
	if (nextPIDController + 1 == PID_CONTROLLER_MAX)
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
	p->motor = motor;
	p->targetPos = SensorValue[sensor];

	//Extra control
	p->isEnabled = isEnabled;

	#ifdef DEBUG_FINE_PID
		writeDebugStreamLine("newPIDController");
	#endif

	return p;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Steps a PID Controller's calculations                      */
/*                                                                         */
/***************************************************************************/
int updatePIDController(pidController *p)
{
	#ifdef DEBUG_FINE_PID
		writeDebugStreamLine("updatePIDControllerStart");
	#endif

	if (p == NULL)
	{
		return EXIT_NULL;
	}

	if (p->isEnabled)
	{
		//Calculate error
		//Error is positive when approaching target
		p->error = p->targetPos - SensorValue[p->sensor];

		//Limit error
		if (_Abs(p->error) < p->errorThreshold)
		{
			p->error = 0;
		}

		//Calculate integral and limit to avoid windup
		p->integral += p->error;
		if (_Abs(p->integral) > p->integralLimit)
		{
			p->integral = _Sign(p->integral) * p->integralLimit;
		}

		//Calculate derivative
		p->derivative = p->error - p->prevError;
		p->prevError = p->error;

		//Calculate and send motor power
		(p->motor)->reqSpeed = (p->error * p->kP) + (p->integral * p->kI) + (p->derivative * p->kD) + p->kBias;

		#ifdef DEBUG_FINE_PID
			writeDebugStreamLine("updatePIDControllerEnd");
		#endif
	}
	else
	{
		return EXIT_INTERRUPTED;
	}

	return EXIT_SUCCESS;
}

#endif

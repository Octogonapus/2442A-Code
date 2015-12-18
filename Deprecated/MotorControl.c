#ifndef MOTORCONTROL_H_INCLUDED
#define MOTORCONTROL_H_INCLUDED

#include "Math.c"

/***************************************************************************/
/*                                                                         */
/* Motor definitions                                                       */
/*                                                                         */
/***************************************************************************/
#define MOTOR_NUM               kNumbOfTotalMotors
#define MOTOR_MIN_VALUE		    (-127)
#define MOTOR_MAX_VALUE			127
#define MOTOR_DEFAULT_SLEW_RATE 10
#define MOTOR_FAST_SLEW_RATE	256
#define MOTOR_TASK_DELAY		15
#define MOTOR_DEADBAND		    10

/***************************************************************************/
/*                                                                         */
/* Motor control definitions                                               */
/*                                                                         */
/***************************************************************************/
#define _SetMotorSpeed(index, speed) driveMotors[index].reqSpeed = (speed)
#define _SetMotorSlew(index, slew) driveMotors[index].slew = (slew)
#define _GetMotor(index) driveMotors[index]
#define _GetMotorSpeed(index) driveMotors[index].reqSpeed

/***************************************************************************/
/*                                                                         */
/* Raw motor control definitions                                           */
/*                                                                         */
/***************************************************************************/
#define _SetMotorSpeedRaw(index, speed) motor[index] = (speed)
#define _GetMotorSpeedRaw(index) motor[index]

/***************************************************************************/
/*                                                                         */
/* Struct to represent a motor                                             */
/*                                                                         */
/***************************************************************************/
typedef struct driveMotor
{
	int reqSpeed;
	int slew;
} driveMotor;

//Array for allocation
static driveMotor driveMotors[MOTOR_NUM];

/***************************************************************************/
/*                                                                         */
/* Subroutine - Adds a motor (by name) to the motor array                  */
/*                                                                         */
/***************************************************************************/
driveMotor* addMotor(tMotor name)
{
	//Allocate from array
	driveMotor *m = &(driveMotors[name]);

	m->reqSpeed = 0;
	m->slew = MOTOR_DEFAULT_SLEW_RATE;

	#ifdef DEBUG_FINE_MOTOR
		writeDebugStreamLine("addMotor");
	#endif

	return m;
}

/***************************************************************************/
/*                                                                         */
/* Task - Updates the power of each motor to best meet the requested power */
/*                                                                         */
/***************************************************************************/
task MotorSlewRateTask()
{
	//Index of current motor
	unsigned int motorIndex;
	//Updated speed of current motor
	int motorTmpSpd;
	//Requested speed of current motor
	int motorTmpReq;
	//Current motor
	driveMotor *currentMotor;

	while (true)
	{
		for (motorIndex = 0; motorIndex < MOTOR_NUM; motorIndex++)
		{
			//Keep internal memory access to a minimum
			currentMotor = &(driveMotors[motorIndex]);
			motorTmpSpd = motor[motorIndex];
			motorTmpReq = currentMotor->reqSpeed;

			//If the motor value needs to change
			if (motorTmpSpd != motorTmpReq)
			{
				//Increase motor value
				if (motorTmpReq > motorTmpSpd)
				{
					motorTmpSpd += currentMotor->slew;

					//Limit speed
					if (motorTmpSpd > motorTmpReq)
					{
						motorTmpSpd = motorTmpReq;
					}
				}

				//Decrease motor value
				if (motorTmpReq < motorTmpSpd)
				{
					motorTmpSpd -= currentMotor->slew;

					//Limit speed
					if (motorTmpSpd < motorTmpReq)
					{
						motorTmpSpd = motorTmpReq;
					}
				}

				//Bound speed
				writeDebugStreamLine("FIRST: %d", motorTmpSpd);
				motorTmpSpd = motorTmpSpd > MOTOR_MAX_VALUE ? MOTOR_MAX_VALUE : motorTmpSpd;
				writeDebugStreamLine("SECOND: %d", motorTmpSpd);
				motorTmpSpd = motorTmpSpd < MOTOR_MIN_VALUE ? MOTOR_MIN_VALUE : motorTmpSpd;
				writeDebugStreamLine("THIRD: %d", motorTmpSpd);

				//Send updated speed to motor
				motor[motorIndex] = motorTmpSpd;
			}
		}
		wait1Msec(MOTOR_TASK_DELAY);
	}
}

#endif

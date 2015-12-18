#ifndef PIDCONTROL_H_INCLUDED
#define PIDCONTROL_H_INCLUDED

#ifndef STATUSCODES_H_INCLUDED
#define STATUSCODES_H_INCLUDED

#define EXIT_SUCCESS        0
#define EXIT_FAILURE        1
#define EXIT_INTERRUPTED    2
#define EXIT_NULL           3
#define COMPARE_MISMATCH    4
#define COMPARE_FAIL        5

#endif

#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#define PI 3.141
#define _Abs(value) ( (value) >= 0 ? (value) : -(value) )
#define _Round(value) ( (value) % 1 > 0.5 ? ((int) (value) + 0.5) : ((int) (value)) )
#define _Sign(value) ( (value) >= 0 ? 1 : (-1) )
#define _Cube(value) ( (value) * (value) * (value) )

#define _InchesToTicks(inches, diam) ( ((inches) / (PI * (diam))) * 360 )
#define _TicksToInches(ticks, diam) ( ((diam) * PI) * ((ticks) / 360) )

#endif

#ifndef MOTORCONTROL_H_INCLUDED
#define MOTORCONTROL_H_INCLUDED

#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#define PI 3.141
#define _Abs(value) ( (value) >= 0 ? (value) : -(value) )
#define _Round(value) ( (value) % 1 > 0.5 ? ((int) (value) + 0.5) : ((int) (value)) )
#define _Sign(value) ( (value) >= 0 ? 1 : (-1) )
#define _Cube(value) ( (value) * (value) * (value) )

#define _InchesToTicks(inches, diam) ( ((inches) / (PI * (diam))) * 360 )
#define _TicksToInches(ticks, diam) ( ((diam) * PI) * ((ticks) / 360) )

#endif

/***************************************************************************/
/*                                                                         */
/* Motor definitions                                                       */
/*                                                                         */
/***************************************************************************/
#define MOTOR_NUM               kNumbOfTotalMotors
#define MOTOR_MIN_VALUE		    127
#define MOTOR_MAX_VALUE			(-127)
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
				motorTmpSpd = motorTmpSpd > MOTOR_MAX_VALUE ? MOTOR_MAX_VALUE : motorTmpSpd;
				motorTmpSpd = motorTmpSpd < MOTOR_MIN_VALUE ? MOTOR_MIN_VALUE : motorTmpSpd;

				//Send updated speed to motor
				motor[motorIndex] = motorTmpSpd;
			}
		}
		wait1Msec(MOTOR_TASK_DELAY);
	}
}

#endif


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

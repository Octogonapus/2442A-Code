/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) Ryan Benasutti                         */
/*                                   2014                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    Module:     Bulldog_Competition_Includes.c                               */
/*    Author:     Ryan Benasutti                                               */
/*    Created:    1 June 2014                                                  */
/*                                                                             */
/*    Revisions:                                                               */
/*                V1.00  14 Oct 2014 - Initial release                         */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    The author is supplying this software for use with the VEX cortex        */
/*    control system. This file can be freely distributed and teams are        */
/*    authorized to freely use this program , however, it is requested that    */
/*    improvements or additions be shared with the Vex community via the vex   */
/*    forum.  Please acknowledge the work of the authors when appropriate.     */
/*    Thanks.                                                                  */
/*                                                                             */
/*    Licensed under the Apache License, Version 2.0 (the "License");          */
/*    you may not use this file except in compliance with the License.         */
/*    You may obtain a copy of the License at                                  */
/*                                                                             */
/*      http://www.apache.org/licenses/LICENSE-2.0                             */
/*                                                                             */
/*    Unless required by applicable law or agreed to in writing, software      */
/*    distributed under the License is distributed on an "AS IS" BASIS,        */
/*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*    See the License for the specific language governing permissions and      */
/*    limitations under the License.                                           */
/*                                                                             */
/*    The author can be contacted on the vex forums as Octogonapus             */
/*    Member of team 2442 Robodogs, Worcester MA.                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

#ifndef BULLDOG_COMPETITON_INCLUDES
#define BULLDOG_COMPETITON_INCLUDES

//Check if RobotC is new enough
#ifndef kRobotCVersionNumeric
#include "FirmwareVersion.h"
#endif
#if kRobotCVersionNumeric < 360
#error "RobotC Version 3.60 or newer is required"
#endif

/***************************************************************************/
/*                                                                         */
/* Status code definitions                                                 */
/*                                                                         */
/***************************************************************************/
#define EXIT_SUCCESS        0
#define EXIT_FAILURE        1
#define EXIT_INTERRUPTED    2
#define EXIT_NULL           3
#define COMPARE_MISMATCH    4
#define COMPARE_FAIL        5

/***************************************************************************/
/*                                                                         */
/* Math definitions                                                        */
/*                                                                         */
/***************************************************************************/
#define CUBED_127 16129
#define ROOT_2    1.414
#define _Sign(value) ( (value) >= 0 ? 1 : (-1) )
#define _Cube(value) ( (value) * (value) * (value) )
#define _InchesToTicks(inches, diam) ( ((inches) / (PI * (diam))) * 360 )
#define _TicksToInches(ticks, diam) ( ((diam) * PI) * ((ticks) / 360) )

/***************************************************************************/
/*                                                                         */
/* Joystick definitions                                                    */
/*                                                                         */
/***************************************************************************/
#define JOY_DRIVE_LV  vexJSLeftV
#define JOY_DRIVE_LH  vexJSLeftH
#define JOY_DRIVE_RV  vexJSRightV
#define JOY_DRIVE_RH  vexJSRightH
#define JOY_THRESHOLD 15

/***************************************************************************/
/*                                                                         */
/* PID control definitions                                                 */
/*                                                                         */
/***************************************************************************/
#define _SetTargetPosition(controller, pos) controller->targetPos = pos
#define _GetPIDSpeed(controller) controller->outVal
#define _ClearPIDControllers() nextPIDController = 0

/***************************************************************************/
/*                                                                         */
/* Motor definitions                                                       */
/*                                                                         */
/***************************************************************************/
#define MOTOR_NUM               kNumbOfTotalMotors
#define MOTOR_MIN_VALUE		      (-127)
#define MOTOR_MAX_VALUE			    127
#define MOTOR_DEFAULT_SLEW_RATE 10
#define MOTOR_FAST_SLEW_RATE    256
#define MOTOR_TASK_DELAY        15
#define MOTOR_DEADBAND          10

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
/* LCD button definitions                                                  */
/*                                                                         */
/***************************************************************************/
#define BUTTON_LEFT   1
#define BUTTON_CENTER 2
#define BUTTON_RIGHT  4

/***************************************************************************/
/*                                                                         */
/* LCD button response definitions                                         */
/*                                                                         */
/***************************************************************************/
#define _WaitForPress() while(nLCDButtons == 0) {} wait1Msec(5)
#define _WaitForRelease() while(nLCDButtons != 0) {} wait1Msec(5)

/***************************************************************************/
/*                                                                         */
/* Default text definitions                                                */
/*                                                                         */
/***************************************************************************/
#define DEFAULT_LINE      "<<            >>"
#define SUBMENU_SELECT    "<<   SELECT   >>"
#define EXIT_MENU_SELECT  "<<     OK     >>"
#define SUBMENU_BACK      "<<    BACK    >>"

/***************************************************************************/
/*                                                                         */
/* Memory constraint definitions                                           */
/*                                                                         */
/***************************************************************************/
#define MAX_MENU_NUM 10
#define MAX_PID_NUM  7

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
	int targetPos;

	//Output
	int outVal;

	//Extra control
	bool isEnabled;
} pidController;

//Array for allocation
static pidController pidControllers[MAX_PID_NUM];
static int nextPIDController = 0;

/***************************************************************************/
/*                                                                         */
/* PID Controllers for the drivetrain                                      */
/*                                                                         */
/***************************************************************************/
#if defined(DRIVE_TANK_2) || defined(DRIVE_TANK_2_CUBIC) || defined(DRIVE_TANK_4) || defined(DRIVE_TANK_4_CUBIC) || defined(DRIVE_TANK_6) || defined(DRIVE_TANK_6_CUBIC) || defined(DRIVE_X) || defined(DRIVE_X_HEADING) || defined(DRIVE_X_CUBIC) || defined(DRIVE_MECANUM) || defined(DRIVE_MECANUM_CUBIC)

pidController *leftTranslationController;
pidController *leftRotationController;
pidController *rightTranslationController;
pidController *rightRotationController;

#endif

#if defined(DRIVE_P) || defined(DRIVE_P_CUBIC)

pidController *frontTranslationController;
pidController *frontRotationController;
pidController *leftTranslationController;
pidController *leftRotationController;

#endif

#if defined(DRIVE_H) || defined(DRIVE_H_CUBIC)

pidController *leftTranslationController;
pidController *leftRotationController;
pidController *middleTranslationController;
pidController *rightTranslationController;
pidController *rightRotationController;

#endif

/***************************************************************************/
/*                                                                         */
/* PID Controllers for the lift                                            */
/*                                                                         */
/***************************************************************************/
#if defined(LIFT_2_1) || defined(LIFT_4_1) || defined(LIFT_6_1)

pidController *liftSystemController;

#endif

#if defined(LIFT_2_2) || defined(LIFT_4_2) || defined(LIFT_6_2)

pidController *liftSystemLeftController;
pidController *liftSystemRightController;

#endif

/***************************************************************************/
/*                                                                         */
/* Struct to represent a drivetrain                                        */
/*                                                                         */
/***************************************************************************/
#if defined(DRIVE_TANK_2) || defined(DRIVE_TANK_2_CUBIC)

typedef struct
{
	tMotor left;
	tMotor right;

	tSensors leftQuad;
	tSensors rightQuad;
} twoMotorDrivetrain;

static twoMotorDrivetrain driveTrain;

#endif

#if defined(DRIVE_TANK_4) || defined(DRIVE_TANK_4_CUBIC) || defined(DRIVE_X) || defined(DRIVE_X_HEADING) || defined(DRIVE_X_CUBIC) || defined(DRIVE_MECANUM) || defined(DRIVE_MECANUM_CUBIC)

typedef struct
{
	tMotor frontLeft;
	tMotor backLeft;
	tMotor frontRight;
	tMotor backRight;

	tSensors leftQuad;
	tSensors rightQuad;
} fourMotorDrivetrain;

static fourMotorDrivetrain driveTrain;

#endif

#if defined(DRIVE_P) || defined(DRIVE_P_CUBIC)

typedef struct
{
	tMotor front;
	tMotor left;
	tMotor right;
	tMotor back;

	tSensors frontQuad;
	tSensors leftQuad;
} fourMotorDrivetrain;

static fourMotorDrivetrain driveTrain;

#endif

#if defined(DRIVE_H) || defined(DRIVE_H_CUBIC)

typedef struct
{
	tMotor frontLeft;
	tMotor backLeft;
	tMotor middle;
	tMotor frontRight;
	tMotor backRight;

	tSensors leftQuad;
	tSensors middleQuad;
	tSensors rightQuad;
} fiveMotorDrivetrain;

static fiveMotorDrivetrain driveTrain;

#endif

#if defined(DRIVE_TANK_6) || defined(DRIVE_TANK_6_CUBIC)

typedef struct
{
	tMotor frontLeft;
	tMotor middleLeft;
	tMotor backLeft;
	tMotor frontRight;
	tMotor middleRight;
	tMotor backRight;

	tSensors leftQuad;
	tSensors rightQuad;
} sixMotorDrivetrain;

static sixMotorDrivetrain driveTrain;

#endif

/***************************************************************************/
/*                                                                         */
/* Struct to represent a lift                                              */
/*                                                                         */
/***************************************************************************/

#if defined(LIFT_2_1)

typedef struct
{
	tMotor left;
	tMotor right;

	tSensors liftQuad;
} lift21;

static lift21 liftSystem;

#endif

#if defined(LIFT_4_1)

typedef struct
{
	tMotor leftTop;
	tMotor leftBottom;
	tMotor rightTop;
	tMotor rightBottom;

	tSensors liftQuad;
} lift41;

static lift41 liftSystem;

#endif

#if defined(LIFT_6_1)

typedef struct
{
	tMotor leftTop;
	tMotor middleLeft;
	tMotor leftBottom;
	tMotor rightTop;
	tMotor middleRight;
	tMotor rightBottom;

	tSensors liftQuad;
} lift61;

static lift61 liftSystem;

#endif

#if defined(LIFT_2_2)

typedef struct
{
	tMotor left;
	tMotor right;

	tSensors leftQuad;
	tSensors rightQuad;
} lift22;

static lift22 liftSystem;

#endif

#if defined(LIFT_4_2)

typedef struct
{
	tMotor leftTop;
	tMotor leftBottom;
	tMotor rightTop;
	tMotor rightBottom;

	tSensors leftQuad;
	tSensors rightQuad;
} lift42;

static lift42 liftSystem;

#endif

#if defined(LIFT_6_2)

typedef struct
{
	tMotor leftTop;
	tMotor middleLeft;
	tMotor leftBottom;
	tMotor rightTop;
	tMotor middleRight;
	tMotor rightBottom;

	tSensors leftQuad;
	tSensors rightQuad;
} lift62;

static lift62 liftSystem;

#endif

/***************************************************************************/
/*                                                                         */
/* Struct to represent a menu (double linked list)                         */
/*                                                                         */
/***************************************************************************/
typedef struct menu
{
	//Pointer to next menu (right button)
	menu *next;
	//Pointer to previous menu (left button)
	menu *prev;
	//Pointer to higher menu (center button)
	menu *up;
	//Pointer to deeper menu (center button)
	menu *down;

	//Displayed text
	string *msg;

	//Function value in the "dispatch table"
	int dispatchFuncVal;
} menu;

//Menu for current selection
menu *currentMenu = NULL;

//Array for allocation
static menu menus[MAX_MENU_NUM];
static int nextMenu = 0;

/***************************************************************************/
/*                                                                         */
/* Prototypes                                                              */
/*                                                                         */
/***************************************************************************/
//File implemented
void allMotorsOff();
void allTasksStop();
void printnVexRCRecieveState();
void startMotorSlewRateTask();
void stopMotorSlewRateTask();
void startLCDControl();
void stopLCDControl();
void startDrivetrainControl();
void stopDrivetrainControl();
void startLiftControl();
void stopLiftControl();
void startLiftPositionUpdater();
void stopLiftPositionUpdater();
task MotorSlewRateTask();
task UpdateLCDTask();
task drivetrainControl();
task liftControl();
task updateLiftPosition();

//User implemented
void pre_auton();
void invoke(int func);
task autonomous();
task usercontrol();

/***************************************************************************/
/*                                                                         */
/* Variables                                                               */
/*                                                                         */
/***************************************************************************/
bool bStopTasksBetweenModes = true;

/***************************************************************************/
/*                                                                         */
/* Task - Main task                                                        */
/*                                                                         */
/***************************************************************************/
task main()
{
	// Master CPU will not let competition start until powered on for at least 2-seconds
	printnVexRCRecieveState();
	wait1Msec(2000);

	pre_auton();

	while (true)
	{
		while (bIfiRobotDisabled)
		{
			printnVexRCRecieveState();
			while (true)
			{
				if (!bIfiRobotDisabled)
					break;
				wait1Msec(25);

				if (!bIfiRobotDisabled)
					break;
				wait1Msec(25);

				if (!bIfiRobotDisabled)
					break;
				wait1Msec(25);

				if (!bIfiRobotDisabled)
					break;
				wait1Msec(25);
			}
		}

		if (bIfiAutonomousMode)
		{
			printnVexRCRecieveState();
			startTask(autonomous);

			// Waiting for autonomous phase to end
			while (bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (!bVEXNETActive)
				{
					if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
						allMotorsOff();
				}
				wait1Msec(25);               // Waiting for autonomous phase to end
			}
			allMotorsOff();
			if(bStopTasksBetweenModes)
			{
				allTasksStop();
			}
		}

		else
		{
			printnVexRCRecieveState();
			startTask(usercontrol);

			// Here we repeat loop waiting for user control to end and (optionally) start
			// of a new competition run
			while (!bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
					allMotorsOff();
				wait1Msec(25);
			}
			allMotorsOff();
			if(bStopTasksBetweenModes)
			{
				allTasksStop();
			}
		}
	}
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Stops all motors                                           */
/*                                                                         */
/***************************************************************************/
void allMotorsOff()
{
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
	motor[port9] = 0;
	motor[port10] = 0;
	stopMotorSlewRateTask();
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Stops all tasks                                            */
/*                                                                         */
/***************************************************************************/
void allTasksStop()
{
	stopTask(1);
	stopTask(2);
	stopTask(3);
	stopTask(4);
	stopTask(5);
	stopTask(6);
	stopTask(7);
	stopTask(8);
	stopTask(9);
	stopTask(10);
	stopTask(11);
	stopTask(12);
	stopTask(13);
	stopTask(14);
	stopTask(15);
	stopTask(16);
	stopTask(17);
	stopTask(18);
	stopTask(19);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PID CONTROL                                                                                                                              PID CONTROL //
// PID CONTROL                                                                                                                              PID CONTROL //
// PID CONTROL                                                                                                                              PID CONTROL //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
/*                                                                         */
/* Subroutine - Initializes a PID Controller                               */
/*                                                                         */
/***************************************************************************/
pidController* newPIDController(tSensors sensor, float kP, float kI, float kD, float kBias = 0.0, int errorThreshold = 15, int integralLimit = 15, bool isEnabled = true)
{
	//Bounds check
	if (nextPIDController + 1 == MAX_PID_NUM)
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

/***************************************************************************/
/*                                                                         */
/* Subroutine - Steps a PID Controller's calculations                      */
/*                                                                         */
/***************************************************************************/
int updatePIDController(pidController *p)
{
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
		if (abs(p->error) < p->errorThreshold)
		{
			p->error = 0;
		}

		//Calculate integral and limit to avoid windup
		p->integral += p->error;
		if (abs(p->integral) > p->integralLimit)
		{
			p->integral = _Sign(p->integral) * p->integralLimit;
		}

		//Calculate derivative
		p->derivative = p->error - p->prevError;
		p->prevError = p->error;

		//Calculate and send motor power
		p->outVal = (p->error * p->kP) + (p->integral * p->kI) + (p->derivative * p->kD) + p->kBias;
	}
	else
	{
		return EXIT_INTERRUPTED;
	}

	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MOTOR CONTROL                                                                                                                          MOTOR CONTROL //
// MOTOR CONTROL                                                                                                                          MOTOR CONTROL //
// MOTOR CONTROL                                                                                                                          MOTOR CONTROL //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
/*                                                                         */
/* Subroutine - Adds a motor (by name) to the motor array                  */
/*                                                                         */
/***************************************************************************/
driveMotor* addMotor(const tMotor name)
{
	//Allocate from array
	driveMotor *m = &(driveMotors[name]);

	m->reqSpeed = 0;
	m->slew = MOTOR_DEFAULT_SLEW_RATE;

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
					motorTmpSpd = motorTmpSpd > motorTmpReq ? motorTmpReq : motorTmpSpd;
				}

				//Decrease motor value
				if (motorTmpReq < motorTmpSpd)
				{
					motorTmpSpd -= currentMotor->slew;

					//Limit speed
					motorTmpSpd = motorTmpSpd < motorTmpReq ? motorTmpReq : motorTmpSpd;
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

/***************************************************************************/
/*                                                                         */
/* Subroutine - Starts motor control                                       */
/*                                                                         */
/***************************************************************************/
void startMotorSlewRateTask()
{
	startTask(MotorSlewRateTask);
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Stops motor control                                        */
/*                                                                         */
/***************************************************************************/
void stopMotorSlewRateTask()
{
	stopTask(MotorSlewRateTask);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LCD CONTROL                                                                                                                              LCD CONTROL //
// LCD CONTROL                                                                                                                              LCD CONTROL //
// LCD CONTROL                                                                                                                              LCD CONTROL //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
/*                                                                         */
/* Subroutine - adds a menu, allocates from array                          */
/*                                                                         */
/***************************************************************************/
menu* newMenu(const string *msg, const int dispatchFuncVal = -1, const menu *next = NULL, const menu *prev = NULL, const menu *up = NULL, const menu *down = NULL)
{
	//Bounds check
	if (nextMenu + 1 == MAX_MENU_NUM)
	{
		return NULL;
	}

	//Grab the next menu slot
	//Should be a null menu
	menu *m = &(menus[nextMenu]);
	nextMenu++;

	m->next = next;
	m->prev = prev;
	m->up = up;
	m->down = down;
	m->msg = msg;
	m->dispatchFuncVal = dispatchFuncVal;

	return m;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - changes the function a menu has                            */
/*                                                                         */
/***************************************************************************/
void changeFunction(menu *m, const int func)
{
	m->dispatchFuncVal = func;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - childs menus to parents                                    */
/*                                                                         */
/***************************************************************************/
void makeLevel(menu *child, menu *parent)
{
	child->up = parent;
	parent->down = child;
}

void makeLevel(menu *child, menu *child2, menu *parent)
{
	child->up = parent;
	child2->up = parent;
	parent->down = child2;
}

void makeLevel(menu *child, menu *child2, menu *child3, menu *parent)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	parent->down = child3;
}

void makeLevel(menu *child, menu *child2, menu *child3, menu *child4, menu *parent)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	child4->up = parent;
	parent->down = child4;
}

void makeLevel(menu *child, menu *child2, menu *child3, menu *child4, menu *child5, menu *parent)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	child4->up = parent;
	child5->up = parent;
	parent->down = child5;
}

void makeLevel(menu *child, menu *child2, menu *child3, menu *child4, menu *child5, menu *child6, menu *parent)
{
	child->up = parent;
	child2->up = parent;
	child3->up = parent;
	child4->up = parent;
	child5->up = parent;
	child6->up = parent;
	parent->down = child6;
}

void makeLevel(menu *startingMenu, menu *parent, const int count = 1)
{
	//Step through memory to get child menus
	for (int i = 0; i < count; i++)
	{
		(startingMenu + i)->up = parent;
		parent->down = (startingMenu + i);
	}
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - inserts a menu into a row                                  */
/*                                                                         */
/***************************************************************************/
void putMenuInRow(menu *m, menu *next, menu *prev = NULL)
{
	m->next = next;

	if (prev != NULL)
	{
		m->prev = prev;
	}
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - pairs two menus (instead of using addMenuRow)              */
/*                                                                         */
/***************************************************************************/
void pairMenus(menu *m1, menu *m2)
{
	m1->next = m2;
	m1->prev = m2;
	m2->next = m1;
	m2->prev = m1;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - pairs three menus (instead of using addMenuRow)            */
/*                                                                         */
/***************************************************************************/
void pairMenus(menu *m1, menu *m2, menu *m3)
{
	m1->next = m2;
	m1->prev = m3;
	m2->next = m3;
	m2->prev = m1;
	m3->next = m1;
	m3->prev = m2;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - pairs four menus (instead of using addMenuRow)            */
/*                                                                         */
/***************************************************************************/
void pairMenus(menu *m1, menu *m2, menu *m3, menu *m4)
{
	m1->next = m2;
	m1->prev = m4;
	m2->next = m3;
	m2->prev = m1;
	m3->next = m4;
	m3->prev = m2;
	m4->next = m1;
	m4->prev = m3;
}

/***************************************************************************/
/*                                                                         */
/* Task - updates the LCD and responds to button presses                   */
/*                                                                         */
/***************************************************************************/
task UpdateLCDTask()
{
	clearLCDLine(0);
	clearLCDLine(1);
	currentMenu = &(menus[0]);
	displayLCDString(0, 0, *menus[0].msg);
	displayLCDString(1, 0, SUBMENU_SELECT);

	while (true)
	{
		//Alert user of crash
		if (bResetFromWatchdogTimeout)
		{
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0, 0, " WATCHDOG RESET ");
		}

		//Only one menu has been added
		//Only check for a function
		if (nextMenu == 1)
		{
			if (nLCDButtons & kButtonCenter)
			{
				if (currentMenu->dispatchFuncVal != -1)
				{
					//A function exists, execute it
					invoke(currentMenu->dispatchFuncVal);
				}
			}
		}
		else
		{
			//Left button
			if (nLCDButtons & kButtonLeft)
			{
				if (currentMenu->prev != NULL)
				{
					currentMenu = currentMenu->prev;
					_WaitForRelease();
				}
			}
			//Right button
			else if (nLCDButtons & kButtonRight)
			{
				if (currentMenu->next != NULL)
				{
					currentMenu = currentMenu->next;
					_WaitForRelease();
				}
			}
			//Center button
			else if (nLCDButtons & kButtonCenter)
			{
				//Let the user hold the center button
				wait1Msec(250);

				//Center held
				if (nLCDButtons & kButtonCenter)
				{
					//If a higher menu exists
					if (currentMenu->up != NULL)
					{
						currentMenu = currentMenu->up;
						_WaitForRelease();
					}
				}
				//Center not held
				else
				{
					//If a lower menu exists
					if (currentMenu->down != NULL)
					{
						currentMenu = currentMenu->down;
						_WaitForRelease();
					}
					//No lower menu exists, check if there is a function
					else if (currentMenu->dispatchFuncVal != -1)
					{
						//A function exists, execute it
						invoke(currentMenu->dispatchFuncVal);
					}
				}
			}
		}
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0, 0, *currentMenu->msg);
		displayLCDString(1, 0, SUBMENU_SELECT);
		wait1Msec(100);
	}
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Starts LCD control                                         */
/*                                                                         */
/***************************************************************************/
void startLCDControl()
{
	startTask(UpdateLCDTask);
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Stops LCD control                                          */
/*                                                                         */
/***************************************************************************/
void stopLCDControl()
{
	stopTask(UpdateLCDTask);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UTIL                                                                                                                                            UTIL //
// UTIL                                                                                                                                            UTIL //
// UTIL                                                                                                                                            UTIL //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
/*                                                                         */
/* Subroutine - Prints which transmitters are connected, if the            */
/*              competition switch is connected, and which mode the        */
/*              competition is in                                          */
/*                                                                         */
/***************************************************************************/
void printnVexRCRecieveState()
{
	//Print transmitters
	if (nVexRCReceiveState & vrXmit1)
	{
		writeDebugStreamLine("Transmitter 1 is connected");
	}
	else if (nVexRCReceiveState & vrXmit2)
	{
		writeDebugStreamLine("Transmitter 2 is connected");
	}
	else if ((nVexRCReceiveState & (vrXmit1 | vrXmit2)) == (vrXmit1 | vrXmit2))
	{
		writeDebugStreamLine("Transmitter 1 and 2 are connected");
	}

	//Print competition switch
	if (nVexRCReceiveState & vrCompetitionSwitch)
	{
		writeDebugStreamLine("Competition switch is connected");
	}
	else
	{
		writeDebugStreamLine("Competition switch is not connected");
	}

	//Print competition mode
	if (nVexRCReceiveState & vrDisabled)
	{
		writeDebugStreamLine("Robot is disabled");
	}
	else if (nVexRCReceiveState & vrAutonomousMode)
	{
		writeDebugStreamLine("Robot is in autonomous mode");
	}
	else
	{
		writeDebugStreamLine("Robot is in tele-op mode");
	}

	writeDebugStream("\n");
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - dumps all current motor and sensor values to the debug     */
/*              stream every 25ms                                          */
/*                                                                         */
/***************************************************************************/
int dumpLevels()
{
	unsigned int i;

	//Print motors
	for (i = 0; i < kNumbOfTotalMotors; i++)
	{
		writeDebugStreamLine("motor port %d: %d", i + 1, motor[i]);
	}

	//Print analog sensors
	for (i = 0; i < kNumbAnalogSensors; i++)
	{
		writeDebugStreamLine("analong port %d: %d", i + 1, SensorValue[i]);
	}

	//Print digital sensors
	for (; i < kNumbDigitalSensors + 7; i++)
	{
		writeDebugStreamLine("digital port %d: %d", i - 7, SensorValue[i]);
	}

	writeDebugStreamLine("\n");

	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DRIVETRAIN CONTROL                                                                                                                DRIVETRAIN CONTROL //
// DRIVETRAIN CONTROL                                                                                                                DRIVETRAIN CONTROL //
// DRIVETRAIN CONTROL                                                                                                                DRIVETRAIN CONTROL //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
/*                                                                         */
/* Subroutine - Initializes the drivetrain                                 */
/*                                                                         */
/***************************************************************************/
#if defined(DRIVE_TANK_2) || defined(DRIVE_TANK_2_CUBIC)

void initializeDrivetrain(const tMotor left, const tMotor right, const tSensors leftQuad, const tSensors rightQuad)
{
	driveTrain.left = left;
	driveTrain.right = right;

	addMotor(left);
	addMotor(right);

	driveTrain.leftQuad = leftQuad;
	driveTrain.rightQuad = rightQuad;
}

void setTranslationPIDControllers(tSensors leftQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	leftTranslationController = newPIDController(leftQuad, kP, kI, kD);
	rightTranslationController = newPIDController(rightQuad, kP, kI, kD);
}

void setRotationPIDControllers(tSensors leftQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	leftRotationController = newPIDController(leftQuad, kP, kI, kD);
	rightRotationController = newPIDController(rightQuad, kP, kI, kD);
}

#endif

#if defined(DRIVE_TANK_4) || defined(DRIVE_TANK_4_CUBIC) || defined(DRIVE_X) || defined(DRIVE_X_HEADING) || defined(DRIVE_X_CUBIC) || defined(DRIVE_MECANUM) || defined(DRIVE_MECANUM_CUBIC)

void initializeDrivetrain(const tMotor frontLeft, const tMotor backLeft, const tMotor frontRight, const tMotor backRight, const tSensors leftQuad, const tSensors rightQuad)
{
	driveTrain.frontLeft = frontLeft;
	driveTrain.backLeft = backLeft;
	driveTrain.frontRight = frontRight;
	driveTrain.backRight = backRight;

	addMotor(frontLeft);
	addMotor(backLeft);
	addMotor(frontRight);
	addMotor(backRight);

	driveTrain.leftQuad = leftQuad;
	driveTrain.rightQuad = rightQuad;
}

void setTranslationPIDControllers(tSensors leftQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	leftTranslationController = newPIDController(leftQuad, kP, kI, kD);
	rightTranslationController = newPIDController(rightQuad, kP, kI, kD);
}

void setRotationPIDControllers(tSensors leftQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	leftRotationController = newPIDController(leftQuad, kP, kI, kD);
	rightRotationController = newPIDController(rightQuad, kP, kI, kD);
}

#endif

#if defined(DRIVE_P) || defined(DRIVE_P_CUBIC)

void initializeDrivetrain(const tMotor front, const tMotor back, const tMotor left, const tMotor right, const tSensors frontQuad, const tSensors leftQuad)
{
	driveTrain.front = front;
	driveTrain.back = back;
	driveTrain.left = left;
	driveTrain.right = right;

	addMotor(front);
	addMotor(back);
	addMotor(left);
	addMotor(right);

	drivetrain.frontQuad = frontQuad;
	driveTrain.leftQuad = leftQuad;
}

void setTranslationPIDControllers(tSensors leftQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	frontTranslationController = newPIDController(leftQuad, kP, kI, kD);
	leftTranslationController = newPIDController(rightQuad, kP, kI, kD);
}

void setRotationPIDControllers(tSensors leftQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	frontRotationController = newPIDController(leftQuad, kP, kI, kD);
	leftRotationController = newPIDController(rightQuad, kP, kI, kD);
}

#endif

#if defined(DRIVE_H) || defined(DRIVE_H_CUBIC)

void initializeDrivetrain(const tMotor frontLeft, const tMotor backLeft, const tMotor middle, const tMotor frontRight, const tMotor backRight, const tSensors leftQuad, const tSensors middleQuad, const tSensors rightQuad)
{
	driveTrain.frontLeft = frontLeft;
	driveTrain.backLeft = backLeft;
	driveTrain.middle = middle;
	driveTrain.frontRight = frontRight;
	driveTrain.backRight = backRight;

	addMotor(frontLeft);
	addMotor(backLeft);
	addMotor(middle);
	addMotor(frontRight);
	addMotor(backRight);

	driveTrain.leftQuad = leftQuad;
	driveTrain.middleQuad = middleQuad;
	driveTrain.rightQuad = rightQuad;
}

void setTranslationPIDControllers(tSensors leftQuad, tSensors middleQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	leftTranslationController = newPIDController(leftQuad, kP, kI, kD);
	middleTranslationController = newPIDController(middleQuad, kP, kI, kD);
	rightTranslationController = newPIDController(rightQuad, kP, kI, kD);
}

void setRotationPIDControllers(tSensors leftQuad, tSensors middleQuad,  tSensors rightQuad, const float kP, const float kI, const float kD)
{
	leftRotationController = newPIDController(leftQuad, kP, kI, kD);
	rightRotationController = newPIDController(rightQuad, kP, kI, kD);
}

#endif

#if defined(DRIVE_TANK_6) || defined(DRIVE_TANK_6_CUBIC)

void initializeDrivetrain(const tMotor frontLeft, const tMotor middleLeft, const tMotor backLeft, const tMotor frontRight, const tMotor middleRight, const tMotor backRight, const tSensors leftQuad, const tSensors rightQuad)
{
	driveTrain.frontLeft = frontLeft;
	driveTrain.middleLeft = middleLeft;
	driveTrain.backLeft = backLeft;
	driveTrain.frontRight = frontRight;
	driveTrain.middleRight = middleRight;
	driveTrain.backRight = backRight;

	addMotor(frontLeft);
	addMotor(middleLeft);
	addMotor(backLeft);
	addMotor(frontRight);
	addMotor(middleRight);
	addMotor(backRight);

	driveTrain.leftQuad = leftQuad;
	driveTrain.rightQuad = rightQuad;
}

void setTranslationPIDControllers(tSensors leftQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	leftTranslationController = newPIDController(leftQuad, kP, kI, kD);
	rightTranslationController = newPIDController(rightQuad, kP, kI, kD);
}

void setRotationPIDControllers(tSensors leftQuad, tSensors rightQuad, const float kP, const float kI, const float kD)
{
	leftRotationController = newPIDController(leftQuad, kP, kI, kD);
	rightRotationController = newPIDController(rightQuad, kP, kI, kD);
}

#endif

/***************************************************************************/
/*                                                                         */
/* Task - Drivetrain control task                                          */
/*                                                                         */
/***************************************************************************/
task drivetrainControl()
{
	#if defined(DRIVE_TANK_2)

		int leftV;
		int rightV;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			rightV = vexRT[JOY_DRIVE_RV];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			rightV = abs(rightV) < JOY_THRESHOLD ? 0 : rightV;

			_SetMotorSpeed(driveTrain.left, vexRT[JOY_DRIVE_LV]);
			_SetMotorSpeed(driveTrain.right, vexRT[JOY_DRIVE_RV]);
		}

	#endif

	#if defined(DRIVE_TANK_2_CUBIC)

		int leftV, speedLV;
		int rightV, speedRV;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			rightV = vexRT[JOY_DRIVE_RV];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			rightV = abs(rightV) < JOY_THRESHOLD ? 0 : rightV;

			speedLV = _Cube(leftV) / CUBED_127;
			speedRV = _Cube(rightV) / CUBED_127;

			_SetMotorSpeed(driveTrain.left, speedLV);
			_SetMotorSpeed(driveTrain.right, speedRV);
		}

	#endif

	#if defined(DRIVE_TANK_4)

		int leftV;
		int rightV;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			rightV = vexRT[JOY_DRIVE_RV];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			rightV = abs(rightV) < JOY_THRESHOLD ? 0 : rightV;

			_SetMotorSpeed(driveTrain.frontLeft, leftV);
			_SetMotorSpeed(driveTrain.backLeft, leftV);
			_SetMotorSpeed(driveTrain.frontRight, rightV);
			_SetMotorSpeed(driveTrain.backRight, rightV);
		}

	#endif

	#if defined(DRIVE_TANK_4_CUBIC)

		int leftV, speedLV;
		int rightV, speedRV;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			rightV = vexRT[JOY_DRIVE_RV];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			rightV = abs(rightV) < JOY_THRESHOLD ? 0 : rightV;

			speedLV = _Cube(leftV) / CUBED_127;
			speedRV = _Cube(rightV) / CUBED_127;

			_SetMotorSpeed(driveTrain.frontLeft, speedLV);
			_SetMotorSpeed(driveTrain.backLeft, speedLV);
			_SetMotorSpeed(driveTrain.frontRight, speedRV);
			_SetMotorSpeed(driveTrain.backRight, speedRV);
		}

	#endif

	#if defined(DRIVE_TANK_6)

		int leftV;
		int rightV;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			rightV = vexRT[JOY_DRIVE_RV];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			rightV = abs(rightV) < JOY_THRESHOLD ? 0 : rightV;

			_SetMotorSpeed(driveTrain.frontLeft, leftV);
			_SetMotorSpeed(driveTrain.middleLeft, leftV);
			_SetMotorSpeed(driveTrain.backLeft, leftV);
			_SetMotorSpeed(driveTrain.frontRight, rightV);
			_SetMotorSpeed(driveTrain.middleRight, rightV);
			_SetMotorSpeed(driveTrain.backRight, rightV);
		}

	#endif

	#if defined(DRIVE_TANK_6_CUBIC)

		int leftV, speedLV;
		int rightV, speedRV;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			rightV = vexRT[JOY_DRIVE_RV];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			rightV = abs(rightV) < JOY_THRESHOLD ? 0 : rightV;

			speedLV = _Cube(leftV) / CUBED_127;
			speedRV = _Cube(rightV) / CUBED_127;

			_SetMotorSpeed(driveTrain.frontLeft, speedLV);
			_SetMotorSpeed(driveTrain.middleLeft, speedLV);
			_SetMotorSpeed(driveTrain.backLeft, speedLV);
			_SetMotorSpeed(driveTrain.frontRight, speedRV);
			_SetMotorSpeed(driveTrain.middleRight, speedRV);
			_SetMotorSpeed(driveTrain.backRight, speedRV);
		}

	#endif

	#if defined(DRIVE_H)

		int leftV, leftH;
		int rightH;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			_SetMotorSpeed(driveTrain.frontLeft, leftV + leftH);
			_SetMotorSpeed(driveTrain.backLeft, leftV + leftH);
			_SetMotorSpeed(driveTrain.middle, rightH);
			_SetMotorSpeed(driveTrain.frontRight, leftV - leftH);
			_SetMotorSpeed(driveTrain.backRight, leftV - leftH);
		}

	#endif

	#if defined(DRIVE_H_CUBIC)

		int leftV, leftH, speedLV, speedLH;
		int rightH, speedRH;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			speedLV = _Cube(leftV) / CUBED_127;
			speedLH = _Cube(leftH) / CUBED_127;
			speedRH = _Cube(rightH) / CUBED_127;

			_SetMotorSpeed(driveTrain.frontLeft, speedLV + speedLH);
			_SetMotorSpeed(driveTrain.backLeft, speedLV + speedLH);
			_SetMotorSpeed(driveTrain.middle, speedRH);
			_SetMotorSpeed(driveTrain.frontRight, speedLV - speedLH);
			_SetMotorSpeed(driveTrain.backRight, speedLV - speedLH);
		}

	#endif

	#if defined(DRIVE_X)

		int leftV, leftH;
		int rightH;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			_SetMotorSpeed(driveTrain.frontLeft, leftV + leftH + rightH);
			_SetMotorSpeed(driveTrain.backLeft, leftV - leftH + rightH);
			_SetMotorSpeed(driveTrain.frontRight, leftV - leftH - rightH);
			_SetMotorSpeed(driveTrain.backRight, leftV + leftH - rightH);
		}

	#endif

	#if defined(DRIVE_X_HEADING)

		int leftV, leftH;
		int rightH;

		const float gyroOffset = 90.0;
		float gyroVal, a, b, radius, theta;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			gyroVal = gyroOffset + (SensorValue[gyro] / 10.0);

			//Convert joystick values to polar
			radius = sqrt((leftH * leftH) + (leftV * leftV));
			theta = atan2(leftV, leftH) * 180.0 / PI;

			//Adjust for robot angle
			theta -= gyroVal;

			//Calculate opposite-side speeds
			a = (cosDegrees(theta + 90.0) + sinDegrees(theta + 90.0)) * radius;
			b = (cosDegrees(theta) + sinDegrees(theta)) * radius;

			_SetMotorSpeed(driveTrain.frontLeft, a + rightH);
			_SetMotorSpeed(driveTrain.backLeft, b + rightH);
			_SetMotorSpeed(driveTrain.frontRight, b - rightH);
			_SetMotorSpeed(driveTrain.backRight, a - rightH);
		}

	#endif

	#if defined(DRIVE_X_CUBIC)

		int leftV, leftH, speedLV, speedLH;
		int rightH, speedRH;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			speedLV = _Cube(leftV) / CUBED_127;
			speedLH = _Cube(leftH) / CUBED_127;
			speedRH = _Cube(rightH) / CUBED_127;

			_SetMotorSpeed(driveTrain.frontLeft, speedLV + speedLH + speedRH);
			_SetMotorSpeed(driveTrain.backLeft, speedLV - speedLH + speedRH);
			_SetMotorSpeed(driveTrain.frontRight, speedLV - speedLH - speedRH);
			_SetMotorSpeed(driveTrain.backRight, speedLV + speedLH - speedRH);
		}

	#endif

	#if defined(DRIVE_MECANUM)

		int leftV, leftH;
		int rightH;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			_SetMotorSpeed(driveTrain.frontLeft, leftV + rightH + leftH);
			_SetMotorSpeed(driveTrain.backLeft, leftV + rightH - leftH);
			_SetMotorSpeed(driveTrain.frontRight, leftV - rightH - leftH);
			_SetMotorSpeed(driveTrain.backRight, leftV - rightH + leftH);
		}

	#endif

	#if defined(DRIVE_MECANUM_CUBIC)

		int leftV, leftH, speedLV, speedLH;
		int rightH, speedRH;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			speedLV = _Cube(leftV) / CUBED_127;
			speedLH = _Cube(leftH) / CUBED_127;
			speedRH = _Cube(rightH) / CUBED_127;

			_SetMotorSpeed(driveTrain.frontLeft, speedLV + speedRH + speedLH);
			_SetMotorSpeed(driveTrain.backLeft, speedLV + speedRH - speedLH);
			_SetMotorSpeed(driveTrain.frontRight, speedLV - speedRH - speedLH);
			_SetMotorSpeed(driveTrain.backRight, speedLV - speedRH + speedLH);
		}

	#endif

	#if defined(DRIVE_P)

		int leftV, leftH;
		int rightH;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			_SetMotorSpeed(driveTrain.front, -leftH - rightH);
			_SetMotorSpeed(driveTrain.left, -leftV - rightH);
			_SetMotorSpeed(driveTrain.right, leftV - rightH);
			_SetMotorSpeed(driveTrain.back, leftH - rightH);
		}

	#endif

	#if defined(DRIVE_P_CUBIC)

		int leftV, leftH, speedLV, speedLH;
		int rightH, speedRH;

		while (true)
		{
			leftV = vexRT[JOY_DRIVE_LV];
			leftH = vexRT[JOY_DRIVE_LH];
			rightH = vexRT[JOY_DRIVE_RH];

			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
			rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

			speedLV = _Cube(leftV) / CUBED_127;
			speedLH = _Cube(leftH) / CUBED_127;
			speedRH = _Cube(rightH) / CUBED_127;

			_SetMotorSpeed(driveTrain.front, -speedLH - speedRH);
			_SetMotorSpeed(driveTrain.left, -speedLV - speedRH);
			_SetMotorSpeed(driveTrain.right, speedLV - speedRH);
			_SetMotorSpeed(driveTrain.back, speedLH - speedRH);
		}

	#endif
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Starts drivetrain control                                  */
/*                                                                         */
/***************************************************************************/
void startDrivetrainControl()
{
	startMotorSlewRateTask();
	startTask(drivetrainControl);
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Stops drivetrain control                                   */
/*                                                                         */
/***************************************************************************/
void stopDrivetrainControl()
{
	stopTask(drivetrainControl);
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives forward or backward                                 */
/*                                                                         */
/***************************************************************************/
#if defined(DRIVE_TANK_2) || defined(DRIVE_TANK_2_CUBIC)

void drive(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	_SetTargetPosition(leftTranslationController, ticks);
	_SetTargetPosition(rightTranslationController, ticks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks))
	{
		updatePIDController(leftTranslationController);
		updatePIDController(rightTranslationController);

		_SetMotorSpeed(driveTrain.left, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.right, _GetPIDSpeed(rightTranslationController));
	}

	_SetMotorSpeed(driveTrain.left, 0);
	_SetMotorSpeed(driveTrain.right, 0);
}

#endif

#if defined(DRIVE_TANK_4) || defined(DRIVE_TANK_4_CUBIC) || defined(DRIVE_H) || defined(DRIVE_H_CUBIC) || defined(DRIVE_MECANUM) || defined(DRIVE_MECANUM_CUBIC)

void drive(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	_SetTargetPosition(leftTranslationController, ticks);
	_SetTargetPosition(rightTranslationController, ticks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks))
	{
		updatePIDController(leftTranslationController);
		updatePIDController(rightTranslationController);

		_SetMotorSpeed(driveTrain.frontLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.frontRight, _GetPIDSpeed(rightTranslationController));
		_SetMotorSpeed(driveTrain.backLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.backRight, _GetPIDSpeed(rightTranslationController));
	}

	_SetMotorSpeed(driveTrain.frontLeft, 0);
	_SetMotorSpeed(driveTrain.backLeft, 0);
	_SetMotorSpeed(driveTrain.frontRight, 0);
	_SetMotorSpeed(driveTrain.backRight, 0);
}

#endif

#if defined(DRIVE_X) || defined(DRIVE_X_HEADING) || defined(DRIVE_X_CUBIC)

void drive(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	const int totalTicks = ticks * ROOT_2;

	_SetTargetPosition(leftTranslationController, totalTicks);
	_SetTargetPosition(rightTranslationController, totalTicks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(totalTicks))
	{
		updatePIDController(leftTranslationController);
		updatePIDController(rightTranslationController);

		_SetMotorSpeed(driveTrain.frontLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.backLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.frontRight, _GetPIDSpeed(rightTranslationController));
		_SetMotorSpeed(driveTrain.backRight, _GetPIDSpeed(rightTranslationController));
	}

	_SetMotorSpeed(driveTrain.frontLeft, 0);
	_SetMotorSpeed(driveTrain.backLeft, 0);
	_SetMotorSpeed(driveTrain.frontRight, 0);
	_SetMotorSpeed(driveTrain.backRight, 0);
}

#endif

#if defined(DRIVE_TANK_6) || defined(DRIVE_TANK_6_CUBIC)

void drive(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	_SetTargetPosition(leftTranslationController, ticks);
	_SetTargetPosition(rightTranslationController, ticks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks) || abs(SensorValue[driveTrain.rightQuad]) < abs(ticks))
	{
		updatePIDController(leftTranslationController);
		updatePIDController(rightTranslationController);

		_SetMotorSpeed(driveTrain.frontLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.middleLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.backLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.middleRight, _GetPIDSpeed(rightTranslationController));
		_SetMotorSpeed(driveTrain.frontRight, _GetPIDSpeed(rightTranslationController));
		_SetMotorSpeed(driveTrain.backRight, _GetPIDSpeed(rightTranslationController));
	}

	_SetMotorSpeed(driveTrain.frontLeft, 0);
	_SetMotorSpeed(driveTrain.middleLeft, 0);
	_SetMotorSpeed(driveTrain.backLeft, 0);
	_SetMotorSpeed(driveTrain.frontRight, 0);
	_SetMotorSpeed(driveTrain.middleRight, 0);
	_SetMotorSpeed(driveTrain.backRight, 0);
}

#endif

#if defined(DRIVE_P) || defined(DRIVE_P_CUBIC)

void drive(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;

	_SetTargetPosition(leftTranslationController, ticks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks))
	{
		updatePIDController(leftTranslationController);

		_SetMotorSpeed(driveTrain.left, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.right, _GetPIDSpeed(leftTranslationController));
	}

	_SetMotorSpeed(driveTrain.left, 0);
	_SetMotorSpeed(driveTrain.right, 0);
}

#endif

/***************************************************************************/
/*                                                                         */
/* Subroutine - Strafes left or right                                      */
/*                                                                         */
/***************************************************************************/
#if defined(DRIVE_H) || defined(DRIVE_H_CUBIC)

void strafe(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.middleQuad] = 0;

	_SetTargetPosition(middleTranslationController, ticks);

	while (abs(SensorValue[driveTrain.middleQuad]) < abs(ticks))
	{
		updatePIDController(middleTranslationController);

		_SetMotorSpeed(driveTrain.middle, _GetPIDSpeed(middleTranslationController));
	}

	_SetMotorSpeed(driveTrain.middle, 0);
}

#endif

#if defined(DRIVE_X) || defined(DRIVE_X_HEADING) || defined(DRIVE_X_CUBIC)

void strafe(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	const int totalTicks = ticks * ROOT_2;

	if (ticks > 0)
	{
		_SetTargetPosition(leftTranslationController, totalTicks);
		_SetTargetPosition(rightTranslationController, -totalTicks);
	}
	else
	{
		_SetTargetPosition(leftTranslationController, -totalTicks);
		_SetTargetPosition(rightTranslationController, totalTicks);
	}

	while (abs(SensorValue[leftQuad]) < abs(totalTicks))
	{
		updatePIDController(leftTranslationController);
		updatePIDController(rightTranslationController);

		_SetMotorSpeed(driveTrain.frontLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.frontRight, _GetPIDSpeed(rightTranslationController));
		_SetMotorSpeed(driveTrain.backLeft, -1 * _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.backRight, -1 * _GetPIDSpeed(rightTranslationController));
	}

	_SetMotorSpeed(driveTrain.frontLeft, 0);
	_SetMotorSpeed(driveTrain.backLeft, 0);
	_SetMotorSpeed(driveTrain.frontRight, 0);
	_SetMotorSpeed(driveTrain.backRight, 0);
}

#endif

#if defined(DRIVE_MECANUM) || defined(DRIVE_MECANUM_CUBIC)

void strafe(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	if (ticks > 0)
	{
		_SetTargetPosition(leftTranslationController, ticks);
		_SetTargetPosition(rightTranslationController, -ticks);
	}
	else
	{
		_SetTargetPosition(leftTranslationController, -ticks);
		_SetTargetPosition(rightTranslationController, ticks);
	}

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks))
	{
		updatePIDController(leftTranslationController);
		updatePIDController(rightTranslationController);

		_SetMotorSpeed(driveTrain.frontLeft, _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.frontRight, _GetPIDSpeed(rightTranslationController));
		_SetMotorSpeed(driveTrain.backLeft, -1 * _GetPIDSpeed(leftTranslationController));
		_SetMotorSpeed(driveTrain.backRight, -1 * _GetPIDSpeed(rightTranslationController));
	}

	_SetMotorSpeed(driveTrain.frontLeft, 0);
	_SetMotorSpeed(driveTrain.backLeft, 0);
	_SetMotorSpeed(driveTrain.frontRight, 0);
	_SetMotorSpeed(driveTrain.backRight, 0);
}

#endif

#if defined(DRIVE_P) || defined(DRIVE_P_CUBIC)

void strafe(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.frontQuad] = 0;

	_SetTargetPosition(frontTranslationController, ticks);

	while (abs(SensorValue[driveTrain.frontQuad]) < abs(ticks))
	{
		updatePIDController(frontTranslationController);

		_SetMotorSpeed(driveTrain.front, _GetPIDSpeed(frontTranslationController));
		_SetMotorSpeed(driveTrain.back, _GetPIDSpeed(frontTranslationController));
	}

	_SetMotorSpeed(driveTrain.front, 0);
	_SetMotorSpeed(driveTrain.back, 0);
}

#endif

/***************************************************************************/
/*                                                                         */
/* Subroutine - Performs a point turn                                      */
/*                                                                         */
/***************************************************************************/
#if defined(DRIVE_TANK_2) || defined(DRIVE_TANK_2_CUBIC)

void turnPID(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	_SetTargetPosition(leftRotationController, ticks);
	_SetTargetPosition(rightRotationController, -ticks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks))
	{
		updatePIDController(leftRotationController);
		updatePIDController(rightRotationController);

		_SetMotorSpeed(driveTrain.left, _GetPIDSpeed(leftRotationController));
		_SetMotorSpeed(driveTrain.right, _GetPIDSpeed(rightRotationController));
	}

	_SetMotorSpeed(driveTrain.left, 0);
	_SetMotorSpeed(driveTrain.right, 0);
}

#endif

#if defined(DRIVE_TANK_4) || defined(DRIVE_TANK_4_CUBIC) || defined(DRIVE_H) || defined(DRIVE_H_CUBIC) || defined(DRIVE_MECANUM) || defined(DRIVE_MECANUM_CUBIC) || defined(DRIVE_X) || defined(DRIVE_X_HEADING) || defined(DRIVE_X_CUBIC)

void turnPID(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	_SetTargetPosition(leftRotationController, ticks);
	_SetTargetPosition(rightRotationController, -ticks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks) || abs(SensorValue[driveTrain.rightQuad]) < abs(ticks))
	{
		updatePIDController(leftRotationController);
		updatePIDController(rightRotationController);

		_SetMotorSpeed(driveTrain.frontLeft, _GetPIDSpeed(leftRotationController));
		_SetMotorSpeed(driveTrain.backLeft, _GetPIDSpeed(leftRotationController));
		_SetMotorSpeed(driveTrain.frontRight, _GetPIDSpeed(rightRotationController));
		_SetMotorSpeed(driveTrain.backRight, _GetPIDSpeed(rightRotationController));
	}

	_SetMotorSpeed(driveTrain.frontLeft, 0);
	_SetMotorSpeed(driveTrain.backLeft, 0);
	_SetMotorSpeed(driveTrain.frontRight, 0);
	_SetMotorSpeed(driveTrain.backRight, 0);
}

#endif

#if defined(DRIVE_TANK_6) || defined(DRIVE_TANK_6_CUBIC)

void turnPID(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.leftQuad] = 0;
	SensorValue[driveTrain.rightQuad] = 0;

	_SetTargetPosition(leftRotationController, ticks);
	_SetTargetPosition(rightRotationController, -ticks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks))
	{
		updatePIDController(leftRotationController);
		updatePIDController(rightRotationController);

		_SetMotorSpeed(driveTrain.frontLeft, _GetPIDSpeed(leftRotationController));
		_SetMotorSpeed(driveTrain.middleLeft, _GetPIDSpeed(leftRotationController));
		_SetMotorSpeed(driveTrain.backLeft, _GetPIDSpeed(leftRotationController));
		_SetMotorSpeed(driveTrain.middleRight, _GetPIDSpeed(rightRotationController));
		_SetMotorSpeed(driveTrain.frontRight, _GetPIDSpeed(rightRotationController));
		_SetMotorSpeed(driveTrain.backRight, _GetPIDSpeed(rightRotationController));
	}

	_SetMotorSpeed(driveTrain.frontLeft, 0);
	_SetMotorSpeed(driveTrain.backRight, 0);
	_SetMotorSpeed(driveTrain.backLeft, 0);
	_SetMotorSpeed(driveTrain.frontRight, 0);
	_SetMotorSpeed(driveTrain.middleRight, 0);
	_SetMotorSpeed(driveTrain.backRight, 0);
}

#endif

#if defined(DRIVE_P) || defined(DRIVE_P_CUBIC)

void turnPID(const int ticks)
{
	startMotorSlewRateTask();

	SensorValue[driveTrain.frontQuad] = 0;
	SensorValue[driveTrain.leftQuad] = 0;

	_SetTargetPosition(frontRotationController, ticks);
	_SetTargetPosition(leftRotationController, ticks);

	while (abs(SensorValue[driveTrain.leftQuad]) < abs(ticks))
	{
		updatePIDController(frontRotationController);
		updatePIDController(leftRotationController);

		_SetMotorSpeed(driveTrain.left, _GetPIDSpeed(leftRotationController));
		_SetMotorSpeed(driveTrain.front, _GetPIDSpeed(frontRotationController));
		_SetMotorSpeed(driveTrain.right, -1 * _GetPIDSpeed(leftRotationController));
		_SetMotorSpeed(driveTrain.back, -1 * _GetPIDSpeed(frontRotationController));
	}

	_SetMotorSpeed(driveTrain.front, 0);
	_SetMotorSpeed(driveTrain.left, 0);
	_SetMotorSpeed(driveTrain.right, 0);
	_SetMotorSpeed(driveTrain.back, 0);
}

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LIFT CONTROL                                                                                                                            LIFT CONTROL //
// LIFT CONTROL                                                                                                                            LIFT CONTROL //
// LIFT CONTROL                                                                                                                            LIFT CONTROL //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
/*                                                                         */
/* Subroutine - Initializes the lift                                       */
/*                                                                         */
/***************************************************************************/
#if defined(LIFT_2_1)

void initializeLift(const tMotor left, const tMotor right, const tSensors liftQuad, const float kP, const float kI, const float kD, const float kBias = 0.0)
{
	liftSystem.left = left;
	liftSystem.right = right;

	addMotor(left);
	addMotor(right);

	liftSystem.liftQuad = liftQuad;

	liftSystemController = newPIDController(liftQuad, _GetMotor(left), kP, kI, kD);
}

#endif

#if defined(LIFT_4_1)

void initializeLift(const tMotor leftTop, const tMotor leftBottom, const tMotor rightTop, const tMotor rightBottom, const tSensors liftQuad, const float kP, const float kI, const float kD, const float kBias = 0.0)
{
	liftSystem.leftTop = leftTop;
	liftSystem.leftBottom = leftBottom;
	liftSystem.rightTop = rightTop;
	liftSystem.rightBottom = rightBottom;

	addMotor(leftTop);
	addMotor(leftBottom);
	addMotor(rightTop);
	addMotor(rightBottom);

	liftSystem.liftQuad = liftQuad;

	liftSystemController = newPIDController(liftQuad, _GetMotor(leftTop), kP, kI, kD);
}

#endif


#if defined(LIFT_6_1)

void initializeLift(const tMotor leftTop, const tMotor middleLeft, const tMotor leftBottom, const tMotor rightTop, const tMotor middleRight, const tMotor rightBottom, const tSensors liftQuad, const float kP, const float kI, const float kD, const float kBias = 0.0)
{
	liftSystem.leftTop = leftTop;
	liftSystem.middleLeft = middleLeft;
	liftSystem.leftBottom = leftBottom;
	liftSystem.rightTop = rightTop;
	liftSystem.middleRight = middleRight;
	liftSystem.rightBottom = rightBottom;

	addMotor(leftTop);
	addMotor(middleLeft);
	addMotor(leftBottom);
	addMotor(rightTop);
	addMotor(middleRight);
	addMotor(rightBottom);

	liftSystem.liftQuad = liftQuad;

	liftSystemController = newPIDController(liftQuad, _GetMotor(leftTop), kP, kI, kD);
}

#endif

#if defined(LIFT_2_2)

void initializeLift(const tMotor left, const tMotor right, const tSensors leftQuad, const tSensors rightQuad, const float kP, const float kI, const float kD, const float kBias = 0.0)
{
	liftSystem.left = left;
	liftSystem.right = right;

	addMotor(left);
	addMotor(right);

	liftSystem.leftQuad = leftQuad;
	liftSystem.rightQuad = rightQuad;

	liftSystemLeftController = newPIDController(leftQuad, _GetMotor(left), kP, kI, kD);
	liftSystemRightController = newPIDController(rightQuad, _GetMotor(right), kP, kI, kD);
}

#endif

#if defined(LIFT_4_2)

void initializeLift(const tMotor leftTop, const tMotor leftBottom, const tMotor rightTop, const tMotor rightBottom, const tSensors leftQuad, const tSensors rightQuad, const float kP, const float kI, const float kD, const float kBias = 0.0, const float errorThreshold = 15.0, const float integralLimit = 15.0)
{
	liftSystem.leftTop = leftTop;
	liftSystem.leftBottom = leftBottom;
	liftSystem.rightTop = rightTop;
	liftSystem.rightBottom = rightBottom;

	addMotor(leftTop);
	addMotor(leftBottom);
	addMotor(rightTop);
	addMotor(rightBottom);

	liftSystem.leftQuad = leftQuad;
	liftSystem.rightQuad = rightQuad;

	liftSystemLeftController = newPIDController(leftQuad, kP, kI, kD, errorThreshold, integralLimit);
	liftSystemRightController = newPIDController(rightQuad, kP, kI, kD);
}

#endif

#if defined(LIFT_6_2)

void initializeLift(const tMotor leftTop, const tMotor middleLeft, const tMotor leftBottom, const tMotor rightTop, const tMotor middleRight, const tMotor rightBottom, const tSensors leftQuad, const tSensors rightQuad, const float kP, const float kI, const float kD, const float kBias = 0.0)
{
	liftSystem.leftTop = leftTop;
	liftSystem.middleLeft = middleLeft;
	liftSystem.leftBottom = leftBottom;
	liftSystem.rightTop = rightTop;
	liftSystem.middleRight = middleRight;
	liftSystem.rightBottom = rightBottom;

	addMotor(leftTop);
	addMotor(middleLeft);
	addMotor(leftBottom);
	addMotor(rightTop);
	addMotor(middleRight);
	addMotor(rightBottom);

	liftSystem.leftQuad = leftQuad;
	liftSystem.rightQuad = rightQuad;

	liftSystemLeftController = newPIDController(leftQuad, _GetMotor(leftTop), kP, kI, kD);
	liftSystemRightController = newPIDController(rightQuad, _GetMotor(rightTop), kP, kI, kD);
}

#endif

/***************************************************************************/
/*                                                                         */
/* Task - Lift control                                                     */
/*                                                                         */
/***************************************************************************/
task liftControl()
{
	#ifndef LIFT_UNSAFE
		stopLiftPositionUpdater();
	#endif

	#if defined(LIFT_2_1) || defined(LIFT_2_2)

		while (true)
		{
			if (vexRT[LIFT_UP])
			{
				_SetMotorSpeed(liftSystem.left, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.right, LIFT_SPEED);
			}
			else if (vexRT[LIFT_DOWN])
			{
				_SetMotorSpeed(liftSystem.left, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.right, -LIFT_SPEED);
			}
			else
			{
				_SetMotorSpeed(liftSystem.left, 0);
				_SetMotorSpeed(liftSystem.right, 0);
			}
		}

	#endif

	#if defined(LIFT_4_1) || defined(LIFT_4_2)

		while (true)
		{
			if (vexRT[LIFT_UP])
			{
				_SetMotorSpeed(liftSystem.leftTop, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.leftBottom, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.rightTop, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.rightBottom, LIFT_SPEED);
			}
			else if (vexRT[LIFT_DOWN])
			{
				_SetMotorSpeed(liftSystem.leftTop, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.leftBottom, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.rightTop, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.rightBottom, -LIFT_SPEED);
			}
			else
			{
				_SetMotorSpeed(liftSystem.leftTop, 0);
				_SetMotorSpeed(liftSystem.leftBottom, 0);
				_SetMotorSpeed(liftSystem.rightTop, 0);
				_SetMotorSpeed(liftSystem.rightBottom, 0);
			}
		}

	#endif

	#if defined(LIFT_6_1) || defined(LIFT_6_2)

		while (true)
		{
			if (vexRT[LIFT_UP])
			{
				_SetMotorSpeed(liftSystem.leftTop, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.middleLeft, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.leftBottom, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.rightTop, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.middleRight, LIFT_SPEED);
				_SetMotorSpeed(liftSystem.rightBottom, LIFT_SPEED);
			}
			else if (vexRT[LIFT_DOWN])
			{
				_SetMotorSpeed(liftSystem.leftTop, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.middleLeft, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.leftBottom, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.rightTop, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.middleRight, -LIFT_SPEED);
				_SetMotorSpeed(liftSystem.rightBottom, -LIFT_SPEED);
			}
			else
			{
				_SetMotorSpeed(liftSystem.leftTop, 0);
				_SetMotorSpeed(liftSystem.middleLeft, 0);
				_SetMotorSpeed(liftSystem.leftBottom, 0);
				_SetMotorSpeed(liftSystem.rightTop, 0);
				_SetMotorSpeed(liftSystem.middleRight, 0);
				_SetMotorSpeed(liftSystem.rightBottom, 0);
			}
		}

	#endif
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Starts lift control                                        */
/*                                                                         */
/***************************************************************************/
void startLiftControl()
{
	startMotorSlewRateTask();
	startTask(liftControl);
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Stops lift control                                         */
/*                                                                         */
/***************************************************************************/
void stopLiftControl()
{
	stopTask(liftControl);
}

/***************************************************************************/
/*                                                                         */
/* Task - Updates the lift's position                                      */
/*                                                                         */
/***************************************************************************/
task updateLiftPosition()
{
	#ifndef LIFT_UNSAFE
		stopLiftControl();
	#endif

	#if defined(LIFT_2_1)

		while (true)
		{
			updatePIDController(liftSystemController);
			_SetMotorSpeed(liftSystem.right, _GetMotorSpeed(liftSystem.left));
		}

	#endif

	#if defined(LIFT_4_1)

		while (true)
		{
			updatePIDController(liftSystemController);
			_SetMotorSpeed(liftSystem.leftBottom, _GetMotorSpeed(liftSystem.leftTop));
			_SetMotorSpeed(liftSystem.rightTop, _GetMotorSpeed(liftSystem.leftTop));
			_SetMotorSpeed(liftSystem.rightBottom, _GetMotorSpeed(liftSystem.leftTop));
		}

	#endif

	#if defined(LIFT_6_1)

		while (true)
		{
			updatePIDController(liftSystemController);
			_SetMotorSpeed(liftSystem.middleLeft, _GetMotorSpeed(liftSystem.leftTop));
			_SetMotorSpeed(liftSystem.leftBottom, _GetMotorSpeed(liftSystem.leftTop));
			_SetMotorSpeed(liftSystem.rightTop, _GetMotorSpeed(liftSystem.leftTop));
			_SetMotorSpeed(liftSystem.middleRight, _GetMotorSpeed(liftSystem.leftTop));
			_SetMotorSpeed(liftSystem.rightBottom, _GetMotorSpeed(liftSystem.leftTop));
		}

	#endif

	#if defined(LIFT_2_2)

		while (true)
		{
			updatePIDController(liftSystemLeftController);
			updatePIDController(liftSystemRightController);
		}

	#endif

	#if defined(LIFT_4_2)

		while (true)
		{
			updatePIDController(liftSystemLeftController);
			updatePIDController(liftSystemRightController);

			_SetMotorSpeed(liftSystem.leftTop, _GetPIDSpeed(liftSystemLeftController));
			_SetMotorSpeed(liftSystem.leftBottom, _GetPIDSpeed(liftSystemLeftController));
			_SetMotorSpeed(liftSystem.rightTop, _GetPIDSpeed(liftSystemRightController));
			_SetMotorSpeed(liftSystem.rightBottom, _GetPIDSpeed(liftSystemRightController));

			wait1Msec(25);
		}

	#endif

	#if defined(LIFT_6_2)

		while (true)
		{
			updatePIDController(liftSystemLeftController);
			updatePIDController(liftSystemRightController);
			_SetMotorSpeed(liftSystem.middleLeft, _GetMotorSpeed(liftSystem.leftTop));
			_SetMotorSpeed(liftSystem.leftBottom, _GetMotorSpeed(liftSystem.leftTop));
			_SetMotorSpeed(liftSystem.middleRight, _GetMotorSpeed(liftSystem.rightTop));
			_SetMotorSpeed(liftSystem.rightBottom, _GetMotorSpeed(liftSystem.rightTop));
		}

	#endif
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Starts the lift position updater                           */
/*                                                                         */
/***************************************************************************/
void startLiftPositionUpdater()
{
	startTask(MotorSlewRateTask);
	startTask(updateLiftPosition);
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Stops the lift position updater                            */
/*                                                                         */
/***************************************************************************/
void stopLiftPositionUpdater()
{
	stopTask(updateLiftPosition);
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Sends the lift's target position in encoder counts         */
/*                                                                         */
/***************************************************************************/
void setLiftTargetPosition(const int pos)
{
	startMotorSlewRateTask();

	#if defined(LIFT_2_1) || defined(LIFT_4_1) || defined(LIFT_6_1)

		_SetTargetPosition(liftSystemController, pos);

	#endif

	#if defined(LIFT_2_2) || defined(LIFT_4_2) || defined(LIFT_6_2)

		_SetTargetPosition(liftSystemLeftController, pos);
		_SetTargetPosition(liftSystemRightController, pos);

	#endif
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Sends the lift to a position in encoder counts (interrupt) */
/*                                                                         */
/***************************************************************************/
#if defined(LIFT_2_1)

void sendLiftToPosition(const int pos)
{
	stopLiftControl();
	startMotorSlewRateTask();

	_SetTargetPosition(liftSystemController, pos);

	while ((abs(SensorValue[liftSystem.liftQuad]) < (abs(pos) - 5)) || (abs(SensorValue[liftSystem.liftQuad]) > (abs(pos) + 5)))
	{
		updatePIDController(liftSystemController);

		_SetMotorSpeed(liftSystem.right, _GetMotorSpeed(liftSystem.left));
	}

	_SetMotorSpeed(liftSystem.left, 0);
	_SetMotorSpeed(liftSystem.right, 0);
	startLiftControl();
}

#endif

#if defined(LIFT_4_1)

void sendLiftToPosition(const int pos)
{
	stopLiftControl();
	startMotorSlewRateTask();

	_SetTargetPosition(liftSystemController, pos);

	while ((abs(SensorValue[liftSystem.liftQuad]) < (abs(pos) - 5)) || (abs(SensorValue[liftSystem.liftQuad]) > (abs(pos) + 5)))
	{
		updatePIDController(liftSystemController);

		_SetMotorSpeed(liftSystem.leftBottom, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.rightTop, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.rightBottom, _GetMotorSpeed(liftSystem.leftTop));
	}

	_SetMotorSpeed(liftSystem.leftTop, 0);
	_SetMotorSpeed(liftSystem.leftBottom, 0);
	_SetMotorSpeed(liftSystem.rightTop, 0);
	_SetMotorSpeed(liftSystem.rightBottom, 0);
	startLiftControl();
}

#endif

#if defined(LIFT_6_1)

void sendLiftToPosition(const int pos)
{
	stopLiftControl();
	startMotorSlewRateTask();

	_SetTargetPosition(liftSystemController, pos);

	while ((abs(SensorValue[liftSystem.liftQuad]) < (abs(pos) - 5)) || (abs(SensorValue[liftSystem.liftQuad]) > (abs(pos) + 5)))
	{
		updatePIDController(liftSystemController);

		_SetMotorSpeed(liftSystem.middleLeft, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.leftBottom, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.rightTop, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.middleRight, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.rightBottom, _GetMotorSpeed(liftSystem.leftTop));
	}

	_SetMotorSpeed(liftSystem.middleLeft, 0);
	_SetMotorSpeed(liftSystem.leftTop, 0);
	_SetMotorSpeed(liftSystem.leftBottom, 0);
	_SetMotorSpeed(liftSystem.rightTop, 0);
	_SetMotorSpeed(liftSystem.middleRight, 0);
	_SetMotorSpeed(liftSystem.rightBottom, 0);
	startLiftControl();
}

#endif

#if defined(LIFT_2_2)

void sendLiftToPosition(const int pos)
{
	stopLiftControl();
	startMotorSlewRateTask();

	_SetTargetPosition(liftSystemLeftController, pos);
	_SetTargetPosition(liftSystemRightController, pos);

	while ((abs(SensorValue[liftSystem.liftQuad]) < (abs(pos) - 5)) || (abs(SensorValue[liftSystem.liftQuad]) > (abs(pos) + 5)))
	{
		updatePIDController(liftSystemLeftController);
		updatePIDController(liftSystemRightController);

		_SetMotorSpeed(liftSystem.right, _GetMotorSpeed(liftSystem.left));
	}

	_SetMotorSpeed(liftSystem.left, 0);
	_SetMotorSpeed(liftSystem.right, 0);
	startLiftControl();
}

#endif

#if defined(LIFT_4_2)

void sendLiftToPosition(const int pos)
{
	stopLiftControl();
	startMotorSlewRateTask();

	_SetTargetPosition(liftSystemLeftController, pos);
	_SetTargetPosition(liftSystemRightController, pos);

	while ((abs(SensorValue[liftSystem.leftQuad]) < (abs(pos) - 5)) || (abs(SensorValue[liftSystem.rightQuad]) > (abs(pos) + 5)))
	{
		updatePIDController(liftSystemLeftController);
		updatePIDController(liftSystemRightController);

		_SetMotorSpeed(liftSystem.leftBottom, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.rightTop, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.rightBottom, _GetMotorSpeed(liftSystem.leftTop));
	}

	_SetMotorSpeed(liftSystem.leftTop, 0);
	_SetMotorSpeed(liftSystem.leftBottom, 0);
	_SetMotorSpeed(liftSystem.rightTop, 0);
	_SetMotorSpeed(liftSystem.rightBottom, 0);
	startLiftControl();
}

#endif

#if defined(LIFT_6_2)

void sendLiftToPosition(const int pos)
{
	stopLiftControl();
	startMotorSlewRateTask();

	_SetTargetPosition(liftSystemLeftController, pos);
	_SetTargetPosition(liftSystemRightController, pos);

	while ((abs(SensorValue[liftSystem.liftQuad]) < (abs(pos) - 5)) || (abs(SensorValue[liftSystem.liftQuad]) > (abs(pos) + 5)))
	{
		updatePIDController(liftSystemLeftController);
		updatePIDController(liftSystemRightController);

		_SetMotorSpeed(liftSystem.middleLeft, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.leftBottom, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.rightTop, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.middleRight, _GetMotorSpeed(liftSystem.leftTop));
		_SetMotorSpeed(liftSystem.rightBottom, _GetMotorSpeed(liftSystem.leftTop));
	}

	_SetMotorSpeed(liftSystem.middleLeft, 0);
	_SetMotorSpeed(liftSystem.leftTop, 0);
	_SetMotorSpeed(liftSystem.leftBottom, 0);
	_SetMotorSpeed(liftSystem.rightTop, 0);
	_SetMotorSpeed(liftSystem.middleRight, 0);
	_SetMotorSpeed(liftSystem.rightBottom, 0);
	startLiftControl();
}

#endif
#endif

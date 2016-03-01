#ifndef AUTONOMOUSFUNCTIONS_H_INCLUDED
#define AUTONOMOUSFUNCTIONS_H_INCLUDED

#include "Bulldog_Core_Includes.h"
#include "Modules\Core\collisionVector2f.c"

/***************************************************************************/
/*                                                                         */
/* Macros - Easy control of motors                                         */
/*                                                                         */
/***************************************************************************/
//DRIVE
#define setAllLeftDriveMotors(power) setMotorSpeed(leftDriveBottomFront, power); setMotorSpeed(leftDriveBottomBack, power); setMotorSpeed(leftDrivePerma, power); setMotorSpeed(leftDriveTopBack, power)
#define setAllRightDriveMotors(power) setMotorSpeed(rightDriveBottomFront, power); setMotorSpeed(rightDriveBottomBack, power); setMotorSpeed(rightDrivePerma, power); setMotorSpeed(rightDriveTopBack, power)

#define setPermaLeftDriveMotors(power) setMotorSpeed(leftDrivePerma, power)
#define setPermaRightDriveMotors(power) setMotorSpeed(rightDrivePerma, power)

#define setAllPermaDriveMotors(power) setMotorSpeed(leftDrivePerma, power); setMotorSpeed(rightDrivePerma, power)
#define setAllDriveMotors(power) setMotorSpeed(leftDriveBottomFront, power); setMotorSpeed(leftDriveBottomBack, power); setMotorSpeed(leftDrivePerma, power); setMotorSpeed(leftDriveTopBack, power); setMotorSpeed(rightDriveBottomFront, power); setMotorSpeed(rightDriveBottomBack, power); setMotorSpeed(rightDrivePerma, power); setMotorSpeed(rightDriveTopBack, power)
#define setAllLauncherMotors(power) setMotorSpeed(leftDriveBottomFront, power); setMotorSpeed(leftDriveBottomBack, power); setMotorSpeed(leftDriveTopBack, power); setMotorSpeed(rightDriveBottomFront, power); setMotorSpeed(rightDriveBottomBack, power); setMotorSpeed(rightDriveTopBack, power)
#define setAllLauncherMotors_Bypass(power) setMotorSpeed_Bypass(leftDriveBottomFront, power); setMotorSpeed_Bypass(leftDriveBottomBack, power); setMotorSpeed_Bypass(leftDriveTopBack, power); setMotorSpeed_Bypass(rightDriveBottomFront, power); setMotorSpeed_Bypass(rightDriveBottomBack, power); setMotorSpeed_Bypass(rightDriveTopBack, power)

#define setAllPermaDriveMotorsSlewRate(rate) setMotorSlew(leftDrivePerma, rate); setMotorSlew(rightDrivePerma, rate)
#define setAllLauncherMotorsSlewRate(rate) setMotorSlew(leftDriveBottomFront, rate); setMotorSlew(leftDriveBottomBack, rate); setMotorSlew(leftDriveTopBack, rate); setMotorSlew(rightDriveBottomFront, rate); setMotorSlew(rightDriveBottomBack, rate); setMotorSlew(rightDriveTopBack, rate)
#define setAllDriveMotorsSlewRate(rate) setMotorSlew(leftDriveBottomFront, rate); setMotorSlew(leftDriveBottomBack, rate); setMotorSlew(leftDrivePerma, rate); setMotorSlew(leftDriveTopBack, rate); setMotorSlew(rightDriveBottomFront, rate); setMotorSlew(rightDriveBottomBack, rate); setMotorSlew(rightDrivePerma, rate); setMotorSlew(rightDriveTopBack, rate)

//INTAKE
#define setOutsideIntakeMotors(power) setMotorSpeed(intakeFront, power)
#define setInsideIntakeMotors(power) setMotorSpeed(intakeBack, power)

#define setAllIntakeMotors(power) setMotorSpeed(intakeFront, power); setMotorSpeed(intakeBack, power)

//RAW DRIVE
#define setPermaLeftDriveMotorsRaw(power) motor[leftDrivePerma] = power
#define setPermaRightDriveMotorsRaw(power) motor[rightDrivePerma] = power
#define setLeftDriveMotorsRaw(power) motor[leftDriveBottomFront] = power; motor[leftDriveBottomBack] = power; motor[leftDrivePerma] = power; motor[leftDriveTopBack] = power
#define setRightDriveMotorsRaw(power) motor[rightDriveBottomFront] = power; motor[rightDriveBottomBack] = power; motor[rightDrivePerma] = power; motor[rightDriveTopBack] = power
#define setAllPermaDriveMotorRaw(power) motor[leftDrivePerma] = power; motor[rightDrivePerma] = power
#define setAllDriveMotorsRaw(power) motor[leftDriveBottomFront] = power; motor[leftDriveBottomBack] = power; motor[leftDrivePerma] = power; motor[leftDriveTopBack] = power; motor[rightDriveBottomFront] = power; motor[rightDriveBottomBack] = power; motor[rightDrivePerma] = power; motor[rightDriveTopBack] = power

//RAW LAUNCHER
#define setAllLauncherMotorsRaw(power) motor[leftDriveBottomFront] = power; motor[leftDriveBottomBack] = power; motor[leftDriveTopBack] = power; motor[rightDriveBottomFront] = power; motor[rightDriveBottomBack] = power; motor[rightDriveTopBack] = power

//RAW INTAKE
#define setOutisdeIntakeMotorsRaw(power) motor[intakeFront] = power
#define setInsideIntakeMotorsRaw(power) motor[intakeBack] = power
#define setAllIntakeMotorsRaw(power) motor[intakeFront] = power; motor[intakeBack] = power

//Deprecated
#define setIntakeMotors(power) setMotorSpeed(intakeFront, power); setMotorSpeed(intakeBack, power)
#define setIntakeMotorsRaw(power) motor[intakeFront] = power; motor[intakeBack] = power

//Sensor redo
#define _sensorResetTypeTo(sensor, type) SensorType[sensor] = sensorNone; SensorType[sensor] = type

//Autonomous helper
#define _autonCE(func) if (func == 1) { return; }

/***************************************************************************/
/*                                                                         */
/* Function type ID's                                                      */
/*                                                                         */
/***************************************************************************/
#define F_TYPE_NONE  0000
#define F_TYPE_DRIVE 0011
#define F_TYPE_TURN  1100

//Autonomous program counter
static int auton_pc = 0;

//Whether or not a collision has happened
static bool collisionHappened = false;

//Autonomous function completion metric as specified:
	//driveTime returns the amount of time left to drive
	//driveQuad returns the amount of ticks left to drive
	//driveIME returns the amount of ticks left to drive
	//turnTime retuns the amount of time left to turn
	//turnQuad returns the amount of ticks left to turn
	//turnIME returns the amount of ticks left to turn
	//turnGyro returns the amount of degrees left to turn
static int f_distanceLeft = 0;

//Autonomous function type ID
static int f_type = F_TYPE_NONE;

/***************************************************************************/
/*                                                                         */
/* Subroutine - Initializes and clears sensors                             */
/*                                                                         */
/***************************************************************************/
void initializeSensors()
{
	clearDebugStream();

	_sensorResetTypeTo(leftDriveQuad, sensorQuadEncoder);
	SensorValue[leftDriveQuad] = 0;
	_sensorResetTypeTo(rightDriveQuad, sensorQuadEncoder);
	SensorValue[rightDriveQuad] = 0;

	//writeDebugStreamLine("calibrating gyro");
	SensorType[gyro] = sensorNone;
	wait1Msec(500);
	SensorType[gyro] = sensorGyro;
	wait1Msec(1100);
	//writeDebugStreamLine("done calibrating gyro");
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Uses the LCD to select an autonomous                       */
/*                                                                         */
/***************************************************************************/
int selectAutonomous()
{
	string currentAuton, specifier;

	int autonColor = 1, autonTile = 1, autonLevel = 1;
	string autonColorString, autonTileString, autonLevelString;

	sprintf(specifier, "Clr, Tl, Lvl");
	sprintf(autonColorString, "Red");
	sprintf(autonTileString, "Left");
	sprintf(autonLevelString, "Pri");

	timer t;
	timer_Initialize(&t);

	while (true)
	{
		//Left button changes auton color
		if (nLCDButtons & kButtonLeft)
		{
			autonColor = autonColor == 1 ? 2 : 1;
			autonColorString = autonColor == 1 ? "Red" : "Blue";
			waitForLCDRelease();
		}

		//Center button changes auton tile or exits
		if (nLCDButtons & kButtonCenter)
		{
			autonTile = autonTile == 1 ? 2 : 1;
			autonTileString = autonTile == 1 ? "Left" : "Right";
			waitForLCDRelease();
		}

		//Right button changes auton level
		if (nLCDButtons & kButtonRight)
		{
			//Exit when holding right button
			timer_PlaceHardMarker(&t);
			while (nLCDButtons & kButtonRight)
			{
				if (timer_GetDTFromHardMarker(&t) >= 250)
				{
					return (autonColor * 100) + (autonTile * 10) + autonLevel;
				}

				wait1Msec(5);
			}
			timer_ClearHardMarker(&t);

			autonLevel = autonLevel + 1 > 3 ? 1 : autonLevel + 1;

			if (autonLevel == 1)
			{
				autonLevelString = "Pri";
			}
			else if (autonLevel == 2)
			{
				autonLevelString = "Sec";
			}
			else
			{
				autonLevelString = "Ter";
			}

			waitForLCDRelease();
		}

		sprintf(currentAuton, "%s,%s,%s", autonColorString, autonTileString, autonLevelString);

		displayLCDCenteredString(0, currentAuton);
		displayLCDCenteredString(1, specifier);

		wait1Msec(25);
	}
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Shifts gear in the transmission                            */
/*                                                                         */
/***************************************************************************/
void shiftGear(int gear = -1010)
{
	switch (gear)
	{
		case 0:
			if (SensorValue[shifter] == 0)
				break;

			SensorValue[shifter] = 0;
			wait1Msec(300);
			setAllLauncherMotorsRaw(60);
			wait1Msec(100);
			setAllLauncherMotorsRaw(-60);
			wait1Msec(100);
			setAllLauncherMotorsRaw(0);
			break;

		case 1:
			if (SensorValue[shifter] == 1)
				break;

			SensorValue[shifter] = 1;
			wait1Msec(300);
			setAllPermaDriveMotors(60);
			wait1Msec(100);
			setAllPermaDriveMotors(-60);
			wait1Msec(100);
			setAllPermaDriveMotors(0);
			break;

		default:
			SensorValue[shifter] = SensorValue[shifter] == 1 ? 0 : 1;

			switch (SensorValue[shifter])
			{
				case 0:
					SensorValue[shifter] = 0;
					wait1Msec(300);
					setAllLauncherMotorsRaw(60);
					wait1Msec(100);
					setAllLauncherMotorsRaw(-60);
					wait1Msec(100);
					setAllLauncherMotorsRaw(0);
					break;

				case 1:
					SensorValue[shifter] = 1;
					wait1Msec(300);
					setAllPermaDriveMotors(60);
					wait1Msec(100);
					setAllPermaDriveMotors(-60);
					wait1Msec(100);
					setAllPermaDriveMotors(0);
					break;
				}

			break;
	}
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives for time in milliseconds                            */
/*                                                                         */
/***************************************************************************/
byte driveTime(const int leftPower, const int rightPower, const int timeMs)
{
	//Shift into drive gear
	shiftGear(0);

	int startingTime = time1[T1];             //Record function start

	setLeftDriveMotorsRaw(leftPower);         //Set left side to its power
	setRightDriveMotorsRaw(rightPower);       //Set right side to its power

	while (startingTime + timeMs > time1[T1]) //Wait for timeMs
	{
		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = time1[T1] - (startingTime + timeMs);
			f_type = F_TYPE_DRIVE;
			return 1;
		}
	}

	setAllDriveMotorsRaw(0);                  //Stop

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives for time in milliseconds while intaking             */
/*                                                                         */
/***************************************************************************/
byte driveAndIntakeTime(const int leftPower, const int rightPower, const int timeMs)
{
	//Shift into drive gear
	shiftGear(0);

	int startingTime = time1[T1];             //Record function start

	setLeftDriveMotorsRaw(leftPower);         //Set left side to its power
	setRightDriveMotorsRaw(rightPower);       //Set right side to its power

	while (startingTime + timeMs > time1[T1]) //Wait for timeMs
	{
		//Run intake in
		setAllIntakeMotorsRaw(127);

		//If limit switch is hit, balls are too far
		//Stop inside intake
		if (SensorValue[intakeLimit] == 1)
		{
			setInsideIntakeMotorsRaw(0);
		}

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = time1[T1] - (startingTime + timeMs);
			f_type = F_TYPE_DRIVE;
			return 1;
		}
	}

	setAllDriveMotorsRaw(0);                  //Stop
	setAllIntakeMotorsRaw(0);                 //Stop intake

	return 0;
}

#ifdef USING_QUADS

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives for distance in units (default: inches)             */
/*                                                                         */
/***************************************************************************/
byte driveQuad(const int power, const int ticks)
{
	//Shift into drive gear
	shiftGear(0);

	//Clear encoders
	SensorValue[leftDriveQuad] = 0;
	SensorValue[rightDriveQuad] = 0;

	//Difference between sides
	int rDiff;

	//10% of power in the direction of rDiff
	int rMod;

	//Thresold for collision recognition
	const int collisionThreshold = 20;

	//Full power for 90% of ticks
	while (abs(SensorValue[leftDriveQuad]) < abs(ticks) * 0.9)
	{
		//Difference between left and right sides
		rDiff = abs(SensorValue[leftDriveQuad]) - abs(SensorValue[rightDriveQuad]);

		//10% of power in the direction of rDiff, determined by which side is lagging
		rMod = sgn(rDiff) * power * 0.1;

		//Directly contorl left side and have right side follow
		setLeftDriveMotorsRaw(power);
		setRightDriveMotorsRaw(power + rMod);

		////Exit if hit a wall
		//if (abs(SensorValue[accelX]) > collisionThreshold)
		//{
		//	setAllDriveMotorsRaw(0);
		//	return 1;
		//}

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = ticks - SensorValue[leftDriveQuad];
			f_type = F_TYPE_DRIVE;
			return 1;
		}

		wait1Msec(1);
	}

	//1/3 power for last 10% of ticks
	while (abs(SensorValue[leftDriveQuad]) < abs(ticks) - 10)
	{
		//Difference between sides
		rDiff = abs(SensorValue[leftDriveQuad]) - abs(SensorValue[rightDriveQuad]);

		//10% of power in the direction of rDiff, determined by which side is lagging
		rMod = sgn(rDiff) * power * 0.1;

		//Directly control left side and have right side follow
		setLeftDriveMotorsRaw(power / 3);
		setRightDriveMotorsRaw((power / 3) + rMod);

		////Exit if hit a wall
		//if (SensorValue[accelX] > collisionThreshold)
		//{
		//	setAllDriveMotorsRaw(0);
		//	return 1;
		//}

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = ticks - SensorValue[leftDriveQuad];
			f_type = F_TYPE_DRIVE;
			return 1;
		}

		wait1Msec(1);
	}

	driveTime(-1 * (power / 2), -1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);                              //Stop

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives for a distance to align with a line                 */
/*                                                                         */
/***************************************************************************/
byte alignWithLine(const int power, const int alignPower, const int lineCutoff = 500)
{
	//Shift into drive gear
	shiftGear(0);

	bool keepRunning = true; //Keep driving to align the robot

	//Clear encoders
	SensorValue[leftDriveQuad] = 0;
	SensorValue[rightDriveQuad] = 0;

	//Difference between sides
	int rDiff;

	//10% of power in the direction of rDiff
	int rMod;

	//Timer for function timeout
	timer timeoutTimer;
	int leftLast = 0, rightLast = 0;

	//Initialize function timeout timer
	timer_Initialize(&timeoutTimer);

	//Drive forward until line found
	while (SensorValue[leftLineSensor] > lineCutoff && SensorValue[rightLineSensor] > lineCutoff)
	{
		//Difference between left and right sides
		rDiff = abs(SensorValue[leftDriveQuad]) - abs(SensorValue[rightDriveQuad]);

		//10% of power in the direction of rDiff, determined by which side is lagging
		rMod = sgn(rDiff) * power * 0.1;

		//Directly contorl left side and have right side follow
		setLeftDriveMotorsRaw(power);
		setRightDriveMotorsRaw(power + rMod);

		//If quad encoders have not moved
		if (SensorValue[leftDriveQuad] == leftLast || SensorValue[rightDriveQuad] == rightLast)
		{
			//Place marker
			timer_PlaceHardMarker(&timeoutTimer);

			//If timeout has been running for 2 seconds
			if (timer_GetDTFromHardMarker(&timeoutTimer) >= 2000)
			{
				//Exit from function
				setAllDriveMotorsRaw(0);
				f_distanceLeft = 0;
				f_type = F_TYPE_DRIVE;
				return 1;
			}
		}

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = 0;
			f_type = F_TYPE_DRIVE;
			return 1;
		}
	}

	//Drive back a bit to align slowly
	setAllDriveMotorsRaw(-alignPower);
	wait1Msec(200);
	setAllDriveMotorsRaw(0);

	//Move sides to align with line
	while (keepRunning)
	{
		//Run left side if it isn't on the line yet
		if (SensorValue[leftLineSensor] > lineCutoff)
		{
			setLeftDriveMotorsRaw(alignPower);
		}
		else
		{
			setLeftDriveMotorsRaw(0);
		}

		//Run right side if it isn't on the line yet
		if (SensorValue[rightLineSensor] > lineCutoff)
		{
			setRightDriveMotorsRaw(alignPower);
		}
		else
		{
			setRightDriveMotorsRaw(0);
		}

		//Exit if both sides are on lines
		if (SensorValue[leftLineSensor] > lineCutoff && SensorValue[rightLineSensor] > lineCutoff)
		{
			setAllDriveMotorsRaw(0);
			keepRunning = false;
		}
	}

	return 0;
}

#endif //USING_QUADS

#ifdef USING_IMES

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives for distance in units (default: inches)             */
/*                                                                         */
/***************************************************************************/
byte driveIME(const int power, const int ticks)
{
	//Shift into drive gear
	shift(0);

	nMotorEncoder[leftDriveFront] = 0;                          //Clear left IME
	nMotorEncoder[rightDriveFront] = 0;                         //Clear right IME

	int rDiff;                                                  //Difference between sides
	int rMod;                                                   //10% of power in the direction of rDiff

	//Full power for 60% of ticks
	while (abs(nMotorEncoder[leftDriveFront]) < abs(ticks) * 0.6)
	{
		rDiff = abs(nMotorEncoder[leftDriveFront]) - abs(nMotorEncoder[rightDriveFront]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                     //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power);                                                        //Directly control left side
		setRightDriveMotorsRaw(power + rMod);                                                //Have right side adjust to keep in tune with left side

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = ticks - SensorValue[leftDriveQuad];
			f_type = F_TYPE_DRIVE;
			return 1;
		}
	}

	//1/3 power for last 40% of ticks
	while (abs(nMotorEncoder[leftDriveFront]) < abs(ticks))
	{
		rDiff = abs(nMotorEncoder[leftDriveFront]) - abs(nMotorEncoder[rightDriveFront]);    //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                     //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power / 3);                                                    //Directly control left side
		setRightDriveMotorsRaw((power / 3) + rMod);                                          //Have right side adjust to keep in tune with left side

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = ticks - SensorValue[leftDriveQuad];
			f_type = F_TYPE_DRIVE;
			return 1;
		}
	}

	driveTime(-1 * (power / 2), -1 * (power / 2), 50);    //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);                              //Stop

	return 0;
}

#endif //USING_IMES

/***************************************************************************/
/*                                                                         */
/* Subroutine - Turns for time in milliseconds                             */
/*                                                                         */
/***************************************************************************/
byte turnTime(const int power, const int timeMs)
{
	int startingTime = time1[T1];

	setLeftDriveMotorsRaw(power);             //Set left side to its power
	setRightDriveMotorsRaw(-1 * power);       //Set right side to its power

	while (startingTime + timeMs > time1[T1]) //Wait for timeMs
	{
		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = time1[T1] - (startingTime + timeMs);
			f_type = F_TYPE_TURN;
			return 1;
		}
	}
	setAllDriveMotorsRaw(0);                  //Stop

	return 0;
}

#ifdef USING_QUADS

/***************************************************************************/
/*                                                                         */
/* Subroutine - Turns for distance in units (default: inches)              */
/*                                                                         */
/***************************************************************************/
byte turnQuad(const int power, const int ticks)
{
	//Shift into drive gear
	shiftGear(0);

	SensorValue[leftDriveQuad] = 0;  //Clear left encoder
	SensorValue[rightDriveQuad] = 0; //Clear right encoder

	int rDiff;                       //Difference between sides
	int rMod;                        //10% of power in the direction of rDiff

	//Full power for 60% of ticks
	while (abs(SensorValue[leftDriveQuad]) < abs(ticks) * 0.6)
	{
		rDiff = abs(SensorValue[leftDriveQuad]) - abs(SensorValue[rightDriveQuad]); //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                            //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power);                                               //Directly control left side
		setRightDriveMotorsRaw((-1 * power) - rMod);                                //Have right side adjust to keep in tune with left side

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = ticks - SensorValue[leftDriveQuad];
			f_type = F_TYPE_TURN;
			return 1;
		}
	}

	//1/3 power for last 40% of ticks
	while (abs(SensorValue[leftDriveQuad]) < abs(ticks))
	{
		rDiff = abs(SensorValue[leftDriveQuad]) - abs(SensorValue[rightDriveQuad]); //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                            //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power / 3);                                           //Directly control left side
		setRightDriveMotorsRaw((-1 * (power * 0.8)) - rMod);                        //Have right side adjust to keep in tune with left side

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = ticks - SensorValue[leftDriveQuad];
			f_type = F_TYPE_TURN;
			return 1;
		}
	}

	turnTime(-1 * (power / 2), 50);  //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);         //Stop

	return 0;
}

#endif //USING_QUADS

#ifdef USING_IMES

/***************************************************************************/
/*                                                                         */
/* Subroutine - Turns for distance in units (default: inches)              */
/*                                                                         */
/***************************************************************************/
byte turnIME(const int power, const int ticks)
{
	//Shift into drive gear
	shift(0);

	nMotorEncoder[leftDriveFront] = 0;  //Clear left IME
	nMotorEncoder[rightDriveFront] = 0; //Clear right IME

	int rDiff;                          //Difference between sides
	int rMod;                           //10% of power in the direction of rDiff

	//Full power for 60% of ticks
	while (abs(nMotorEncoder[leftDriveFront]) < abs(ticks) * 0.6)
	{
		rDiff = abs(nMotorEncoder[leftDriveFront]) - abs(nMotorEncoder[rightDriveFront]); //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                  //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power);                                                     //Directly control left side
		setRightDriveMotorsRaw((-1 * power) - rMod);                                      //Have right side adjust to keep in tune with left side

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = ticks - SensorValue[leftDriveQuad];
			f_type = F_TYPE_TURN;
			return 1;
		}
	}

	//1/3 power for last 40% of ticks
	while (abs(nMotorEncoder[leftDriveFront]) < abs(ticks))
	{
		rDiff = abs(nMotorEncoder[leftDriveFront]) - abs(nMotorEncoder[rightDriveFront]); //Difference between sides
		rMod = sgn(rDiff) * power * 0.1;                                                  //10% of power in the direction of rDiff
		setLeftDriveMotorsRaw(power / 3);                                                 //Directly control left side
		setRightDriveMotorsRaw((-1 * (power * 0.8)) - rMod);                              //Have right side adjust to keep in tune with left side

		//Exit if collision has happened
		if (collisionHappened)
		{
			setAllDriveMotorsRaw(0);
			f_distanceLeft = ticks - SensorValue[leftDriveQuad];
			f_type = F_TYPE_TURN;
			return 1;
		}
	}

	turnTime(-1 * (power / 2), 50);     //Brake at -50% power for a short time to eliminate momentum
	setAllDriveMotorsRaw(0);            //Stop

	return 0;
}

#endif //USING_IMES

#ifdef USING_GYRO

/***************************************************************************/
/*                                                                         */
/* Subroutine - Turns for distance in degrees                              */
/*                                                                         */
/***************************************************************************/
byte turnGyro(const float deg)
{
	//Shift into drive gear
	shiftGear(0);

	//Clear the gyro
	SensorValue[gyro] = 0;

	//Scale degrees down to gyro ticks
	int ticks = (int)(deg * 10);

	//Loop timeout
	const int timeout = 1000;

	//Turn direction
	const int dir = sign(deg);

	//Timer for timeout and stabalize time
	timer t;
	timer_Initialize(&t);

	//Position PID controller for turning
	pos_PID pid;
	pos_PID_InitController(&pid, gyro, 0.5, 0, 0.04);

	//Set controller's target position
	pos_PID_SetTargetPosition(&pid, ticks);

	//Marker for timeout
	timer_PlaceMarker(&t);

	//writeDebugStreamLine("Error, Output");

	//Turn to target
	pos_PID_StepController(&pid);
	while (abs(pos_PID_GetError(&pid)) > 0)
	{
		//Step controller
		pos_PID_StepController(&pid);

		//Set drive to controller's output
		if (dir == -1)
		{
			//Turn right
			setLeftDriveMotorsRaw(-1 * pos_PID_GetOutput(&pid));
			setRightDriveMotorsRaw(pos_PID_GetOutput(&pid));
		}
		else
		{
			//Turn left
			setLeftDriveMotorsRaw(-1 * pos_PID_GetOutput(&pid));
			setRightDriveMotorsRaw(pos_PID_GetOutput(&pid));
		}

		writeDebugStreamLine("%d, %d, %d", dir, pos_PID_GetError(&pid), pos_PID_GetOutput(&pid));

		//Exit if taking too long
		if (timer_GetDTFromMarker(&t) > timeout)
		{
			setAllDriveMotorsRaw(0);
			return 1;
		}

		//Exit if output is too small to turn the robot
		if (dir == -1)
		{
			if (pos_PID_GetOutput(&pid) >= -5)
			{
				setAllDriveMotorsRaw(0);
				return 1;
			}
		}
		else
		{
			if (pos_PID_GetOutput(&pid) <= 5)
			{
				setAllDriveMotorsRaw(0);
				return 1;
			}
		}

		wait1Msec(10);
	}

	//Let controller stabalize for 500ms
	timer_PlaceMarker(&t);

	//Run for 500ms
	while (timer_GetDTFromMarker(&t) < 500)
	{
		//Step controller
		pos_PID_StepController(&pid);

		//Set drive to controller's output
		if (dir == -1)
		{
			//Turn right
			setLeftDriveMotorsRaw(pos_PID_GetOutput(&pid));
			setRightDriveMotorsRaw(-1 * pos_PID_GetOutput(&pid));
		}
		else
		{
			//Turn left
			setLeftDriveMotorsRaw(-1 * pos_PID_GetOutput(&pid));
			setRightDriveMotorsRaw(pos_PID_GetOutput(&pid));
		}

		//writeDebugStreamLine("%d, %d", pos_PID_GetError(&pid), pos_PID_GetOutput(&pid));
	}

	//Stop drive motors
	setAllDriveMotorsRaw(0);

	return 0;
}

#endif //USING_GYRO

int auton_maintainLauncher_target = 90;
task maintainLauncherForAuton()
{
	//Shift into launcher gear
	shiftGear(1);

	startTask(motorSlewRateTask);

	int launcherCurrentPower = 0, auton_maintainLauncher_target_last = 0;

	while (true)
	{
		//Set the TBH controller's target velocity to the new target velocity
		//if the target velocity has changed
		if (auton_maintainLauncher_target != auton_maintainLauncher_target_last)
		{
			vel_TBH_SetTargetVelocity(&launcherTBH, auton_maintainLauncher_target);
		}

		//Remember the current target rpm
		auton_maintainLauncher_target_last = auton_maintainLauncher_target;

		//Step the TBH controller and get the output
		if (vel_TBH_GetVelocity(&launcherTBH) <= auton_maintainLauncher_target - 10)
		{
			vel_TBH_StepVelocity(&launcherTBH);
			launcherCurrentPower = 127;
		}
		else
		{
			launcherCurrentPower = vel_TBH_StepController(&launcherTBH);
		}

		//Bound the TBH controller's output to [0, inf) so the launcher's motors always run in the correct direction
		launcherCurrentPower = launcherCurrentPower < 0 ? 0 : launcherCurrentPower;

		//Set motors to low slew rate to minimize torque on launcher
		setAllLauncherMotorsSlewRate(0.8);
		setAllLauncherMotors(-launcherCurrentPower);

		wait1Msec(25);
	}
}

void launchFourBalls(int target)
{
	int ballCount = 0, intakeLimit_last = 0;

	auton_maintainLauncher_target = target;
	startTask(maintainLauncherForAuton);

	//Wait for initial boost to finish
	wait1Msec(3500);

	//Run until 4 balls have been launched
	while (ballCount < 4)
	{
		//If launcher velocity is in acceptable bounds
		if (vel_TBH_GetError(&launcherTBH) <= 1 && vel_TBH_GetError(&launcherTBH) >= -2)
		{
			//Run intake to launch a ball
			setIntakeMotorsRaw(127);

			//If the intake limit switch is no longer hit, a ball has been fired
			if (SensorValue[intakeLimit] == 0 && intakeLimit_last == 1)
			{
				ballCount++;
			}

			//Remember current intake limit switch position
			intakeLimit_last = SensorValue[intakeLimit];
		}
		else
		{
			setIntakeMotorsRaw(0);
		}

		wait1Msec(25);
	}

	setIntakeMotorsRaw(0);
	stopTask(maintainLauncherForAuton);
}

bool forceTrig; //Simulate a collision
collisionVector2f collVec; //Collision vector
/***************************************************************************/
/*                                                                         */
/* Subroutine - Corrects for a collision                                   */
/*              See notebook for math and diagrams behind this code        */
/*                                                                         */
/***************************************************************************/
void correctForCollision()
{
	if (f_type == F_TYPE_DRIVE)
	{
		//Travel from current position to the position at the end of the autonomous function that got interrupted

		if (f_distanceLeft > 0)
		{
			//Turn to face P_g, theta = -atan2(dx, z - dy) - dG
			turnGyro(-10 * radiansToDegrees(atan2(collVec.x, f_distanceLeft - collVec.y)) - (collVec.gyroEnd - collVec.gyroStart));

			//Drive to P_g, d = sqrt(dx^2 + dy^2)
			driveQuad(100, sqrt(pow(collVec.x, 2) + pow(f_distanceLeft - collVec.y, 2)));

			//Turn back to starting angle
			turnGyro(collVec.gyroStart);
		}
		else if (f_distanceLeft < 0)
		{
			if (collVec.x > 0)
			{
				//Turn to face P_g, theta = PI - atan2(dx, z - dy) - dG
				turnGyro(10 * (180 - radiansToDegrees(atan2(collVec.x, f_distanceLeft - collVec.y))) - (collVec.gyroEnd - collVec.gyroStart));

				//Drive to P_g, d = sqrt(dx^2 + dy^2)
				driveQuad(100, sqrt(pow(collVec.x, 2) + pow(f_distanceLeft - collVec.y, 2)));

				//Turn back to starting angle
				turnGyro(collVec.gyroStart);
			}
			else if (collVec.x < 0)
			{
				//Turn to face P_g, theta = -(PI + atan2(dx, z - dy)) - dG
				turnGyro(-10 * (180 + radiansToDegrees(atan2(collVec.x, f_distanceLeft - collVec.y))) - (collVec.gyroEnd - collVec.gyroStart));

				//Drive to P_g, d = sqrt(dx^2 + dy^2)
				driveQuad(100, sqrt(pow(collVec.x, 2) + pow(f_distanceLeft - collVec.y, 2)));

				//Turn back to starting angle
				turnGyro(collVec.gyroStart);
			}
		}
	}
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Monitors for a collision                                   */
/*              See notebook for math and diagrams behind this code        */
/*                                                                         */
/***************************************************************************/
task monitorForCollision()
{
	//Threshold for what is recognized as a collision
	const int collisionThreshold = 20;

	//Axes x and y are sampled at 200 Hz for 2 seconds in the event of a collision
	//200 Hz * 2 seconds = 400 samples
	//Caches for x and y are written to before a collision for data completeness
	byte cacheX;
	byte dataX[400];
	float velX = 0;
	byte cacheY;
	byte dataY[400];
	float velY = 0;

	//Gyro values pre- and post-collision
	int gyroStart, gyroEnd;

	//Current index in the accelerometer data arrays
	int dataIndex = 0;

	//Time at start of collision
	long startTime;

	while (true)
	{
		writeDebugStreamLine("S %d, %d", SensorValue[accelX], SensorValue[accelY]);

		//Record gyro value pre-collision
		gyroStart = SensorValue[gyro];

		//if (abs(cacheX = SensorValue[accelX]) > collisionThreshold || abs(cacheY = SensorValue[accelY]) > collisionThreshold)
		//if (abs(cacheX = SensorValue[accelX]) == 0 || abs(cacheY = SensorValue[accelY]) == 0)
		if (forceTrig)
		{
			//Let autonomous functions know about the collision
			collisionHappened = true;

			//Record collision time
			startTime = time1[T4];

			//Start sampling
			while (time1[T4] < startTime + 2000)
			{
				//Record x and y samples
				dataX[dataIndex] = SensorValue[accelX];
				dataY[dataIndex] = SensorValue[accelY];
				writeDebugStreamLine("D %d, %d, %d", dataX[dataIndex], dataY[dataIndex], dataIndex);

				//Index safety
				dataIndex += dataIndex < 399 ? 1 : 0;

				//Sample at 200 Hz (hopefully)
				wait1Msec(5);
			}

			//Record gyro value post-collision
			gyroEnd = SensorValue[gyro];

			//Collision over
			collisionHappened = false;

			//Calculate displacement
			for (int i = 0; i < 400; i++)
			{
				velX += dataX[i] * 5;
				velY += dataY[i] * 5;
				collVec.x += velX * 5;
				collVec.y += velY * 5;
			}

			//Scale values back to regular size
			velX /= 1000;
			velY /= 1000;
			collVec.x /= 1000;
			collVec.y /= 1000;

			//Record gyro information
			collVec.gyroStart = gyroStart;
			collVec.gyroEnd = gyroEnd;

			//Correct for displacement from collision
			correctForCollision();

			//Restart autonomous at next step
			startAutonomous();
		}

		//Check for collision at 50 Hz
		wait1Msec(20);
	}
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives in a direction (x drive only)                       */
/* (Experimental: see notebook and x drive proofs)                         */
/*                                                                         */
/***************************************************************************/
//void driveIndependent(int degrees, int ticks)
//{
//		const float radius = 127;
//		float a, b, theta, vectorX = ticks * cosDegrees(degrees), vectorY = ticks * sinDegrees(degrees);

//		if (degrees > 0 && degrees < 90)
//		{
//			//
//		}
//		else if (degrees == 90)
//		{
//			//
//		}
//		else if (degrees > 90 && degrees < 180)
//		{
//			while (SensorValue[rightDriveQuad] < vectorX || SensorValue[rightDriveQuad] < vectorY)
//			{
//				//Convert degrees to polar coordinates
//				theta = atan2(radius * sinDegrees(theta), radius * cosDegrees(theta)) * (180.0 / PI);

//				//Calculate opposite-side speeds
//				a = (cosDegrees(theta + 90.0) + sinDegrees(theta + 90.0)) * radius;
//				//Optimized a = radius * ROOT_2 * sinDegrees(theta + (PI / 4) + 90);
//				b = (cosDegrees(theta) + sinDegrees(theta)) * radius;

//				motor[frontLeft] = a;
//				motor[backLeft] = b;
//				motor[frontRight] = b;
//				motor[backRight] = a;
//			}
//		}
//		else if (degrees == 180)
//		{
//			//
//		}
//		else if (degrees > 180 && degrees < 270)
//		{
//			//
//		}
//		else if (degrees == 270)
//		{
//			//
//		}
//		else if (degrees > 270 && degrees < 360)
//		{
//			//
//		}
//		else if (degrees == 360)
//		{
//			//
//		}
//}

#endif

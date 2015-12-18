#ifndef AUTONOMOUSFUNCTIONS_H_INCLUDED
#define AUTONOMOUSFUNCTIONS_H_INCLUDED

#include "StatusCodes.c"
#include "MotorControl.c"
#include "PIDControl.c"

//PID Controllers for drive movement
pidController *leftController;
pidController *rightController;

/***************************************************************************/
/*                                                                         */
/* Subroutine - initializes everything needed for autonomous               */
/*                                                                         */
/***************************************************************************/
int initializeAuto()
{
	//Drivetrain motors
	addMotor(leftFront);
	addMotor(rightFront);
	addMotor(rightBack);
	addMotor(leftBack);

	//PID Controllers for drive movement
	leftController = newPIDController(leftQuad, addMotor(leftFront), 0.0, 0.0, 0.0);
	rightController = newPIDController(rightQuad, addMotor(rightFront), 0.0, 0.0, 0.0);

	#ifdef DEBUG_FINE_AUTO
		writeDebugStreamLine("initializeAuto");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - initializes the gyro                                       */
/*                                                                         */
/***************************************************************************/
int initializeGyro()
{
	SensorType[gyro] = sensorNone;
	wait1Msec(1000);
	SensorType[gyro] = sensorGyro;
	wait1Msec(2000);

	#ifdef DEBUG_FINE_AUTO
		writeDebugStreamLine("initializeGyro");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - drives forward                                             */
/*                                                                         */
/***************************************************************************/
int driveForward(const int distance, const int speed = 127)
{
	const int totalTicks = _InchesToTicks(distance, 3.25);

	SensorValue[leftQuad] = 0;
	SensorValue[rightQuad] = 0;

	_SetTargetPosition(leftController, totalTicks);
	_SetTargetPosition(rightController, totalTicks);

	while (SensorValue[leftQuad] != totalTicks)
	{
		updatePIDController(leftController);
		updatePIDController(rightController);
		_SetMotorSpeed(leftBack, _GetMotorSpeed(leftFront));
		_SetMotorSpeed(rightBack, _GetMotorSpeed(rightFront));
	}

	_ClearPIDControllers();

	#ifdef DEBUG_FINE_AUTO
		writeDebugStreamLine("driveForward");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - drives backward                                            */
/*                                                                         */
/***************************************************************************/
int driveBackward(const int distance, const int speed = 127)
{
	const int totalTicks = _InchesToTicks(distance, 3.25);

	#ifdef DEBUG_FINE_AUTO
		writeDebugStreamLine("driveBackward");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - does a left point turn                                     */
/*                                                                         */
/***************************************************************************/
int turnLeftPoint(const int deg = 90)
{
	SensorValue[gyro] = 0;
	const int totalCounts = deg * 10;

	switch (deg)
	{
		case 45:
			break;

		case 90:
			int countsLeft = totalCounts - SensorValue[gyro];
			int calculatedSpeed = (int) ((countsLeft / totalCounts) * 127.0);
			while (countsLeft > 0)
			{
				calculatedSpeed = (int) ((countsLeft / totalCounts) * 127.0);
				_SetMotorSpeed(leftFront, calculatedSpeed);
				_SetMotorSpeed(rightFront, calculatedSpeed);
				_SetMotorSpeed(leftBack, calculatedSpeed);
				_SetMotorSpeed(rightBack, calculatedSpeed);
			}
			_SetMotorSpeed(leftFront, 0);
			_SetMotorSpeed(rightFront, 0);
			_SetMotorSpeed(leftBack, 0);
			_SetMotorSpeed(rightBack, 0);
			break;

		case 135:
			break;

		case 180:
			break;

		default:
			break;
	}

	#ifdef DEBUG_FINE_AUTO
		writeDebugStreamLine("turnLeftPoint");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - does a right point turn                                    */
/*                                                                         */
/***************************************************************************/
int turnRightPoint(const int deg = 90)
{
	SensorValue[gyro] = 0;
	const int totalCounts = deg * 10;

	switch (deg)
	{
		case 45:
			break;

		case 90:
			break;

		case 135:
			break;

		case 180:
			break;

		default:
			break;
	}

	#ifdef DEBUG_FINE_AUTO
		writeDebugStreamLine("turnRightPoint");
	#endif

	return EXIT_SUCCESS;
}

#endif

#ifndef DrivetrainControl
#define DrivetrainControl

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
/* Motor definitions                                                       */
/*                                                                         */
/***************************************************************************/
#define MOTOR_NUM			        	kNumbOfTotalMotors
#define MOTOR_MIN_VALUE			    127
#define MOTOR_MAX_VALUE			    (-127)
#define MOTOR_DEFAULT_SLEW_RATE 10
#define MOTOR_FAST_SLEW_RATE	  256
#define MOTOR_TASK_DELAY		    15
#define MOTOR_DEADBAND		     	10

/***************************************************************************/
/*                                                                         */
/* Motor control with slew rate definitions                                */
/*                                                                         */
/***************************************************************************/
#define _SetLeftFrontMotor(speed)    motorReq[leftFront] = speed
#define _SetRightFrontMotor(speed)   motorReq[rightFront] = speed
#define _SetLeftBackMotor(speed)     motorReq[leftBack] = speed
#define _SetRightBackMotor(speed)    motorReq[rightBack] = speed
#define _SetLeftDrive(speed, speed)  _SetLeftFrontMotor(speed); _SetLeftBackMotor(speed)
#define _SetRightDrive(speed, speed) _SetRightFrontMotor(speed); _SetRightBackMotor(speed)
#define _SetDrive(speed)             _SetLeftDrive(speed, speed); _SetRightDrive(speed, speed)

/***************************************************************************/
/*                                                                         */
/* Motor control without slew rate definitions                             */
/*                                                                         */
/***************************************************************************/
#define _SetLeftFrontMotorRaw(speed)    motor[leftFront] = speed
#define _SetRightFrontMotorRaw(speed)   motor[rightFront] = speed
#define _SetLeftBackMotorRaw(speed)     motor[leftBack] = speed
#define _SetRightBackMotorRaw(speed)    motor[rightBack] = speed
#define _SetLeftDriveRaw(speed, speed)  _SetLeftFrontMotorRaw(speed); _SetLeftBackMotorRaw(speed)
#define _SetRightDriveRaw(speed, speed) _SetRightFrontMotorRaw(speed); _SetRightBackMotorRaw(speed)
#define _SetDriveRaw(speed)             _SetLeftDriveRaw(speed, speed); _SetRightDriveRaw(speed, speed)

/***************************************************************************/
/*                                                                         */
/* Motor control arrays                                                    */
/*                                                                         */
/***************************************************************************/
//Array for requested motor speeds
int motorReq[MOTOR_NUM];

//Array to hold slew rate for motors
int motorSlew[MOTOR_NUM];

/***************************************************************************/
/*                                                                         */
/* Task - Updates the speed of each motor to best meet the requested speed */
/*                                                                         */
/***************************************************************************/
deprecated task DrivetrainSlewRateTask()
{
	//Index of current motor
	unsigned int motorIndex;
	//Updated speed of current motor
	int motorTmpSpd;
	//Requested speed of current motor
	int motorTmpReq;

	//Initialize all motor speeds to 0
	//Initialize all motor slew rates to the default slew rate
	for (motorIndex = 0; motorIndex < MOTOR_NUM; motorIndex++)
	{
		motorReq[motorIndex] = 0;
		motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
	}

	while (true)
	{
		for (motorIndex = 0; motorIndex < MOTOR_NUM; motorIndex++)
		{
			//Keep internal memory access to a minimum
			motorTmpSpd = motor[motorIndex];
			motorTmpReq = motorReq[motorIndex];

			//If the motor value needs to change
			if (motorTmpSpd != motorTmpReq)
			{
				//Increase motor value
				if (motorTmpReq > motorTmpSpd)
				{
					motorTmpSpd += motorSlew[motorIndex];

					//Limit speed
					if (motorTmpSpd > motorTmpReq)
					{
						motorTmpSpd = motorTmpReq;
					}
				}

				//Decrease motor value
				if (motorTmpReq < motorTmpSpd)
				{
					motorTmpSpd -= motorSlew[motorIndex];

					//Limit speed
					if (motorTmpSpd < motorTmpReq)
					{
						motorTmpSpd = motorTmpReq;
					}
				}

				//Send updated speed to motor
				motor[motorIndex] = motorTmpSpd;
			}
		}

		wait1Msec(MOTOR_TASK_DELAY);
	}
}

/***************************************************************************/
/*                                                                         */
/* Task - Gives drivetrain control to the driver                           */
/*                                                                         */
/***************************************************************************/
deprecated task DriverControlTask()
{
	while (true)
	{
		_SetLeftDrive(vexRT[JOY_DRIVE_LV], vexRT[JOY_DRIVE_LV]);
		_SetRightDrive(vexRT[JOY_DRIVE_RV], vexRT[JOY_DRIVE_RV]);

		//Don't hog CPU
		EndTimeSlice();
	}
}

#endif

#ifndef DRIVERCONTROL_H_INCLUDED
#define DRIVERCONTROL_H_INCLUDED

#include "MotorControl.c"
#include "PIDControl.c"

/***************************************************************************/
/*                                                                         */
/* Joystick definitions                                                    */
/*                                                                         */
/***************************************************************************/
#define JOY_DRIVE_LV  vexJSLeftV
#define JOY_DRIVE_LH  vexJSLeftH
#define JOY_DRIVE_RV  vexJSRightV
#define JOY_DRIVE_RH  vexJSRightH
#define JOY_THRESHOLD 5

/***************************************************************************/
/*                                                                         */
/* Task - Gives drivetrain control to the driver                           */
/*                                                                         */
/***************************************************************************/
task DrivetrainControlTask()
{
	//Drivetrain motors
	addMotor(leftFront);
	addMotor(rightFront);
	addMotor(rightBack);
	addMotor(leftBack);

	int leftV, speedLV;
	int leftH, speedLH;
	int rightV, speedRV;
	int rightH, speedRH;

	//16129 == (127 * 127)
	//This is used to scale the cubed value back down to a motor power
	while (true)
	{
		#ifdef DRIVE_TANK
				leftV = vexRT[JOY_DRIVE_LV];
				rightV = vexRT[JOY_DRIVE_RV];

				_SetMotorSpeed(leftFront, leftV);
				_SetMotorSpeed(leftBack, leftV);
				_SetMotorSpeed(rightFront, rightV);
				_SetMotorSpeed(rightBack, rightV);
		#endif
		#ifdef DRIVE_TANK_CUBIC
				leftV = vexRT[JOY_DRIVE_LV];
				rightV = vexRT[JOY_DRIVE_RV];

				speedLV = _Cube(leftV) / 16129;
				speedRV = _Cube(rightV) / 16129;

				_SetMotorSpeed(leftFront, speedLV);
				_SetMotorSpeed(leftBack, speedLV);
				_SetMotorSpeed(rightFront, speedRV);
				_SetMotorSpeed(rightBack, speedRV);
		#endif
		#ifdef DRIVE_H
				//
		#endif
		#ifdef DRIVE_X
				leftV = vexRT[JOY_DRIVE_LV];
				leftH = vexRT[JOY_DRIVE_LH];
				rightH = vexRT[JOY_DRIVE_RH];

				_SetMotorSpeed(leftFront, leftV - leftH - rightH);
				_SetMotorSpeed(leftBack, leftV + leftH - rightH);
				_SetMotorSpeed(rightFront, -leftV - leftH - rightH);
				_SetMotorSpeed(rightBack, -leftV + leftH - rightH);
		#endif
		#ifdef DRIVE_X_CUBIC
				leftV = vexRT[JOY_DRIVE_LV];
				leftH = vexRT[JOY_DRIVE_LH];
				rightH = vexRT[JOY_DRIVE_RH];

				speedLV = _Cube(leftV) / 16129;
				speedLH = _Cube(leftH) / 16129;
				speedRH = _Cube(rightH) / 16129;

				_SetMotorSpeed(leftFront, speedLV - speedLH - speedRH);
				_SetMotorSpeed(leftBack, speedLV + speedLH - speedRH);
				_SetMotorSpeed(rightFront, -speedLV - speedLH - speedRH);
				_SetMotorSpeed(rightBack, -speedLV + speedLH - speedRH);
		#endif
		#ifdef DRIVE_MECANUM
				leftV = vexRT[JOY_DRIVE_LV];
				leftH = vexRT[JOY_DRIVE_LH];
				rightH = vexRT[JOY_DRIVE_RH];

				_SetMotorSpeed(leftFront, leftV + rightH + leftH);
				_SetMotorSpeed(leftBack, leftV + rightH - leftH);
				_SetMotorSpeed(rightFront, leftV - rightH - leftH);
				_SetMotorSpeed(rightBack, leftV - rightH + leftH);
		#endif
		#ifdef DRIVE_MECANUM_CUBIC
				leftV = vexRT[JOY_DRIVE_LV];
				leftH = vexRT[JOY_DRIVE_LH];
				rightH = vexRT[JOY_DRIVE_RH];

				speedLV = _Cube(leftV) / 16129;
				speedLH = _Cube(leftH) / 16129;
				speedRH = _Cube(rightH) / 16129;

				_SetMotorSpeed(leftFront, speedLV + speedRH + speedLH);
				_SetMotorSpeed(leftBack, speedLV + speedRH - speedLH);
				_SetMotorSpeed(rightFront, speedLV - speedRH - speedLH);
				_SetMotorSpeed(rightBack, speedLV - speedRH + speedLH);
		#endif

		//Don't hog CPU
		EndTimeSlice();
	}
}

/***************************************************************************/
/*                                                                         */
/* Task - Gives lift control to the driver                                 */
/*                                                                         */
/***************************************************************************/
task LiftControlTask()
{
	//Lift motors
	pidController *liftController = newPIDController(liftQuad, addMotor(leftLift), 0.0, 0.0, 0.0);

	_SetTargetPosition(liftController, 360);

	while (true)
	{
		//Keep the lift controller updated
		updatePIDController(liftController);

		//Tie the right lift motor speed to the left lift motor speed to avoid drifting
		_SetMotorSpeed(rightLift, _GetMotorSpeed(leftLift));

		//Go to one rotation
		if (vexRT[Btn8U])
		{
			_SetTargetPosition(liftController, 360);
		}
		//Go to zero rotations
		else if (vexRT[Btn8D])
		{
			_SetTargetPosition(liftController, 0);
		}
	}
}

#endif

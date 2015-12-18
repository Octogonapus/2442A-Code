#ifndef DRIVERCONTROL_H_INCLUDED
#define DRIVERCONTROL_H_INCLUDED

#include "Bulldog_Competition_Includes.c"

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

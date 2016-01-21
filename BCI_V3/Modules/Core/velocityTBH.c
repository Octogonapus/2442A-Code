#ifndef VELOCITYTBH_C_INCLUDED
#define VELOCITYTBH_C_INCLUDED

#include "VelocityTBH.h"

void vel_TBH_InitController(vel_TBH* tbh, tSensors sensor, float gain, int outValApprox)
{
	tbh->gain = gain;

	tbh->currentVelocity = 0.0;
	tbh->prevPosition = 0;
	tbh->error = 0;
	tbh->prevError = 0;
	tbh->firstCross = true;
	tbh->outValApprox = outValApprox;
	tbh->outValAtZero = 0.0;

	tbh->dt = 0.0;
	tbh->prevTime = 0;

	tbh->sensor = sensor;
	tbh->imeMotor = 1010;
	tbh->currentPosition = 0;
	tbh->targetVelocity = 0.0;

	tbh->outVal = 0.0;
}

void vel_TBH_InitController(vel_TBH* tbh, const tMotor imeMotor, const float gain, const int outValApprox)
{
	tbh->gain = gain;

	tbh->currentVelocity = 0.0;
	tbh->prevPosition = 0;
	tbh->error = 0;
	tbh->prevError = 0;
	tbh->firstCross = true;
	tbh->outValApprox = outValApprox;
	tbh->outValAtZero = 0.0;

	tbh->dt = 0.0;
	tbh->prevTime = 0;

	tbh->sensor = 1010;
	tbh->imeMotor = imeMotor;
	tbh->currentPosition = 0;
	tbh->targetVelocity = 0.0;

	tbh->outVal = 0.0;
}

void vel_TBH_SetTargetVelocity(vel_TBH *tbh, int targetVelocity, int outValApprox)
{
	tbh->targetVelocity = targetVelocity;
	tbh->firstCross = true;

	//Set outValApprox if it is not the default value
	if (outValApprox != -1010)
	{
		tbh->outValApprox = outValApprox;
	}
}

int vel_TBH_StepController_VEL(vel_TBH* tbh)
{
	//Calculate timestep
	tbh->dt = (time1[T1] - tbh->prevTime) + 1;
	tbh->prevTime = time1[T1];

	//Calculate current velocity
	if (tbh->imeMotor == 1010)
	{
		tbh->currentVelocity = (SensorValue[tbh->sensor] - tbh->prevPosition) * (TBH_DEGPMS_TO_RPM / (tbh->dt * 1000));
		tbh->prevPosition = SensorValue[tbh->sensor];
	}
	else
	{
		tbh->currentVelocity = getMotorVelocity(tbh->imeMotor);
	}

	//Calculate error
	tbh->error = tbh->targetVelocity - tbh->currentVelocity;

	//Calculate new outVal
	tbh->outVal = tbh->outVal + (tbh->error * tbh->gain);

	//Check for zero crossing on error term
	if (sgn(tbh->error) != sgn(tbh->prevError))
	{
		//If first zero crossing since new target velocity
		if (tbh->firstCross)
		{
			//Set drive to an open loop approximation
			tbh->outVal = tbh->outValApprox;
			tbh->firstCross = false;
		}
		else
		{
			tbh->outVal = 0.5 * (tbh->outVal + tbh->outValAtZero);
		}

		//Save this outVal as the new zero base value
		tbh->outValAtZero = tbh->outVal;
	}

	//Save error
	tbh->prevError = tbh->error;

	return tbh->outVal;
}

#endif

#pragma config(Sensor, dgtl1,  leftQuad,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightQuad,      sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  leftLiftQuad,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  rightLiftQuad,  sensorQuadEncoder)
#pragma config(Motor,  port2,           rightFront,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftFront,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftTopLift,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftBottomLift, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightBottomLift, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightTopLift,  tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#define DRIVE_X
#define LIFT_4_2
#define LIFT_UP Btn5U
#define LIFT_DOWN Btn5D
#define LIFT_SPEED 127
#include "Bulldog_Competition_Includes.c"

#include "AutonomousFunctions.c"
//#include "Perceptron.c"

#include "Autonomous.c"

/***************************************************************************/
/*                                                                         */
/* Variables                                                               */
/*                                                                         */
/***************************************************************************/
bool bEndPreAuton = false;

/***************************************************************************/
/*                                                                         */
/* Subroutine - Pre Autonomous                                             */
/*                                                                         */
/***************************************************************************/
void pre_auton()
{
	if (!bResetFromWatchdogTimeout)
	{
		bStopTasksBetweenModes = true;

		initializeDrivetrain(leftFront, leftBack, rightFront, rightBack, leftQuad, rightQuad);
		setTranslationPIDControllers(leftQuad, rightQuad, 0.3, 0.0, 0.5);
		setRotationPIDControllers(leftQuad, rightQuad, 0.4, 0.2, 0.0);
		initializeLift(leftTopLift, leftBottomLift, rightTopLift, rightBottomLift, leftLiftQuad, rightLiftQuad, 1.0, 2.0, 1.0, 500.0, 500.0);

		initializeSensors();	//This takes ~3 seconds

		//Level 1
		menu *options = newMenu("Options");
		menu *startDriverControl = newMenu("Start DC", 2);
		pairMenus(options, startDriverControl);

		//Level 2
		menu *auton1menu = newMenu("Run Auton 1", 0);
		menu *driveForwardMenu = newMenu("Drive forward", 1);
		menu *turn90ticksMenu = newMenu("Turn 90t", 3);
		menu *strafeRightMenu = newMenu("Strafe right", 4);
		pairMenus(auton1menu, driveForwardMenu, turn90ticksMenu, strafeRightMenu);

		makeLevel(auton1menu, driveForwardMenu, turn90ticksMenu, strafeRightMenu, options);

		bLCDBacklight = true;
		startLCDControl();

		while (!bEndPreAuton) { wait1Msec(25); }
	}
}

/***************************************************************************/
/*                                                                         */
/* Task - Autonomous                                                       */
/*                                                                         */
/***************************************************************************/
task autonomous()
{
	auton1();
}

/***************************************************************************/
/*                                                                         */
/* Task - User Control                                                     */
/*                                                                         */
/***************************************************************************/
task usercontrol()
{
	startLiftControl();

	int leftV, leftH;
	int rightH;
	bool flipForwardVector;

	while (true)
	{
		leftV = vexRT[JOY_DRIVE_LV];
		leftH = vexRT[JOY_DRIVE_LH];
		rightH = vexRT[JOY_DRIVE_RH];
		flipForwardVector = (bool) vexRT[Btn8R];

		leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
		leftH = abs(leftH) < JOY_THRESHOLD ? 0 : leftH;
		rightH = abs(rightH) < JOY_THRESHOLD ? 0 : rightH;

		if (flipForwardVector)
		{
			_SetMotorSpeed(driveTrain.frontLeft, -leftV + leftH + rightH);
			_SetMotorSpeed(driveTrain.backLeft, -leftV - leftH + rightH);
			_SetMotorSpeed(driveTrain.frontRight, -leftV - leftH - rightH);
			_SetMotorSpeed(driveTrain.backRight, -leftV + leftH - rightH);
		}
		else
		{
			_SetMotorSpeed(driveTrain.frontLeft, leftV + leftH + rightH);
			_SetMotorSpeed(driveTrain.backLeft, leftV - leftH + rightH);
			_SetMotorSpeed(driveTrain.frontRight, leftV - leftH - rightH);
			_SetMotorSpeed(driveTrain.backRight, leftV + leftH - rightH);
		}

		wait1Msec(25);
	}

	//startLiftPositionUpdater();
	//setLiftTargetPosition(90);
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Invoke                                                     */
/*                                                                         */
/***************************************************************************/
void invoke(int func)
{
	switch (func)
	{
		//Run autonomous 1
		case 0:
			auton1();
			break;

		//Drive forward 360 ticks
		case 1:
			drive(360);
			break;

		//End pre autonomous
		case 2:
			bEndPreAuton = true;
			stopLCDControl();
			break;

		//Turn 90 ticks
		case 3:
			turnPID(90);
			break;

		//Strafe right 360 ticks
		case 4:
			strafe(180);
			break;

		default:
			break;
	}
}

void doPerceptron()
{
	//int x1[] = {0, 0};
	//int x2[] = {0, 1};
	//int x3[] = {1, 0};
	//int x4[] = {1, 1};

	//int hiddenx1[2];
	//int hiddenx2[2];
	//int hiddenx3[2];
	//int hiddenx4[2];

	//perceptron_t orP, andP, xorP;

	//initializePerceptron(&orP);
	//initializePerceptron(&andP);
	//initializePerceptron(&xorP);

	//for (int i = 0; i < 1000; i++)
	//{
	//	train(&orP, x1, 0);
	//	train(&orP, x2, 1);
	//	train(&orP, x3, 1);
	//	train(&orP, x4, 1);

	//	train(&andP, x1, 0);
	//	train(&andP, x2, 0);
	//	train(&andP, x3, 0);
	//	train(&andP, x4, 1);

	//	train(&xorP, x1, 0);
	//	train(&xorP, x3, 1);
	//	train(&xorP, x4, 0);
	//}

	//hiddenx1[0] = classify(&orP, x1);
	//hiddenx1[1] = classify(&andP, x1);

	//hiddenx2[0] = classify(&orP, x2);
	//hiddenx2[1] = classify(&andP, x2);

	//hiddenx3[0] = classify(&orP, x3);
	//hiddenx3[1] = classify(&andP, x3);

	//hiddenx4[0] = classify(&orP, x4);
	//hiddenx4[1] = classify(&andP, x4);

	//writeDebugStreamLine("orP, x1: %d", classify(&orP, x1));
	//writeDebugStreamLine("orP, x2: %d", classify(&orP, x2));
	//writeDebugStreamLine("orP, x3: %d", classify(&orP, x3));
	//writeDebugStreamLine("orP, x4: %d", classify(&orP, x4));

	//writeDebugStreamLine("\nandP, x1: %d", classify(&andP, x1));
	//writeDebugStreamLine("andP, x2: %d", classify(&andP, x2));
	//writeDebugStreamLine("andP, x3: %d", classify(&andP, x3));
	//writeDebugStreamLine("andP, x4: %d", classify(&andP, x4));

	//writeDebugStreamLine("\nxorP, x1: %d", classify(&xorP, hiddenx1));
	//writeDebugStreamLine("xorP, x2: %d", classify(&xorP, hiddenx2));
	//writeDebugStreamLine("xorP, x3: %d", classify(&xorP, hiddenx3));
	//writeDebugStreamLine("xorP, x4: %d", classify(&xorP, hiddenx4));
}

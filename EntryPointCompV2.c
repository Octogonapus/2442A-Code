#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    powerExpander,  sensorAnalog)
#pragma config(Sensor, in2,    gyro,           sensorGyro)
#pragma config(Sensor, in3,    accelX,         sensorAccelerometer)
#pragma config(Sensor, in4,    accelY,         sensorAccelerometer)
#pragma config(Sensor, in5,    leftLineSensor, sensorLineFollower)
#pragma config(Sensor, in6,    rightLineSensor, sensorLineFollower)
#pragma config(Sensor, dgtl1,  launcherQuad,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  brake,          sensorDigitalOut)
#pragma config(Sensor, dgtl4,  shifter,        sensorDigitalOut)
#pragma config(Sensor, dgtl5,  leftDriveQuad,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  rightDriveQuad, sensorQuadEncoder)
#pragma config(Sensor, dgtl9, intakeLimit,    sensorTouch)
#pragma config(Sensor, dgtl10, intakeLED,      sensorDigitalOut)
#pragma config(Sensor, I2C_1,  leftBankIME,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightBankIME,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           intakeFront,   tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           leftDriveBottomFront, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftDriveBottomBack, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           leftDriveTopFront, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           leftDriveTopBack, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightDriveBottomFront, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           rightDriveBottomBack, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port8,           rightDriveTopFront, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightDriveTopBack, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          intakeBack,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#pragma DebuggerWindows("Motors")
#pragma DebuggerWindows("Sensors")

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"

//Setup LCD
#define LCD_SAFETY_REQ_COMP_SWITCH
#define MENU_NUM 23
#define USING_QUADS
#define USING_GYRO

//Auton function prototypes
void startAutonomous();

//Whether or not to end pre auton
bool endPreAuton = false;

//The autonomous program to run
int autonSelection = -1;

#include "Bulldog_Core_Includes.h"

//Launcher velocity controller
vel_TBH launcherTBH;

//Autonomous program file includes
#include "autonIncludes.h"

//Programming skills routine
#include "programmingSkills.c"

//Menus
//Level 1 - General Info
menu *autonomousSelectionMenu;
menu *endPreAutonMenu;
menu *batteryVoltageMenu;
menu *powerExpanderVoltageMenu;
menu *backupBatteryVoltageMenu;

void pre_auton()
{
	bStopTasksBetweenModes = true;

	//Initialize launcher TBH controller
	vel_TBH_InitController(&launcherTBH, leftDriveBottomBack, 0.0085, 75);

	//Iniialize all sensors
	initializeSensors();

	//Hand motors to slew rate controller
	addMotor(intakeFront, MOTOR_FAST_SLEW_RATE);
	addMotor(leftDriveBottomFront, MOTOR_FAST_SLEW_RATE);
	addMotor(leftDriveBottomBack, MOTOR_FAST_SLEW_RATE);
	addMotor(leftDriveTopFront, MOTOR_FAST_SLEW_RATE);
	addMotor(leftDriveTopBack, MOTOR_FAST_SLEW_RATE);
	addMotor(rightDriveBottomFront, MOTOR_FAST_SLEW_RATE);
	addMotor(rightDriveBottomBack, MOTOR_FAST_SLEW_RATE);
	addMotor(rightDriveTopFront, MOTOR_FAST_SLEW_RATE);
	addMotor(rightDriveTopBack, MOTOR_FAST_SLEW_RATE);
	addMotor(intakeBack, MOTOR_FAST_SLEW_RATE);

	//Menu system
	//Level 1 - General Info
	autonomousSelectionMenu = newMenu("Select Auton", 2);
	endPreAutonMenu = newMenu("Confirm", 1);

	string batteryVoltage;
	sprintf(batteryVoltage, "Main: %1.2f%c", nAvgBatteryLevel / 1000.0, 'V');
	batteryVoltageMenu = newMenu(batteryVoltage);

	string powerExpanderVoltage;
	sprintf(powerExpanderVoltage, "Expander: %1.2f%c", SensorValue[powerExpander] / ANALOG_IN_TO_V, 'V');
	powerExpanderVoltageMenu = newMenu(powerExpanderVoltage);

	string backupBatteryVoltage;
	sprintf(backupBatteryVoltage, "Backup: %1.2f%c", BackupBatteryLevel / 1000.0, 'V');
	backupBatteryVoltageMenu = newMenu(backupBatteryVoltage);

	linkMenus(autonomousSelectionMenu, endPreAutonMenu, batteryVoltageMenu, powerExpanderVoltageMenu, backupBatteryVoltageMenu);

	bLCDBacklight = true;
	startTask(updateLCDTask);
	while (!getLCDSafetyState() && !endPreAuton) { wait1Msec(50); }

}

task autonomous()
{
	//autonSelection = 111;
	startAutonomous();
}

task usercontrol()
{
	//startTask(autonomous);
	//wait1Msec(15000);
	//stopTask(autonomous);

	//Drivetrain variables
	int leftV, rightV;
	const int drivetrainSlewRate = 5;

	//Intake variables
	const int intakeTimeoutMs = 2000, intakeMinimumError = 2;
	bool intake_prevStateIn = false, intakePrevState = false, intakeUseTimeout = true;

	//Launcher variables
	bool launcherOn = false, stepController = true;
	int launcherTargetRPM = 90, launcherTargetRPM_last = 0;
	int launcherPOWER = 52, launcherCurrentPower = 0, launcherRPMIncrement = 1;

	startTask(motorSlewRateTask);

	bLCDBacklight = true;

	string line1String, line2String;

	timer launcherTimer, intakeTimer, intakeTimerTimer, t;
	timer_Initialize(&launcherTimer);
	timer_Initialize(&intakeTimer);
	timer_Initialize(&intakeTimerTimer);

	//timer_Initialize(&t);
	//while (timer_GetDTFromStart(t) <= 8000)
	while(true)
	{
		writeDebugStreamLine("%d,%d,%d,%d,%d", launcherTargetRPM, launcherTBH.currentVelocity, getMotorVelocity(leftDriveBottomBack), launcherCurrentPower, launcherTBH.error);

		//sprintf(line1String, "CV:%1.2f, T:%d", launcherTBH.currentVelocity, launcherTBH.targetVelocity);
		//sprintf(line1String, "L: %d, R: %d", getMotorVelocity(leftDriveBottomBack), getMotorVelocity(rightDriveBottomBack));
		sprintf(line1String, "RPM: %d", launcherTBH.currentVelocity);
		displayLCDCenteredString(0, line1String);

		//sprintf(line2String, "%1.2f", SensorValue[powerExpander] / ANALOG_IN_TO_MV);
		//sprintf(line2String, "CP:%d", launcherCurrentPower);
		//sprintf(line2String, "LH: %d, RH: %d", getMotorVelocity(leftDriveBottomBack) * 25, getMotorVelocity(rightDriveBottomBack) * 25);
		sprintf(line2String, "T:%d,C:%d,A:%d", launcherTargetRPM, launcherCurrentPower, launcherTBH.outValApprox);
		displayLCDCenteredString(1, line2String);

		/* ------------ DRIVETRAIN ------------ */

		//If the launcher is not on
		if (!launcherOn)
		{
			//Change drive motors' slew rate back to normal after launcher control
			setAllDriveMotorsSlewRate(drivetrainSlewRate);

			//Grab values from joystick
			leftV = vexRT[JOY_JOY_LV];
			rightV = vexRT[JOY_JOY_RV];

			//Bound joystick values
			leftV = abs(leftV) < JOY_THRESHOLD ? 0 : leftV;
			rightV = abs(rightV) < JOY_THRESHOLD ? 0 : rightV;

			//Send these values to the drivetrain
			setLeftDriveMotors(leftV);
			setRightDriveMotors(rightV);
		}

		/* -------------- INTAKE -------------- */

		//Outside intake should turn inwards
		if (vexRT[JOY_TRIG_LU] == 1 || vexRT[JOY_TRIG_LD] == 1)
		{
			setOutsideIntakeMotors(127);
		}
		//Outside intake should turn outwards
		else if (vexRT[JOY_BTN_LU])
		{
			setOutsideIntakeMotors(-127);
		}
		//Intake should not turn
		else
		{
			setOutsideIntakeMotors(0);
		}

		//Inside intake should turn inwards
		if (vexRT[JOY_TRIG_LD])
		{
			//If launcher is running
			if (launcherOn)
			{
				//If ball is ready
				if (SensorValue[intakeLimit] == 1)
				{
					//Place timeout mark
					timer_PlaceHardMarker(&intakeTimer);

					//If velocity controller has low error
					if (vel_TBH_GetError(&launcherTBH) <= intakeMinimumError)
					{
						//After exiting this block, the intake will have been running inwards so set the flag
						intake_prevStateIn = true;
						setInsideIntakeMotors(127);
					}
					//If velocity controller does not have low error but intake timeout has expired
					else if (intakeUseTimeout && timer_GetDTFromMarker(&intakeTimer) >= intakeTimeoutMs)
					{
						//After exiting this block, the intake will have been running inwards so set the flag
						intake_prevStateIn = true;
						setInsideIntakeMotors(127);

						//Do not use the timeout after this
						intakeUseTimeout = false;

						//Light timeout LED
						SensorValue[intakeLED] = LED_ON;
					}
				}
			}
			//If launcher is not running
			else
			{
				//After exiting this block, the intake will have been running inwards so set the flag
				intake_prevStateIn = true;
				setInsideIntakeMotors(127);
			}
		}
		//Inside intake should turn outwards
		else if (vexRT[JOY_BTN_LD])
		{
			setInsideIntakeMotors(-127);
			timer_ClearHardMarker(&intakeTimer);
		}
		//Inside intake should not run
		else
		{
			//If the intake was previously turning intwards, stop it from drifting
			if (intake_prevStateIn)
			{
				//Send a backwards jolt to the intake
				setInsideIntakeMotors(-127);
				wait1Msec(40);
				setInsideIntakeMotors(127);
				wait1Msec(10);

				//Stop the intake
				setInsideIntakeMotors(0);

				//After exiting this block, the intake will not have been running
				intake_prevStateIn = false;
			}
			//If the intake was not previously turning inwards
			else
			{
				//Stop the intake
				setInsideIntakeMotors(0);
			}

			timer_ClearHardMarker(&intakeTimer);
		}

		/* ------------- LAUNCHER ------------- */

		//Launcher on flag
		if (vexRT[JOY_TRIG_RD])
		{
			launcherOn = !launcherOn;

			//Wait for the button to be released before continuing
			waitForZero(vexRT[JOY_TRIG_RD]);
		}

		//Velocity controller math flag
		if (vexRT[JOY_TRIG_RU])
		{
			stepController = !stepController;

			//Wait for the button to be released before continuing
			waitForZero(vexRT[JOY_TRIG_RU]);
		}

		//If the launcher should run
		if (launcherOn)
		{
			//If the velocity controller should step its calculations
			if (stepController)
			{
				//Set the TBH controller's target velocity to the new target velocity
				//if the target velocity has changed
				if (launcherTargetRPM != launcherTargetRPM_last)
				{
					vel_TBH_SetTargetVelocity(&launcherTBH, launcherTargetRPM);
				}

				//Remember the current target rpm
				launcherTargetRPM_last = launcherTargetRPM;

				//Rev the launcher to 127 while far under target
				if (launcherTBH.currentVelocity <= launcherTargetRPM - 20)
				{
					vel_TBH_StepVelocity(&launcherTBH);
					launcherCurrentPower = 127;
				}
				//Use a velocity controller when close to target
				else
				{
					//Step the TBH controller and get the output
					launcherCurrentPower = vel_TBH_StepController(&launcherTBH);

					//Bound the output to [0, inf) to prevent the launcher from running backwards
					launcherCurrentPower = launcherCurrentPower < 0 ? 0 : launcherCurrentPower;
				}

				//Rev the launcher right before firing a ball
				if (SensorValue[intakeLimit] == 1)
				{
					//Set intakePrevState to true for the first time a ball is ready
					//in order to control the rev timer correctly
					if (!intakePrevState)
					{
						intakePrevState = true;
						timer_PlaceMarker(&launcherTimer);
					}
				}

				//Rev launcher
				if (timer_GetDTFromMarker(&launcherTimer) <= 285)
				{
					launcherCurrentPower = 127;
				}
				else if (SensorValue[intakeLimit] == 0)
				{
					intakePrevState = false;
				}
			}

			//Set motors to low slew rate to minimize torque on launcher
			setAllDriveMotorsSlewRate(1);
			setAllDriveMotors(-launcherCurrentPower);
		}
		//If the launcher should not run
		else
		{
			//Step velocity calculation
			vel_TBH_StepVelocity(&launcherTBH);
		}

		//Launcher speed targets
		//Full field shot
		if (vexRT[JOY_BTN_RL])
		{
			launcherTargetRPM = 90;
			vel_TBH_SetTargetVelocity(&launcherTBH, launcherTargetRPM, 77);

			launcherPOWER = 90;

			//Wait for the button to be released before continuing
			waitForZero(vexRT[JOY_BTN_RL]);
		}

		//Half field shot
		if (vexRT[JOY_BTN_RR])
		{
			launcherTargetRPM = 80;
			vel_TBH_SetTargetVelocity(&launcherTBH, launcherTargetRPM, 67);

			launcherPOWER = 70;

			//Wait for the button to be released before continuing
			waitForZero(vexRT[JOY_BTN_RR]);
		}

		//Increment target velocity
		if (vexRT[JOY_BTN_RU])
		{
			launcherTargetRPM += launcherRPMIncrement;
			vel_TBH_SetTargetVelocity(&launcherTBH, launcherTargetRPM, launcherTBH.outValApprox + 1);

			launcherPOWER++;

			//Wait for the button to be released before continuing
			waitForZero(vexRT[JOY_BTN_RU]);
		}

		//Decrement target velocity
		if (vexRT[JOY_BTN_RD])
		{
			launcherTargetRPM -= launcherRPMIncrement;
			vel_TBH_SetTargetVelocity(&launcherTBH, launcherTargetRPM, launcherTBH.outValApprox - 1);

			launcherPOWER--;

			//Wait for the button to be released before continuing
			waitForZero(vexRT[JOY_BTN_RD]);
		}

		/* ------------- SHIFTER ------------- */

		//Invert the shifter's state
		if (vexRT[JOY_BTN_LR])
		{
			//Do not allow a shift while the launcher is running
			//The robot risks signifigant damage
			if (launcherOn)
			{
				launcherOn = false;

				//Semi e-stop motors
				setAllDriveMotorsRaw(0);
			}

			//Shift gear
			shiftGear();

			//Wait for the button to be released before continuing
			waitForZero(vexRT[JOY_BTN_LR]);
		}

		/* ------------- PARKING BRAKE ------------- */

		//Invert the brake's state
		if (vexRT[JOY_BTN_LL])
		{
			SensorValue[brake] = SensorValue[brake] == 1 ? 0 : 1;

			//Wait for the button to be released before continuing
			waitForZero(vexRT[JOY_BTN_LL]);
		}

		//Task sleep
		wait1Msec(25);
	}
}

//Run an autonomous function based on current selection
void startAutonomous()
{
	//Naming convention: <red side = 1, blue side = 2><left side = 1, right side = 2><primary = 1, secondary = 2, tertiary = 3>

	switch (autonSelection)
	{
		case 111:
			redLeftAutonPrimary();
			break;

		case 112:
			redLeftAutonSecondary();
			break;

		case 113:
			redLeftAutonTertiary();
			break;

		case 121:
			redRightAutonPrimary();
			break;

		case 122:
			redRightAutonSecondary();
			break;

		case 123:
			redRightAutonTertiary();
			break;

		case 211:
			blueLeftAutonPrimary();
			break;

		case 212:
			blueLeftAutonSecondary();
			break;

		case 213:
			blueLeftAutonTertiary();
			break;

		case 221:
			blueRightAutonPrimary();
			break;

		case 222:
			blueRightAutonSecondary();
			break;

		case 223:
			blueRightAutonTertiary();
			break;

		default:
			break;
	}
}

//LCD Library callback function
void invoke(int func)
{
	if (func == 1)
	{
		endPreAuton = true;
		stopTask(updateLCDTask);
	}
	else if (func == 2)
	{
		autonSelection = selectAutonomous();
	}
}

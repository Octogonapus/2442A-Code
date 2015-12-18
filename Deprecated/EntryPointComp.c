#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  leftQuad,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightQuad,      sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  liftQuad,       sensorQuadEncoder)
#pragma config(Motor,  port2,           leftFront,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightFront,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           leftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightLift,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftBack,      tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#define DRIVE_TANK
#include "Vex_Competition_Includes.c"

#include "MotorControl.c"
#include "AutonomousFunctions.c"
#include "DriverControl.c"
#include "LCDControl.c"

#include "Autonomous1.c"

void pre_auton()
{
	bStopTasksBetweenModes = true;
	initializeGyro();	//This takes ~3 seconds

	menu *auton1menu = newMenu("Run Auton 1", 0);
	menu *driveForwardMenu = newMenu("Drive forward", 1);
	pairMenus(auton1menu, driveForwardMenu);
}

task autonomous()
{
	auton1();
}

task usercontrol()
{
	initializeAuto();

	startTask(MotorSlewRateTask);
	startTask(DrivetrainControlTask);
	//startTask(LiftControlTask);

	while (true) { EndTimeSlice(); }
}

//LCD function
void invoke(int func)
{
	switch (func)
	{
        //Run autonomous 1
        case 0:
            auton1();
            break;

        //Drive forward 12 inches
        case 1:
            //driveForward(12);
            break;

        default:
            break;
	}
}

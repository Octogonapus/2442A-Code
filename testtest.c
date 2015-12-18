#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftLauncherBottom, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftLauncherTop, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightLauncherBottom, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightLauncherTop, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightDriveFront, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightDriveBack, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftDriveBack, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftDriveFront, tmotorVex393_MC29, openLoop)

task main()
{
	while (true)
	{
		motor[rightDriveFront] = vexRT[Ch2];
		motor[rightDriveBack] = vexRT[Ch2];
		motor[leftDriveFront] = vexRT[Ch3];
		motor[leftDriveBack] = vexRT[Ch3];

		wait1Msec(25);
	}
}

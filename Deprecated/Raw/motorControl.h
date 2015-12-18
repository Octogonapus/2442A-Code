#ifndef MOTORCONTROL_H_INCLUDED
#define MOTORCONTROL_H_INCLUDED

//Motor general
#define MOTOR_NUM               kNumbOfTotalMotors
#define MOTOR_MIN_VALUE         (-127)
#define MOTOR_MAX_VALUE         127
#define MOTOR_DEFAULT_SLEW_RATE 10
#define MOTOR_FAST_SLEW_RATE    256
#define MOTOR_TASK_DELAY        15
#define MOTOR_DEADBAND          10

//Motor control
#define setMotorSpeed(index, power) driveMotors[index].reqSpeed = (power)
#define setMotorSlew(index, slew) driveMotors[index].slew = (slew)
#define getMotor(index) driveMotors[index]
#define getMotorSpeed(index) driveMotors[index].reqSpeed

//Raw motor control
#define setMotorSpeedRaw(index, power) motor[index] = (power)
#define getMotorSpeedRaw(index) motor[index]

//Motor representation
typedef struct driveMotor
{
	int reqSpeed;   //Input speed
	float artSpeed; //Artificial speed (the exact speed as governed by the slew rate)
	float slew;     //Slew rate
} driveMotor;

//Adds and initializes a motor (by name) to the motor array
driveMotor* addMotor(const tMotor name, float slewRate = MOTOR_DEFAULT_SLEW_RATE);

//Updates the power of each motor to best meet the requested power
task motorSlewRateTask();

#endif //#ifndef MOTORCONTROL_H_INCLUDED

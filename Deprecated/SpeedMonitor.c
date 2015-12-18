#ifndef SPEEDMONITOR_H_INCLUDED
#define SPEEDMONITOR_H_INCLUDED

#include "StatusCodes.c"

/***************************************************************************/
/*                                                                         */
/* Struct to represent a motor monitor                                     */
/*                                                                         */
/***************************************************************************/
typedef struct motorMonitor
{
    int power;
    float rpm;
    
    tSensors sensor;
    int oldPos;
} motorMonitor;

//Array for allocation
static motorMonitor motorMonitors[kNumbOfTotalMotors];

/***************************************************************************/
/*                                                                         */
/* Subroutine - Adds a motor (by name) to the motor array                  */
/*                                                                         */
/***************************************************************************/
motorMonitor* addMotorMonitor(tMotor name, tSensors sensor)
{
	//Allocate from array
	motorMonitor *m = &(motorMonitors[name]);
    
	m->power = motor[name];
	m->rpm = -1;
    m->sensor = sensor;
    m->oldPos = 0;
    m->newPos = SensorValue[sensor];
    
    #ifdef DEBUG_FINE_SPEEDMONITOR
        writeDebugStreamLine("addMotorMonitor");
    #endif
    
	return m;
}

/***************************************************************************/
/*                                                                         */
/* Task - Updates the speed of each motor monitor                          */
/*                                                                         */
/***************************************************************************/
task SpeedMonitorTask()
{
    //Index of current motor
	unsigned int motorIndex;
	//Current motor
	motorMonitor *currentMotorMonitor;
    //Change in encoder ticks since last check
    int delta;
    
	while (true)
	{
		for (motorIndex = 0; motorIndex < kNumbOfTotalMotors; motorIndex++)
		{
			//Keep internal memory access to a minimum
			currentMotorMonitor = &(motorMonitors[motorIndex]);
            
            //Update rpm
            delta = SensorValue[m->sensor] - m->oldPos;
            m->oldPos = SensorValue[m->sensor];
            m->rpm = (delta * (time1[T1] / 60000.0)) / 360.0;
            time1[T1] = 0;
            
            //Update power
            m->power = motor[motorIndex];
            writeDebugStreamLine("Motor %d: speed %d", motorIndex, m->rpm);
        }
        
        wait1Msec(25);
    }
}

#endif
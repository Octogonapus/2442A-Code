#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

//Enum for cortex states
typedef enum
{
	vrNoXmiters =         0,    //No transmitters connected
	vrXmit1 =             0x01, //1 == Transmitter 1 connected
	vrXmit2 =             0x02, //1 == Transmitter 2 connected
	vrBit2 =              0x04, //Unused
	vrCompetitionSwitch = 0x08, //0 == No Comp Switch, 1 == Competition Switch attached
	vrResetSlave =        0x10, //Unused
	vrGameController =    0x20, //0 == Legacy75MHz, 1 == Game Controller
	vrAutonomousMode =    0x40, //0 == Driver Control, 1 == Autonomous Mode
	vrDisabled =          0x80, //0 == Enabled, 1 == Disabled
} TVexRecieverState;

//Wait for a value to become zero
#define _WaitForZero(val) while(val != 0) { wait1Msec(5); }
//Wait for any LCD button to be pressed
#define _WaitForLCDPress() while(nLCDButtons == 0) {} wait1Msec(5)
//Wait for all LCD buttons to be released
#define _WaitForLCDRelease() while(nLCDButtons != 0) {} wait1Msec(5)

//Dumps all current motor and sensor values to the debug stream
void dumpLevels();

//Prints which transmitters are connected, if the competition switch is connected, and which mode the competition is in
void printnVexRCRecieveState();

#endif //#ifndef UTIL_H_INCLUDED

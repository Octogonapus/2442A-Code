#ifndef RECORDER_H_INCLUDED
#define RECORDER_H_INCLUDED

task recordToDebugStreamTask()
{
	unsigned byte i;
	
	clearTimer(T4);

	//Format is <(m)otor><port><value><(t)ime>

	while (true)
	{
		//Print motors
		for (i = 0; i < kNumbOfTotalMotors; i++)
		{
			writeDebugStream("m%d%03d", i + 1, motor[i]);
		}

		//Print time
		writeDebugStream("t%.4f", time1[T4]);
	}
}

#endif

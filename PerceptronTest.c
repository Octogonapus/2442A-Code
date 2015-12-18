#include "perceptron.c"

#pragma DebuggerWindows("DebugStream");

task main()
{
	int x1[] = {0, 0};
	int x2[] = {0, 1};
	int x3[] = {1, 0};
	int x4[] = {1, 1};

	int hiddenx1[2];
	int hiddenx2[2];
	int hiddenx3[2];
	int hiddenx4[2];

	perceptron_t orP, andP, xorP;

	InitializePerceptron(&orP);
	InitializePerceptron(&andP);
	InitializePerceptron(&xorP);

	for (int i = 0; i < 20; i++)
	{
		Train(&orP, x1, 0);
		Train(&orP, x2, 1);
		Train(&orP, x3, 1);
		Train(&orP, x4, 1);

		Train(&andP, x1, 0);
		Train(&andP, x2, 0);
		Train(&andP, x3, 0);
		Train(&andP, x4, 1);

		Train(&xorP, x1, 0);
		Train(&xorP, x3, 1);
		Train(&xorP, x4, 0);
	}

	hiddenx1[0] = Classify(&orP, x1);
	hiddenx1[1] = Classify(&andP, x1);

	hiddenx2[0] = Classify(&orP, x2);
	hiddenx2[1] = Classify(&andP, x2);

	hiddenx3[0] = Classify(&orP, x3);
	hiddenx3[1] = Classify(&andP, x3);

	hiddenx4[0] = Classify(&orP, x4);
	hiddenx4[1] = Classify(&andP, x4);

	writeDebugStreamLine("orP, x1: %d", Classify(&orP, x1));
	writeDebugStreamLine("orP, x2: %d", Classify(&orP, x2));
	writeDebugStreamLine("orP, x3: %d", Classify(&orP, x3));
	writeDebugStreamLine("orP, x4: %d", Classify(&orP, x4));

	writeDebugStreamLine("\nandP, x1: %d", Classify(&andP, x1));
	writeDebugStreamLine("andP, x2: %d", Classify(&andP, x2));
	writeDebugStreamLine("andP, x3: %d", Classify(&andP, x3));
	writeDebugStreamLine("andP, x4: %d", Classify(&andP, x4));

	writeDebugStreamLine("\nxorP, x1: %d", Classify(&xorP, hiddenx1));
	writeDebugStreamLine("xorP, x2: %d", Classify(&xorP, hiddenx2));
	writeDebugStreamLine("xorP, x3: %d", Classify(&xorP, hiddenx3));
	writeDebugStreamLine("xorP, x4: %d", Classify(&xorP, hiddenx4));
}

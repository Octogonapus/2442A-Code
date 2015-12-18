#include "BCI_V3\Bulldog_Core_Includes.h"
#include "Modules\Core\collisionVector2f.c"

collisionVector2f collVec; //Collision vector

byte cacheX;
byte dataX[400];
float velX = 0;
byte cacheY;
byte dataY[400];
float velY = 0;

task main()
{
	//Simulate collision data
	for (int i = 0; i < 400; i++)
	{
		dataX[i] = 10;
		dataY[i] = 10;
	}

	//Calculate displacement
	for (int i = 0; i < 400; i++)
	{
		velX += dataX[i] * 0.005;
		velY += dataY[i] * 0.005;
		collVec.x += velX * 0.005;
		collVec.y += velY * 0.005;
	}

	//Convert meters to inches
	collVec.x *= 39.3701;
	collVec.y *= 39.3701;

	//Convert inches to feet
	collVec.x /= 12;
	collVec.y /= 12;

	////Calculate displacement
	//for (int i = 0; i < 400; i++)
	//{
	//	velX += dataX[i] * 5;
	//	velY += dataY[i] * 5;
	//	collVec.x += velX * 5;
	//	collVec.y += velY * 5;
	//}

	//velX /= 1000;
	//velY /= 1000;
	//collVec.x /= 1000000;
	//collVec.y /= 1000000;

	////Convert meters to inches
	//collVec.x *= 39.3701;
	//collVec.y *= 39.3701;

	////Convert inches to feet
	//collVec.x /= 12;
	//collVec.y /= 12;

	while (true) { wait1Msec(25); }
}

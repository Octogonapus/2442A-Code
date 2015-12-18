#define MENU_NUM 1

#include "Modules\Core\lcdControl.c"

bool preAutonRun = false;

void pre_auton()
{
	//Make some menus
	menu *helloMenu = newMenu("Hello!");
}

//task main()
//{
//	startTask(usercontrol);
//}

task usercontrol()
{
	if (!preAutonRun)
	{
		pre_auton();
	}
}

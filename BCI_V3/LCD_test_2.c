#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"

#define MENU_NUM 6
#include "Modules\Core\lcdControl.c"

bool endPreAuton = false;

void pre_auton()
{
  bStopTasksBetweenModes = true;

  //Level 1
  menu *helloMenu = newMenu("Hello!");
  menu *changeGreetingMenu = newMenu("Change greeting", 1);
  menu *downALevelMenu = newMenu("Go Down");
  menu *exitMenu = newMenu("Goodbye!", 0);

  linkMenus(helloMenu, changeGreetingMenu, downALevelMenu, exitMenu);

  //Level 2
  menu *optionOne = newMenu("First option");
  menu *optionTwo = newMenu("Second option");

  linkMenus(optionOne, optionTwo);

  formLevel(downALevelMenu, optionOne);

  startTask(updateLCDTask);

  while (!endPreAuton) { wait1Msec(25); }
}

task autonomous()
{
}

task usercontrol()
{
	while (true) {}
}

void invoke(int func)
{
	switch (func)
	{
		case 0:
			endPreAuton = true;
			stopTask(updateLCDTask);
			break;

		case 1:
			changeMessage(&(menus[0]), "Hi there!");
			break;

		default:
			break;
	}
}

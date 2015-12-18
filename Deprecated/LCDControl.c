#ifndef LCDCONTROL_H_INCLUDED
#define LCDCONTROL_H_INCLUDED

#include "StatusCodes.c"

/***************************************************************************/
/*                                                                         */
/* LCD Button definitions                                                  */
/*                                                                         */
/***************************************************************************/
#define BUTTON_LEFT   1
#define BUTTON_CENTER 2
#define BUTTON_RIGHT  4

/***************************************************************************/
/*                                                                         */
/* Memory constraint definitions                                           */
/*                                                                         */
/***************************************************************************/
#define MAX_MENU_NUM 10

/***************************************************************************/
/*                                                                         */
/* Default text definitions                                                */
/*                                                                         */
/***************************************************************************/
#define DEFAULT_LINE      "<<            >>"
#define SUBMENU_SELECT    "<<   SELECT   >>"
#define EXIT_MENU_SELECT  "<<     OK     >>"
#define SUBMENU_BACK      "<<    BACK    >>"

/***************************************************************************/
/*                                                                         */
/* Button response helper definitions                                      */
/*                                                                         */
/***************************************************************************/
#define _WaitForPress() while(nLCDButtons == 0) {} wait1Msec(5)
#define _WaitForRelease() while(nLCDButtons != 0) {} wait1Msec(5)

//Menu structure (double linked list)
typedef struct menu
{
	//Pointer to next menu (right button)
	menu *next;
	//Pointer to previous menu (left button)
	menu *prev;
	//Pointer to higher menu (center button)
	menu *up;
	//Pointer to deeper menu (center button)
	menu *down;

	//Displayed text
	string *msg;

	//Function value in the "dispatch table"
	int dispatchFuncVal;
} menu;

//Menu for current selection
menu *current = NULL;

//Array for menus (no dynamic allocation)
static menu menus[MAX_MENU_NUM];
static int nextMenu = 0;

//Protoype for function execution from the "dispatch table"
//The user must implement this function
void invoke(int func);

/***************************************************************************/
/*                                                                         */
/* Subroutine - adds a menu, allocates from array                          */
/*                                                                         */
/***************************************************************************/
menu* newMenu(string *msg, int dispatchFuncVal = -1, menu *next = NULL, menu *prev = NULL, menu *up = NULL, menu *down = NULL)
{
	//Bounds check
	if (nextMenu + 1 == MAX_MENU_NUM)
	{
		return NULL;
	}

	//Grab the next menu slot
	//Should be a null menu
	menu *m = &(menus[nextMenu]);
	nextMenu++;

	m->next = next;
	m->prev = prev;
	m->up = up;
	m->down = down;
	m->msg = msg;
	m->dispatchFuncVal = dispatchFuncVal;

	#ifdef DEBUG_FINE_LCD
		writeDebugStreamLine("newMenu");
	#endif

	return m;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - changes the function a menu has                            */
/*                                                                         */
/***************************************************************************/
int changeFunction(menu *m, const int func)
{
	m->dispatchFuncVal = func;

	#ifdef DEBUG_FINE_LCD
		writeDebugStreamLine("changeFunction");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - childs menus to parents, depends on child addition order   */
/*                                                                         */
/***************************************************************************/
int makeLevel(const menu* startingMenu, const menu *parent, const int count = 1)
{
	//Step through memory to get child menus
	for (int i = 0; i < count; i++)
	{
		(startingMenu + i)->up = parent;
		parent->down = (startingMenu + i);
	}

	#ifdef DEBUG_FINE_LCD
		writeDebugStreamLine("makeLevel");
	#endif

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - inserts a menu into a row                                  */
/*                                                                         */
/***************************************************************************/
int putMenuInRow(menu *m, menu *next, menu *prev = NULL)
{
	m->next = next;

	if (prev != NULL)
	{
		m->prev = prev;
	}

	#ifdef DEBUG_FINE_LCD
		writeDebugStreamLine("putMenuInRow");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - pairs two menus (instead of using addMenuRow)              */
/*                                                                         */
/***************************************************************************/
int pairMenus(menu *m1, menu *m2)
{
	m1->next = m2;
	m1->prev = m2;
	m2->next = m1;
	m2->prev = m1;

	#ifdef DEBUG_FINE_LCD
		writeDebugStreamLine("pairMenus2");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - pairs three menus (instead of using addMenuRow)            */
/*                                                                         */
/***************************************************************************/
int pairMenus(menu *m1, menu *m2, menu *m3)
{
	m1->next = m2;
	m1->prev = m3;
	m2->next = m3;
	m2->prev = m1;
	m3->next = m1;
	m3->prev = m2;

	#ifdef DEBUG_FINE_LCD
		writeDebugStreamLine("pairMenus3");
	#endif

	return EXIT_SUCCESS;
}

/***************************************************************************/
/*                                                                         */
/* Task - updates the LCD and responds to button presses                   */
/*                                                                         */
/***************************************************************************/
task UpdateLCDTask()
{
	clearLCDLine(0);
	clearLCDLine(1);
	current = &(menus[0]);
	displayLCDString(0, 0, *menus[0].msg);
	displayLCDString(1, 0, SUBMENU_SELECT);

	#ifdef DEBUG_FINE_LCD
		writeDebugStreamLine("Wrote initial message to LCD");
	#endif

	while (true)
	{
		//Alert user of crash
		if (bResetFromWatchdogTimeout)
		{
            #ifdef DEBUG_LCD
                writeDebugStreamLine("Watchdog Reset");
            #endif
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0, 0, " WATCHDOG RESET ");
		}

		//Only one menu has been added
		//Only check for a function
		if (nextMenu == 1)
		{
			if (nLCDButtons & kButtonCenter)
			{
				if (current->dispatchFuncVal != -1)
				{
					#ifdef DEBUG_FINE_LCD
						writeDebugStreamLine("Executing a function");
					#endif
					//A function exists, execute it
					invoke(current->dispatchFuncVal);
				}
			}
		}
		else
		{
			//Left button
			if (nLCDButtons & kButtonLeft)
			{
				#ifdef DEBUG_LCD
					writeDebugStreamLine("Left button pressed");
				#endif
				if (current->prev != NULL)
				{
					#ifdef DEBUG_FINE_LCD
						writeDebugStreamLine("Going left");
					#endif
					current = current->prev;
					_WaitForRelease();
				}
			}
			//Right button
			else if (nLCDButtons & kButtonRight)
			{
				#ifdef DEBUG_LCD
					writeDebugStreamLine("Right button pressed");
				#endif
				if (current->next != NULL)
				{
					#ifdef DEBUG_FINE_LCD
						writeDebugStreamLine("Going right");
					#endif
					current = current->next;
					_WaitForRelease();
				}
			}
			//Center button
			else if (nLCDButtons & kButtonCenter)
			{
				#ifdef DEBUG_LCD
					writeDebugStreamLine("Center button pressed, waiting for hold");
				#endif
				//Let the user hold the center button
				wait1Msec(250);

				//Center held
				if (nLCDButtons & kButtonCenter)
				{
					#ifdef DEBUG_LCD
						writeDebugStreamLine("Center button held");
					#endif
					//If a higher menu exists
					if (current->up != NULL)
					{
						#ifdef DEBUG_FINE_LCD
							writeDebugStreamLine("Going up");
						#endif
						current = current->up;
						_WaitForRelease();
					}
				}
				//Center not held
				else
				{
					#ifdef DEBUG_LCD
						writeDebugStreamLine("Center button not held");
					#endif
					//If a lower menu exists
					if (current->down != NULL)
					{
						#ifdef DEBUG_FINE_LCD
							writeDebugStreamLine("Going down");
						#endif
						current = current->down;
						_WaitForRelease();
					}
					//No lower menu exists, check if there is a function
					else if (current->dispatchFuncVal != -1)
					{
						#ifdef DEBUG_FINE_LCD
							writeDebugStreamLine("Executing a function");
						#endif
						//A function exists, execute it
						invoke(current->dispatchFuncVal);
					}
				}
			}
		}
		clearLCDLine(0);
		displayLCDString(0, 0, *current->msg);
		EndTimeSlice();
	}
}

#endif

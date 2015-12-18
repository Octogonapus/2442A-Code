#ifndef LCDCONTROL_H_INCLUDED
#define LCDCONTROL_H_INCLUDED

//Do nothing with no menus
#ifdef MENU_NUM
#if MENU_NUM > 0

//LCD buttons
#define BUTTON_LEFT   1
#define BUTTON_CENTER 2
#define BUTTON_RIGHT  4

//Default text
#define DEFAULT_LINE     "<<            >>"
#define SUBMENU_SELECT   "<<   SELECT   >>"
#define EXIT_MENU_SELECT "<<     OK     >>"
#define SUBMENU_BACK     "<<    BACK    >>"
#define SAFETY_TRIG      "   SAFETY_TRIG  "

//Menu representation
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

//Handles function calls from lcdControl
//Note: Must be implemented by the user
void invoke(int func);

//Adds and initializes a menu
menu* newMenu(const string *msg, const int dispatchFuncVal = -1, const menu *next = NULL, const menu *prev = NULL, const menu *up = NULL, const menu *down = NULL);

//Changes the function a menu has
void changeFunction(menu *m, const int func);

//Changes the message a menu has
void changeMessage(const menu *m, const string *newMsg);

//Childs 1 menu to a parent
void formLevel(menu *parent, menu *child);

//Childs 2 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2);

//Childs 3 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2, menu *child3);

//Childs 4 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4);

//Childs 5 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5);

//Childs 6 menus to a parent
void formLevel(menu *parent, menu *child, menu *child2, menu *child3, menu *child4, menu *child5, menu *child6);

//Childs n menus to a parent
void formLevel(menu *startingMenu, menu *parent, const int count = 1);

//Inserts a menu into a row
void putMenuInRow(menu *m, menu *next, menu *prev = NULL);

//Pairs 2 menus
void linkMenus(menu *m1, menu *m2);

//Pairs 3 menus
void linkMenus(menu *m1, menu *m2, menu *m3);

//Pairs 4 menus
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4);

//Pairs 5 menus
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5);

//Pairs 6 menus
void linkMenus(menu *m1, menu *m2, menu *m3, menu *m4, menu *m5, menu *m6);

//Updates the LCD and responds to button presses
task updateLCDTask();

#endif //#if MENU_NUM > 0
#endif //#ifdef MENU_NUM

#endif //#ifndef LCDCONTROL_H_INCLUDED

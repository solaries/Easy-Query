
#include <ncurses.h>

#include "FieldInfo.h"

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
//void menuSetup(WINDOW **menu_win );
void menuSetup(struct AppInfo   *appInfo);


//int manageMenu(WINDOW *menu_win) ;
int manageMenu(struct AppInfo   *appInfo) ;



#endif // MENU_H_INCLUDED

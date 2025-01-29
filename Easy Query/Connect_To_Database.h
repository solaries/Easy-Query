#include <ncurses.h>

#include "FieldInfo.h"


#ifndef CONNECT_TO_DATABASE_H_INCLUDED
#define CONNECT_TO_DATABASE_H_INCLUDED

//void menuSetup(WINDOW **menu_win );
void connectToDatabaseSetup(struct AppInfo   *appInfo);


//int manageMenu(WINDOW *menu_win) ;
int manageConnectToDatabase(struct AppInfo   *appInfo ) ;



//void print_menu(struct AppInfo   *appInfo, int highlight );

#endif // CONNECT_TO_DATABASE_H_INCLUDED

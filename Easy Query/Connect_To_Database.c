#include "Connect_To_Database.h"
#include "DB_com.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FieldInfo.h"

#define WIDTH 30
#define HEIGHT 12

static int startx = 0;
static int starty = 0;

static char ** choices;

//[] =
//{
//			"Server Connection  ",
//			"Create Database    ",
//			"Connect to Database",
//			"Create Table       ",
//			"Insert             ",
//			"Select             ",
//			"Update             ",
//			"Delete             ",
//			"Exit               ",
//		  };

static int n_choices ; //= sizeof(choices) / sizeof(char *);

static void print_menu(struct AppInfo   *appInfo, int highlight );

void connectToDatabaseSetup(struct AppInfo   *appInfo){

    choices = malloc(3 * sizeof(char *));
    choices[0] ="Server Connection  " ;
    choices[1] ="Create Database  " ;
    choices[2] ="Server Connection  " ;

    n_choices = sizeof(choices) / sizeof(char *);



	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
	appInfo->win = newwin(HEIGHT, WIDTH, starty -6, startx -24);
    appInfo->panel = new_panel(appInfo->win);
	keypad(appInfo->win, TRUE);
}


int manageConnectToDatabase(struct AppInfo   *appInfo ){



//	if (!mysql_real_connect(conn, server, user, password,  database, 0, NULL, 0)) {
//	if (!mysql_real_connect(conn,trim_whitespaces( appInfo->str[0]) ,trim_whitespaces(appInfo->str[1]) ,trim_whitespaces(appInfo->str[2]) ,  NULL, 0, NULL, 0)) {
    if(strlen(trim_whitespaces( appInfo->str[0])) ==0){
         appInfo->strMsg = "Invalid server information.";
        return 27;
    }

    if(strlen(trim_whitespaces( appInfo->str[1])) ==0){
         appInfo->strMsg = "Invalid user information";
        return 27;
    }

    if(strlen(trim_whitespaces( appInfo->str[2])) ==0){
         appInfo->strMsg = "Invalid password information";
        return 27;
    }

//    if(strlen(trim_whitespaces( appInfo->str[3])) ==0){
//         appInfo->strMsg = "Invalid database information";
//        return 27;
//    }


    appInfo->strMsg =  getDatabases(appInfo) ;
    return 27;

//    mvprintw(22, 0, "Ctrl + Q or ESC: Query,  Ctrl + E : Execute,   Ctrl + R: Result" );
    mvprintw(22, 0, "Ctrl + Q or ESC: Query , Enter : Select menu item                        " );
//    mvprintw(23, 0, "Ctrl + W: Menu,  Alt + X: Exit, Space: toggle Select" );
    mvprintw(23, 0, "UP: UP, Down: Down , Ctrl + X: Exit                                                              " );

    refresh();

	int highlight = 1;
	int choice = 0;
	int c;
	print_menu(  appInfo , highlight );
    while(1)
	{	c = wgetch(appInfo->win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				return choice;
				break;

            case 27  :
                { //esc
                    return c;
                }
                break;
            case 17  :
                { //ctrl + Q
                    return c;
                }
                break;
            case 24  :
                { //ctrl + x
                    return c;
                }
                break;
			default:
				refresh();
				break;
		}

		print_menu(   appInfo  , highlight );
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
    return 27;
}



void print_menu(struct AppInfo   *appInfo, int highlight )
{
	int x, y, i;
	x = 2;
	y = 2;
	box(appInfo->win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{
        if(highlight == i + 1) /* High light the present choice */
        {	wattron(appInfo->win, A_REVERSE);
            mvwprintw(appInfo->win, y, x, "%s", choices[i]);
            wattroff(appInfo->win, A_REVERSE);
        }
        else{
            mvwprintw(appInfo->win, y, x, "%s", choices[i]);

        }
		++y;
	}
	wrefresh(appInfo->win);
}


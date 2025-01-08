#include "Menu.h"
#include <ncurses.h>
#include "FieldInfo.h"

#define WIDTH 30
#define HEIGHT 12

int startx = 0;
int starty = 0;

char *choices[] = {
			"Server Connection  ",
			"Create Database    ",
			"Connect to Database",
			"Create Table       ",
			"Insert             ",
			"Select             ",
			"Update             ",
			"Delete             ",
			"Exit               ",
		  };

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(struct AppInfo   *appInfo, int highlight, bool activeMenu);

//void menuSetup(WINDOW **menu_win ){
void menuSetup(struct AppInfo   *appInfo){


//	startx = (80 - WIDTH) / 2;
//	starty = (24 - HEIGHT) / 2;
//	appInfo->win = newwin(HEIGHT, WIDTH, starty -6, startx -21);
//	keypad(appInfo->win, TRUE);


}


//int manageMenu(WINDOW *menu_win){
int manageMenu(struct AppInfo   *appInfo, bool activeMenu){
	int highlight = 1;
	int choice = 0;
	int c;

//mvprintw(1, 0, "                            " );
//	int mxx =  appInfo->win->_begx;
//    mvprintw(20, 0, "@@@@@@@@@@@@@@@@@@@@@@@   '%p'  ",  appInfo );
//    mvprintw(21, 0, "@@@@@@@@@@@@@@@@@@@@@@@   '%p' '%d'",  appInfo->win , appInfo->win->_begx );
//	refresh();

//	getch();
//    mvprintw(22, 0, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX '%d'", menu_win->_begx);
//	refresh();

//	getch();
//    mvprintw(21, 0, "@@@@@@@@@@@@@@@@@@@@@@@   '%p' '%d'",  appInfo->win , appInfo->win->_begx );
//	refresh();

	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
	if(!activeMenu){




        print_menu(  appInfo , highlight,   activeMenu);
        //mvprintw(20, 0, "yyyyyyyyyyyyyyyyyyyyyyyyyyy  "  );
//        refresh();
//        getch();
        return 0;
	}
	appInfo->win = newwin(HEIGHT, WIDTH, starty -6, startx -21);

	keypad(appInfo->win, TRUE);


    mvprintw(21, 0, " "  );
	print_menu(  appInfo , highlight,   activeMenu);
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
				break;

            case 27  :
                { //esc
                    return 27;
                }
                break;
            case 17  :
                { //esc
                    return 17;
                }
                break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}

        mvprintw(21, 0, "       %d               ", c );
		print_menu(   appInfo  , highlight,   activeMenu);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
    return 27;
}



void print_menu(struct AppInfo   *appInfo, int highlight, bool activeMenu)
{
	int x, y, i;
//    mvprintw(19, 0, "tttttttttttttt  " );
//    refresh();
//	getch();
//    WINDOW *menu_win = *menu_win_;
	x = 2;
	y = 2;
//    mvprintw(20, 0, "RRRRRRRRRRRRRR  " );
//    refresh();
//	getch();

//    mvprintw(22, 0, "TTTTTTTTTTTTT   '%p' '%p' '%d'                                        ",  appInfo->win , appInfo->win , appInfo->win->_begx );
//	refresh();

//	getch();

//    mvprintw(21, 0, "SSSSSSSSSSSSSSSSSSSSSSSSSss '%d'", appInfo->win->_maxx);
//	refresh();
//	getch();
	box(appInfo->win, 0, 0);
//	getch();
	for(i = 0; i < n_choices; ++i)
	{
        if(activeMenu){
            if(highlight == i + 1) /* High light the present choice */
            {	wattron(appInfo->win, A_REVERSE);
                mvwprintw(appInfo->win, y, x, "%s", choices[i]);
                wattroff(appInfo->win, A_REVERSE);
            }
            else{
//                wattron(appInfo->win, A_INVIS);
                mvwprintw(appInfo->win, y, x, "%s", choices[i]);
//                wattroff(appInfo->win, A_INVIS);

            }
        }
        else{

                wattron(appInfo->win, A_INVIS);
                mvwprintw(appInfo->win, y, x, "%s", choices[i]);
                wattroff(appInfo->win, A_INVIS);
        }
		++y;
	}
	wrefresh(appInfo->win);
}


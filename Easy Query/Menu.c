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
void print_menu(struct AppInfo   *appInfo, int highlight );


void menuSetup(struct AppInfo   *appInfo){

	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
	appInfo->win = newwin(HEIGHT, WIDTH, starty -6, startx -24);
    appInfo->panel = new_panel(appInfo->win);
	keypad(appInfo->win, TRUE);
}


int manageMenu(struct AppInfo   *appInfo ){

//    mvprintw(22, 0, "Ctrl + Q or ESC: Query,  Ctrl + E : Execute,   Ctrl + R: Result" );
    mvprintw(22, 0, "Ctrl + Q or ESC: Query , Enter : Select menu item                        " );
//    mvprintw(23, 0, "Ctrl + W: Menu,  Alt + X: Exit, Space: toggle Select" );
    mvprintw(23, 0, "UP: UP, Down: Down , Alt + X: Exit                                                              " );

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


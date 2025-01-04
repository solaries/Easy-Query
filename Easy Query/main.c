#include <stdio.h>
#include <stdlib.h>
#include "Connect_To_Database.h"
#include "Create_Database.h"
#include "Create_Table.h"
#include "Datatype.h"
#include "Delete.h"
#include "Field.h"
#include "Foreign_Key.h"
#include "Form.h"
#include "Insert.h"
#include "Main_Menu_list.h"
#include "Menu.h"
#include "Panel.h"
#include "Query.h"
#include "Result_Text_Or_Cells.h"
#include "Select.h"
#include "Server_Connection.h"
#include "Table.h"
#include "Table_Field.h"
#include "Unique.h"
#include "Update.h"
#include "FieldInfo.h"
#include <form.h>
#include <panel.h>


#include <ncurses.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);


int main()
{

	initscr();
	start_color();
	raw();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);


	init_pair(5, COLOR_WHITE, COLOR_BLUE);
	init_pair(6, COLOR_WHITE, COLOR_BLUE);


    struct AppInfo appInfo;

	int queryFieldSize = 75;
	FIELD *queryfield[2];
    queryfield[0] = new_field(4, queryFieldSize, 1, 1, 0, 0);






    queryfield[1] = NULL;
	FORM  *queryForm = new_form(queryfield);




	set_field_fore(queryfield[0], COLOR_PAIR(5));/* Put the field with blue background */
	set_field_back(queryfield[0], COLOR_PAIR(6));/* and white foreground (characters */

    int  rows, cols;
	 WINDOW *my_query_form_win;

	scale_form(queryForm, &rows, &cols);
    my_query_form_win = newwin(rows + 5, cols + 2, 1, 1);
    keypad(my_query_form_win, TRUE);
    set_form_win(queryForm, my_query_form_win);
    set_form_sub(queryForm, derwin(my_query_form_win, rows, cols, 3, 1));
    box(my_query_form_win, 0, 0);
    win_show(my_query_form_win, "My Form",  1);
    print_in_middle(my_query_form_win, 1, 0, cols + 4, "Query...", COLOR_PAIR(3));


// Create a window for the panel
//WINDOW *queryWin = newwin(10, 78, 1, 1);
//win_show(queryWin, "Query",  1);
//box(queryWin, 0, 0);
//wrefresh(queryWin);
// Create a panel and associate it with the form
//PANEL *queryPanel = new_panel(queryWin);
PANEL *queryPanel = new_panel(my_query_form_win);
//set_panel_userptr(queryPanel, queryForm);
hide_panel(queryPanel);
//show_panel(queryPanel);

// Draw the panel and refresh the window
update_panels();
doupdate();
    appInfo.queryString = "";
    querySetup(  queryPanel, my_query_form_win,queryForm       , queryfield      , queryFieldSize, &appInfo.queryString);


//    mvprintw(15, 0, "string: %s   ",appInfo.queryString );
//    getch();




    // Clean up
//    delwin(queryWin);
	unpost_form(queryForm);
	free_form(queryForm);
	free_field(queryfield[0]);
	endwin();
    return 0;
}


void win_show(WINDOW *win, char *label, int label_color)
{

    int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);

	print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}



void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{

    int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	x = 2;
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

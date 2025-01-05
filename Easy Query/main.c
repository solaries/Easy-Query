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
void buildInfo( struct AppInfo *appInfo , int fieldSize,char *label,  int yPlus);


int main()
{

	initscr();
	start_color();
	raw();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);


	init_pair(5, COLOR_WHITE, COLOR_BLUE);
	init_pair(6, COLOR_WHITE, COLOR_BLUE);


    struct AppInfo queryInfo;
    buildInfo(&queryInfo  , 75,"Query...",0);
    querySetup( &queryInfo );



    struct AppInfo resultInfo;
    buildInfo(&resultInfo  , 75,"Result...",10);
    resultSetup( &resultInfo );


	WINDOW *menu_win;
	menuSetup(menu_win);


    int cmd = manageQuery( &queryInfo ) ;


//	set_field_fore(queryInfo.field[0], COLOR_PAIR(1));/* Put the field with blue background */
//	set_field_back(queryInfo.field[0], COLOR_PAIR(2));/* and white foreground (characters */
    while(cmd !=24){
        switch(cmd)
        {
            case 9  :
                { //tab
//                    return ch;
                }
                break;

            case 27  :
                { //esc
                    cmd = manageQuery( &queryInfo ) ;
                }
                break;

            case 5  :
                { //ctrl + E
                   cmd =  manageResult( &resultInfo ) ;
                }
                break;

            case 23  :
                { //ctrl + W - for menu
                   cmd = manageMenu( menu_win );
//                    return ch;
                }
                break;


            case 17  :
                { //ctrl + Q
                    cmd = manageQuery( &queryInfo ) ;
                }
                break;

            case 18  :
                { //ctrl + R
                   cmd =  manageResult( &resultInfo ) ;
                }
                break;


            case 24  :
                { //ctrl + x
//                    return ch;
                }
                break;
            default:

                {

                }
                break;
        }
    }

//      cmd = manageQueryField( &queryInfo ) ;
//    cmd = cmd + 0;
    //mvprintw(15, 0, "%s" , appInfo.str);

//    mvprintw(15, 0, "string: %s   ",appInfo.queryString );
    //getch();




    // Clean up
//    delwin(queryWin);
	unpost_form(queryInfo.form);
	free_form(queryInfo.form);
	free_field(queryInfo.field[0]);

	unpost_form(resultInfo.form);
	free_form(resultInfo.form);
	free_field(resultInfo.field[0]);



	endwin();
    return 0;
}

void buildInfo(struct AppInfo   *appInfo ,  int fieldSize,char *label,  int yPlus){


	appInfo->fieldSize = fieldSize ;//75;


    appInfo->rowCount = 1;
    appInfo->charCount = 0;
    appInfo->rowCur = 1;
    appInfo->colCur = 1;
    appInfo->charCur = 1;




//	FIELD *queryfield[2];
    appInfo->field[0] = new_field(4, appInfo->fieldSize, 1, 1, 0, 0);
    appInfo->field[1] = NULL;
	appInfo->form = new_form(appInfo->field);
	set_field_fore(appInfo->field[0], COLOR_PAIR(5));/* Put the field with blue background */
	set_field_back(appInfo->field[0], COLOR_PAIR(6));/* and white foreground (characters */

    int  rows, cols;
//    WINDOW *my_query_form_win;

	scale_form(appInfo->form, &rows, &cols);
    appInfo->win = newwin(rows + 5, cols + 2, 1 + yPlus, 1);
    keypad(appInfo->win, TRUE);
    set_form_win(appInfo->form, appInfo->win);
    set_form_sub(appInfo->form, derwin(appInfo->win, rows, cols, 3, 1));
    box(appInfo->win, 0, 0);
    //win_show(appInfo.my_query_form_win, "...",  1);
//    print_in_middle(appInfo->win, 1, 0, cols + 4, "Query...", COLOR_PAIR(3));
    print_in_middle(appInfo->win, 1, 0, cols + 4, label, COLOR_PAIR(1));


// Create a window for the panel
//WINDOW *queryWin = newwin(10, 78, 1, 1);
//win_show(queryWin, "Query",  1);
//box(queryWin, 0, 0);
//wrefresh(queryWin);
// Create a panel and associate it with the form
//PANEL *queryPanel = new_panel(queryWin);
//PANEL *queryPanel = new_panel(my_query_form_win);
appInfo->panel = new_panel(appInfo->win);
//set_panel_userptr(queryPanel, queryForm);
hide_panel(appInfo->panel);
//show_panel(queryPanel);

// Draw the panel and refresh the window
update_panels();
doupdate();
    appInfo->str = "";
    //querySetup(  queryPanel, my_query_form_win,queryForm       , queryfield      , queryFieldSize, &appInfo.queryString);





//    appInfo->str= "XX 3 XXX";
//    appInfo->str = "DD";
//    field_opts_off(appInfo->field[0], O_AUTOSKIP);
//    set_field_opts(appInfo->field[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE | O_WRAP   );
//
//    post_form(appInfo->form);
//	wrefresh(appInfo->win);
//    set_current_field(appInfo->form, appInfo->field[0]);
//    setupQueryField( appInfo);

}


void win_show(WINDOW *win, char *label, int label_color)
{

    int /*startx, starty,*/  height, width;

	//getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);
    height = height + 0;
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

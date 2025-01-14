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

#define WIDTH 30
#define HEIGHT 12

void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void buildInfo( struct AppInfo *appInfo , int fieldSize,char *label,  int yPlus);
void destroy_win(WINDOW *local_win);
void freeFields(struct AppInfo   *appInfo );

int main()
{

	initscr();
	start_color();
	raw();
//	cbreak(); //this will cause the application to end on ctrl + c
	noecho();
	keypad(stdscr, TRUE);

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);


	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_WHITE, COLOR_BLUE);


    struct AppInfo queryInfo;
    queryInfo.numberOfFields = 1;
    queryInfo.fieldXPosition = 1;
    queryInfo.windXPosition = 1;
    queryInfo.numberOfRows = 4;
    buildInfo(&queryInfo  , 75,"Query...",0);
    querySetup( &queryInfo );

    struct AppInfo resultInfo;
    resultInfo.numberOfFields = 1;
    resultInfo.fieldXPosition = 1;
    resultInfo.windXPosition = 1;
    resultInfo.numberOfRows = 4;
    buildInfo(&resultInfo  , 75,"Result...",10);
    resultSetup( &resultInfo );

	refresh();

    struct AppInfo menuInfo;
    menuSetup(&menuInfo ) ;



    struct AppInfo serverConnectInfo;
    serverConnectInfo.numberOfFields = 3;
    serverConnectInfo.numberOfRows = 1;
    serverConnectInfo.windXPosition = 3;
    serverConnectInfo.fieldXPosition = 20;
    buildInfo(&serverConnectInfo  , 50,"Server Connection...",3);
    serverConnectionSetup( &serverConnectInfo );




    hide_panel((&menuInfo)->panel);
    hide_panel((&serverConnectInfo)->panel);
    update_panels();
    doupdate();

    int cmd = manageQuery( &queryInfo ) ;

    while(cmd !=24){

        switch(cmd)
        {
//            case 9  :
//                { //tab
////                    return ch;
//                }
//                break;

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

                    show_panel((&menuInfo)->panel);
                    cmd = manageMenu( &menuInfo  );

                    hide_panel((&menuInfo)->panel);
                    update_panels();
                    doupdate();
                    refresh();

                    destroy_win((&menuInfo)->win);

                    box((&queryInfo)->win, 0, 0);
                    wrefresh((&queryInfo)->win);
                    box((&resultInfo)->win, 0, 0);
                    wrefresh((&resultInfo)->win);
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
//            case 24  :
//                { //ctrl + x
////                    return ch;
//                }
//                break;
            default:

                {

                }
                break;
        }
    }

    // Clean up
	unpost_form(queryInfo.form);
	free_form(queryInfo.form);
//	free_field(queryInfo.field[0]);
    freeFields(&queryInfo);
	delwin(queryInfo.win);

	unpost_form(resultInfo.form);
	free_form(resultInfo.form);
//	free_field(resultInfo.field[0]);
    freeFields(&resultInfo);
	delwin(queryInfo.win);

	unpost_form(serverConnectInfo.form);
	free_form(serverConnectInfo.form);
    freeFields(&serverConnectInfo);
	delwin(serverConnectInfo.win);

	delwin(menuInfo.win);

	endwin();
    return 0;
}


void freeFields(struct AppInfo   *appInfo ){
    for (int i =0; i < appInfo->numberOfFields;i++){
        free_field(appInfo->field2[i]);
    }
}

void destroy_win(WINDOW *local_win)
{
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners
	 * and so an ugly remnant of window.
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window
	 * 3. rs: character to be used for the right side of the window
	 * 4. ts: character to be used for the top side of the window
	 * 5. bs: character to be used for the bottom side of the window
	 * 6. tl: character to be used for the top left corner of the window
	 * 7. tr: character to be used for the top right corner of the window
	 * 8. bl: character to be used for the bottom left corner of the window
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
//	delwin(local_win);
}


void buildInfo(struct AppInfo   *appInfo ,  int fieldSize,char *label,  int yPlus){


	appInfo->fieldSize = fieldSize ;//75;


    appInfo->rowCount = 1;
    appInfo->charCount = 0;
    appInfo->rowCur = 1;
    appInfo->colCur = 1;
    appInfo->charCur = 1;
    appInfo->field2 = malloc((appInfo->numberOfFields + 1) * sizeof(FIELD *));

    for (int i =0; i < appInfo->numberOfFields;i++){
        appInfo->field2[i] = new_field(  appInfo->numberOfRows , appInfo->fieldSize, 1 + (i * 2), appInfo->fieldXPosition, 0, 0);

        set_field_fore(appInfo->field2[i], COLOR_PAIR(5));/* Put the field with blue background */
        set_field_back(appInfo->field2[i], COLOR_PAIR(5));/* and white foreground (characters */


        if(i==0){

//	set_field_fore(appInfo->field2[0], COLOR_PAIR(5));/* Put the field with blue background */
//	set_field_back(appInfo->field2[0], COLOR_PAIR(6));/* and white foreground (characters */

        }
    }
    appInfo->field2[appInfo->numberOfFields] = NULL;

//    appInfo->field[0] = new_field(4, appInfo->fieldSize, 1, 1, 0, 0);
//    appInfo->field[1] = NULL;





	appInfo->form = new_form(appInfo->field2);
//	set_field_fore(appInfo->field[0], COLOR_PAIR(5));/* Put the field with blue background */
//	set_field_back(appInfo->field[0], COLOR_PAIR(6));/* and white foreground (characters */

    int  rows, cols;

	scale_form(appInfo->form, &rows, &cols);
//    appInfo->win = newwin(rows + 5, cols + 2, 1 + yPlus, 1);
    appInfo->win = newwin(rows + 5, cols + 2, 1 + yPlus, appInfo->windXPosition);
    keypad(appInfo->win, TRUE);
    set_form_win(appInfo->form, appInfo->win);
    set_form_sub(appInfo->form, derwin(appInfo->win, rows, cols, 3, 1));
    box(appInfo->win, 0, 0);

    print_in_middle(appInfo->win, 1, 0, cols + 4, label, COLOR_PAIR(1));
    appInfo->panel = new_panel(appInfo->win);
    appInfo->str = "";
 }


void win_show(WINDOW *win, char *label, int label_color)
{

    int /*startx, starty,*/  height, width;

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

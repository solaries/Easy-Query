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
#include "Message.h"
#include "Result_Text_Or_Cells.h"
#include "Select.h"
#include "Server_Connection.h"
#include "Table.h"
#include "Table_Field.h"
#include "Unique.h"
#include "Update.h"
#include "FieldInfo.h"

#include "DB_com.h"

#include <form.h>
#include <panel.h>


#include <ncurses.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

//#define WIDTH 30
//#define HEIGHT 12



// sudo apt-get install libmysqlclient-dev

//  gcc -o connect_mysql $(mysql_config --cflags) connect_mysql.c $(mysql_config --libs)

void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void buildInfo( struct AppInfo *appInfo , int fieldSize,char *label,  int yPlus);
void destroy_win(WINDOW *local_win);
void freeFields(struct AppInfo   *appInfo );
void prepLocationAndPassword(struct AppInfo   *appInfo , int num);
void freeLocationAndPassword(struct AppInfo   *appInfo , int num);
void closePanel(struct AppInfo   *appInfo ,struct AppInfo   *queryInfo ,struct AppInfo   *resultInfo  );

void free_bool_memory(bool ** ptr);
void free_int_memory(int ** ptr);
//void free_str_memory(char ** ptr);

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
	init_pair(7, COLOR_BLACK, COLOR_CYAN);


    struct AppInfo queryInfo;
    queryInfo.numberOfFields = 1;
    queryInfo.fieldXPosition = 1;
    queryInfo.windXPosition = 1;
    queryInfo.numberOfRows = 4;

    queryInfo.str = malloc(1 * sizeof(char *));
    prepLocationAndPassword(&queryInfo  ,   1) ;
//    queryInfo.isPassword = malloc(1 * sizeof(bool *));
//    queryInfo.isPassword[0] = malloc(sizeof(bool));

//        appInfo->rowCount =rowCount ;
//        appInfo->charCount = charCount ;
//        appInfo->rowCur =rowCur ;
//        appInfo->colCur =colCur ;
//        appInfo->charCur =charCur ;

    *queryInfo.isPassword[0] = false;
    queryInfo.isCreateDB = false;
    buildInfo(&queryInfo  , 75,"Query...",0);
    querySetup( &queryInfo );

    struct AppInfo resultInfo;
    resultInfo.numberOfFields = 1;
    resultInfo.fieldXPosition = 1;
    resultInfo.windXPosition = 1;
    resultInfo.numberOfRows = 4;
//    resultInfo.isPassword = malloc(1 * sizeof(bool *));
//    resultInfo.isPassword[0] = malloc(sizeof(bool));

    prepLocationAndPassword(&resultInfo  ,   1) ;

    *resultInfo.isPassword[0] = false;
    resultInfo.isCreateDB = false;
    buildInfo(&resultInfo  , 75,"Result...",9);
    resultSetup( &resultInfo );

	refresh();

    struct AppInfo menuInfo;
    menuSetup(&menuInfo ) ;



    struct AppInfo serverConnectInfo;
    serverConnectInfo.numberOfFields = 9;
    serverConnectInfo.numberOfRows = 1;
    serverConnectInfo.windXPosition = 3;
    serverConnectInfo.fieldXPosition = 12;
    serverConnectInfo.str = malloc(3 * sizeof(char *));
    serverConnectInfo.labels = malloc(3 * sizeof(char *));
    prepLocationAndPassword(&serverConnectInfo  ,   3) ;
    *serverConnectInfo.isPassword[0] = false;
    *serverConnectInfo.isPassword[1] = false;
    *serverConnectInfo.isPassword[2] = true;
    serverConnectInfo.isCreateDB = false;
    serverConnectInfo.labels[0] = "Server: ";
    serverConnectInfo.labels[1] = "User:";
    serverConnectInfo.labels[2] = "Password: " ;
    buildInfo(&serverConnectInfo  , 51,"Server Connection...",3);
    serverConnectionSetup( &serverConnectInfo );




    struct AppInfo createDatabaseInfo;
    createDatabaseInfo.numberOfFields = 9;
    createDatabaseInfo.numberOfRows = 1;
    createDatabaseInfo.windXPosition = 3;
    createDatabaseInfo.fieldXPosition = 12;
    createDatabaseInfo.str  = serverConnectInfo.str;
    createDatabaseInfo.labels = malloc(3 * sizeof(char *));
    prepLocationAndPassword(&createDatabaseInfo  ,   4) ;


//    for (int i =1; i <  4;i++){
//        free(createDatabaseInfo.rowCount[i]);
//        free(createDatabaseInfo.charCount[i]);
//        free(createDatabaseInfo.rowCur[i]);
//        free(createDatabaseInfo.colCur[i]);
//        free(createDatabaseInfo.charCur[i]);
//
//        createDatabaseInfo.rowCount[i] = serverConnectInfo.rowCount[i-1];
//        createDatabaseInfo.charCount[i] = serverConnectInfo.charCount[i-1];
//        createDatabaseInfo.rowCur[i] =serverConnectInfo.rowCur[i-1];
//        createDatabaseInfo.colCur[i] =serverConnectInfo.colCur[i-1];
//        createDatabaseInfo.charCur[i] =serverConnectInfo.charCur[i-1];
//    }
//    free(appInfo->rowCount);
//    free(appInfo->charCount);
//    free(appInfo->rowCur);
//    free(appInfo->colCur);
//    free(appInfo->charCur);


    *createDatabaseInfo.isPassword[0] = false;
    *createDatabaseInfo.isPassword[1] = false;
    *createDatabaseInfo.isPassword[2] = false;
    *createDatabaseInfo.isPassword[3] = true;
    createDatabaseInfo.isCreateDB = false;
    createDatabaseInfo.labels[0] = "Database: " ;
    createDatabaseInfo.labels[1] = "Server: ";
    createDatabaseInfo.labels[2] = "User:";
//    createDatabaseInfo.labels[3] = "Password: " ;

    createDatabaseInfo.isCreateDB=true;

    buildInfo(&createDatabaseInfo  , 51,"Create Database...",3);
    createDatabaseSetup( &createDatabaseInfo );


//
//
//
//
//
//
//
//
//


    struct AppInfo messageInfo;
    messageInfo.numberOfFields = 1;
    messageInfo.numberOfRows = 4;
    messageInfo.windXPosition = 5;
    messageInfo.fieldXPosition = 1;
    messageInfo.str = malloc(1 * sizeof(char *));
    prepLocationAndPassword(&messageInfo  ,   1) ;
    *messageInfo.isPassword[0] = false;
    messageInfo.isCreateDB = false;
    buildInfo(&messageInfo  , 60,"Message...",5);
    messageSetup( &messageInfo );


    field_opts_off((&messageInfo)->field2[0], O_ACTIVE);
    set_field_fore((&messageInfo)->field2[0], COLOR_PAIR(1));
    set_field_back((&messageInfo)->field2[0], COLOR_PAIR(1));

//getch();

    hide_panel((&menuInfo)->panel);
    hide_panel((&serverConnectInfo)->panel);
    hide_panel((&createDatabaseInfo)->panel);
    hide_panel((&messageInfo)->panel);
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

            case 1  :
                { //Server Connection Is selected serverConnectInfo->str[0]
//                    show_panel((&createDatabaseInfo)->panel);
//                    cmd = manageCreateDatabase( &createDatabaseInfo  );
//                    closePanel( &createDatabaseInfo ,&queryInfo ,&resultInfo  );
                    show_panel((&serverConnectInfo)->panel);
                    cmd = manageServerConnection( &serverConnectInfo  );
                    closePanel( &serverConnectInfo ,&queryInfo ,&resultInfo  );
                }
                break;
            case 2  :
                { //Server Connection Is selected serverConnectInfo->str[0]

                      set_field_buffer(createDatabaseInfo.field2[3], 0, createDatabaseInfo.str[0]);
                      set_field_buffer(createDatabaseInfo.field2[6], 0, createDatabaseInfo.str[1]);

/*
0 localhost server
1 root user
2 lordisjesus password
3 database

*/


/*
0 1 2
3 4 5
6 7 8
9 10 11


*/

//                    set_field_buffer(createDatabaseInfo.field2[0], 0, createDatabaseInfo.str[0]);
//                    set_current_field(createDatabaseInfo.form, createDatabaseInfo.field2[1]);
//                    set_field_buffer(createDatabaseInfo.field2[1], 0, createDatabaseInfo.str[1]);
//
//                    set_current_field(createDatabaseInfo.form, createDatabaseInfo.field2[0]);

                    show_panel((&createDatabaseInfo)->panel);
                    cmd = manageCreateDatabase( &createDatabaseInfo , &serverConnectInfo);
                    closePanel( &createDatabaseInfo ,&queryInfo ,&resultInfo  );
                }
                break;
            case 55555  :
                { //esc

                    messageInfo.str[0] = createDatabase(
                    (&createDatabaseInfo)->str[0] /*char *server*/ ,
                    (&createDatabaseInfo)->str[1] /*char *user*/ ,
                    (&createDatabaseInfo)->str[2] /*char *password*/ ,
                    (&createDatabaseInfo)->str[3] /*char *database*/  );
//                    v = 1;

                    show_panel((&messageInfo)->panel);
                    box((&messageInfo)->win, 0, 0);
                    cmd = manageMessage( &messageInfo, messageInfo.str[0] ) ;
                    closePanel( &messageInfo ,&queryInfo ,&resultInfo  );

//                    cmd = manageQuery( &queryInfo ) ;
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
                    show_panel((&menuInfo)->panel);
                    cmd = manageMenu( &menuInfo  );
                    closePanel( &menuInfo ,&queryInfo ,&resultInfo  );
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
	delwin(queryInfo.win);
    free(queryInfo.str);
//    free(queryInfo.isPassword[0]);
//    free(queryInfo.isPassword);
    freeLocationAndPassword(&queryInfo , 1);
    freeFields(&queryInfo);

	unpost_form(resultInfo.form);
	free_form(resultInfo.form);
//	free_field(resultInfo.field[0]);
	delwin(resultInfo.win);
//    free(resultInfo.isPassword[0]);
//    free(resultInfo.isPassword);
    freeLocationAndPassword(&resultInfo , 1);
    freeFields(&resultInfo);

	delwin(menuInfo.win);

	unpost_form(serverConnectInfo.form);
	free_form(serverConnectInfo.form);

//    free(serverConnectInfo.str[0]);
//    free(serverConnectInfo.str[1]);
//    free(serverConnectInfo.str[2]);
    free(serverConnectInfo.str);
    free(serverConnectInfo.labels);
    freeLocationAndPassword(&serverConnectInfo , 3);
    freeFields(&serverConnectInfo);
	delwin(serverConnectInfo.win);

	unpost_form(createDatabaseInfo.form);
	free_form(createDatabaseInfo.form);

    free(createDatabaseInfo.str);
    free(createDatabaseInfo.labels);
    freeLocationAndPassword(&createDatabaseInfo , 3);
	delwin(createDatabaseInfo.win);
    freeFields(&createDatabaseInfo);

	endwin();
    return 0;
}

//void free_bool_memory(bool ** ptr) {
//
//    if(*ptr != NULL){
//        free(*ptr);
//        *ptr = NULL;
//    }
//}
//
//void free_int_memory(int ** ptr) {
//
//    if(*ptr != NULL){
//        free(*ptr);
//        *ptr = NULL;
//    }
//}

//void free_str_memory(char ** ptr) {
//
//    if(ptr != NULL){
//        free(ptr);
//        ptr = NULL;
//    }
//}

void closePanel(struct AppInfo   *appInfo ,struct AppInfo   *queryInfo ,struct AppInfo   *resultInfo  ){
    destroy_win(appInfo->win);
//getch();
    hide_panel(appInfo->panel);
    update_panels();
    doupdate();
//getch();
    refresh();
//getch();
    box(queryInfo->win, 0, 0);
    wrefresh(queryInfo->win);
//getch();
    box(resultInfo->win, 0, 0);
    wrefresh(resultInfo->win);
//getch();
//    hide_panel((&menuInfo)->panel);
//    update_panels();
//    doupdate();
//    refresh();
//
//    destroy_win((&menuInfo)->win);
//
//    box((&queryInfo)->win, 0, 0);
//    wrefresh((&queryInfo)->win);
//    box((&resultInfo)->win, 0, 0);
//    wrefresh((&resultInfo)->win);
}
void freeFields(struct AppInfo   *appInfo ){
    for (int i =0; i < appInfo->numberOfFields;i++){
        free_field(appInfo->field2[i]);
    }
}
void freeLocationAndPassword(struct AppInfo   *appInfo , int num){
    for (int i =0; i <  num;i++){
        free(appInfo->isPassword[i]);

        free(appInfo->rowCount[i]);
        free(appInfo->charCount[i]);
        free(appInfo->rowCur[i]);
        free(appInfo->colCur[i]);
        free(appInfo->charCur[i]);

//        free_bool_memory(&appInfo->isPassword[i]);
//        free_int_memory(&appInfo->rowCount[i]);
//        free_int_memory(&appInfo->charCount[i]);
//        free_int_memory(&appInfo->rowCur[i]);
//        free_int_memory(&appInfo->colCur[i]);
//        free_int_memory(&appInfo->charCur[i]);

//        free_str_memory(&appInfo->str[i]);
    }
//    free(serverConnectInfo.isPassword[1]);
//    free(serverConnectInfo.isPassword[2]);
    free(appInfo->isPassword);
    free(appInfo->rowCount);
    free(appInfo->charCount);
    free(appInfo->rowCur);
    free(appInfo->colCur);
    free(appInfo->charCur);
}
void prepLocationAndPassword(struct AppInfo   *appInfo , int num) {
    appInfo->isPassword = malloc(num * sizeof(bool *));
    appInfo->rowCount =malloc(num * sizeof(int *)) ;
    appInfo->charCount = malloc(num * sizeof(int *))  ;
    appInfo->rowCur =malloc(num * sizeof(int *))  ;
    appInfo->colCur =malloc(num * sizeof(int *))  ;
    appInfo->charCur =malloc(num * sizeof(int *))  ;
    for (int i =0; i <  num;i++){
        appInfo->isPassword[i] = malloc(sizeof(bool));
        appInfo->rowCount[i] =malloc(sizeof(int)) ;
        appInfo->charCount[i] = malloc(sizeof(int)) ;
        appInfo->rowCur[i] =malloc(sizeof(int)) ;
        appInfo->colCur[i] =malloc(sizeof(int)) ;
        appInfo->charCur[i] =malloc(sizeof(int)) ;
        *appInfo->rowCount[i] =0 ;
        *appInfo->charCount[i] = 0 ;
        *appInfo->rowCur[i] =0 ;
        *appInfo->colCur[i] =0 ;
        *appInfo->charCur[i] =0 ;
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
    appInfo->field2 = malloc((appInfo->numberOfFields + 1) * sizeof(FIELD *));
//mvprintw(14, 10, "Value 1:");
	refresh();
    for (int i =0; i < appInfo->numberOfFields;i++){
        if(i % 3 == 1 ){
            appInfo->field2[i] = new_field(  appInfo->numberOfRows , appInfo->fieldSize - 41 ,   (i / 3) * 2 , 2, 0, 0);
            field_opts_off(appInfo->field2[i], O_ACTIVE);
            set_field_buffer(appInfo->field2[i], 0, appInfo->labels[( i / 3) ]);
            if(appInfo->str!=NULL){
                appInfo->str[( i / 3)] = "";
            }
        }
        else if(i % 3 ==2 ){
            appInfo->field2[i] = new_field(  appInfo->numberOfRows , appInfo->fieldSize - 47 ,     ( i / 3) * 2  , 63, 0, 0);
        }
        else{
            *appInfo->rowCount[i/3] = 1;
            *appInfo->charCount[i/3] = 0;
            *appInfo->rowCur[i/3] = 1;
            *appInfo->colCur[i/3] = 1;
            *appInfo->charCur[i/3] = 1;
            appInfo->field2[i] = new_field(  appInfo->numberOfRows , appInfo->fieldSize,    ( i  / 3 ) * 2 , appInfo->fieldXPosition, 0, 0);
            set_field_fore(appInfo->field2[i], COLOR_PAIR(5));/* Put the field with blue background */
            set_field_back(appInfo->field2[i], COLOR_PAIR(5));/* and white foreground (characters */
//            if(*appInfo->isPassword[i/3]){
//              //  field_opts_off(appInfo->field2[i], O_PUBLIC);
//            }
//            else{
//                field_opts_on(appInfo->field2[i], O_PUBLIC);
//            }
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
	wattron(appInfo->win, COLOR_PAIR(1));
//	mvwprintw(appInfo->win, 2, 3, "%s", "Value 1:");
	wattroff(appInfo->win, COLOR_PAIR(1));
	refresh();
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
	if(win == NULL){
		win = stdscr;
	}
	getyx(win, y, x);
	if(startx != 0){
		x = startx;
    }
	if(starty != 0){
		y = starty;
	}
	if(width == 0){
		width = 80;
	}
	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	x = 2;
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

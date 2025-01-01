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


#include <ncurses.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int main()
{

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

    struct AppInfo appInfo;

	int queryFieldSize = 20;
	FIELD *field[2];
    field[0] = new_field(5, queryFieldSize, 6, 20, 0, 0);
    field[1] = NULL;
	FORM  *my_form = new_form(field);

    appInfo.queryString = "";
    queryPanel(my_form       , field      , queryFieldSize, &appInfo.queryString);



//    mvprintw(15, 0, "string: %s   ",appInfo.queryString );
//    getch();

	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	endwin();
    return 0;
}

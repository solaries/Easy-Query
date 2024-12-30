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
#include <form.h>


#include <ncurses.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>


static void getCoord(int pos,FIELD *field, int* downY,int* downX){
    int temp_x, temp_y;
                    getyx(stdscr,  temp_y,  temp_x);
//    getyx(stdscr, &temp_y, &temp_x);
    *downX = temp_x;
    *downY = temp_y;

                    mvprintw(pos, 0, "after down : %d  %d    "
                    , temp_y
                    , temp_x
                     );


}

static char* trim_whitespaces(char *str)
{
	char *end;

	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}


int main()
{

	FIELD *field[3];
	FORM  *my_form;
	int ch;
	int colSize = 4;
	int rowCount = 1;
	int charCount = 0;
	int rowCur = 1;
	int colCur = 1;
	int charCur = 1;

	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize few color pairs */
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);

	/* Initialize the fields */
//height, width, starty, startx, number of offscreen rows and number of additional working buffers
	field[0] = new_field(1, 10, 4, 18, 0, 0);
	field[1] = new_field(5, colSize, 6, 20, 0, 0);
	field[2] = NULL;

	/* Set field options */
	set_field_fore(field[0], COLOR_PAIR(1));/* Put the field with blue background */
	set_field_back(field[0], COLOR_PAIR(2));/* and white foreground (characters */
						/* are printed in white 	*/
	field_opts_off(field[0], O_AUTOSKIP);  	/* Don't go to next field when this */
						/* Field is filled up 		*/
    field_opts_off(field[1], O_AUTOSKIP);
    //set_field_buffer(field[1],0,"" );
    //set_field_opts(field[1], O_WRAP);
    //field_opts_on(field[1], O_WRAP);

	//field_opts_on(field[1], O_WRAP  );

	set_field_back(field[1], A_UNDERLINE);
	//field_opts_off(field[1], O_AUTOSKIP );

    set_field_opts(field[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE | O_WRAP   );
    //set_field_pad(field[1],3);




	//set_field_buffer(field[1], 0, "ds");


	/* Create the form and post it */
	my_form = new_form(field);
	post_form(my_form);
	refresh();

	set_current_field(my_form, field[0]); /* Set focus to the colored field */
	mvprintw(4, 10, "Value 1:");
	mvprintw(6, 10, "Value 2:");


	//set_field_buffer(field[1], 0, "val1\1");

	mvprintw(LINES - 2, 0, "Use UP, DOWN arrow keys to switch between fields");

    mvprintw(21, 0, "col size: %d ,row count: %d ,char count: %d ,row current: %d ,col Current: %d ,", colSize , rowCount , charCount ,rowCur  , colCur );
	refresh();

//set_field_pad (field[1],'\0');

	/* Loop through to get user requests */
	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	case 9:
				/* Go to next field */
				form_driver(my_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				//form_driver(my_form, REQ_END_LINE);
				break;
            case KEY_DOWN:
                {
                    if(rowCur < rowCount){
                        charCur +=4;
                        rowCur +=1;
                        //rowCur = ((charCur  -1 )/ colSize) + 1 ;
                        if((charCur    )% colSize ==0){
                            colCur = colSize;
                        }
                        else{
                            colCur = ((charCur   ) % colSize)  ;
                        }
                        mvprintw(19, 0, "                                                                                                                          "  );
                        mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                        form_driver(my_form, REQ_NEXT_LINE );
                        for (int i = 1; i < colCur     ;i++){
                            form_driver(my_form, REQ_NEXT_CHAR);
                        }
                    }
                    else{
                        mvprintw(19, 0, "no move down                                                                                                                "  );
                    }

                    form_driver(my_form, '\0');
                }
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				//form_driver(my_form, REQ_END_LINE);
				// mvprintw(20, 0, "Item selected is : %d ", ch);
				break;
			case KEY_UP:
				/* Go to previous field */
				//form_driver(my_form, REQ_PREV_FIELD);
                {
                    if(rowCur > 1){
                        charCur -=4;
                        rowCur -=1;
                        //rowCur = ((charCur  -1 )/ colSize) + 1 ;
                        if((charCur    )% colSize ==0){
                            colCur = colSize;
                        }
                        else{
                            colCur = ((charCur   ) % colSize)  ;
                        }
                        mvprintw(19, 0, "                                                                                                                          "  );
                        mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                        form_driver(my_form, REQ_PREV_LINE );

                        for (int i = 1; i < colCur     ;i++){
                            form_driver(my_form, REQ_NEXT_CHAR);
                        }
                    }
                    else{
                        mvprintw(19, 0, "no move up                                                                                                                "  );
                    }
                    form_driver(my_form, '\0');
                }

				break;
			case KEY_LEFT:
                //form_driver(my_form, REQ_NEW_LINE );
                if(charCur > 1){
                    charCur -=1;
                    rowCur = ((charCur  -1 )/ colSize) + 1 ;
                    if((charCur    )% colSize ==0){
                        colCur = colSize;
                    }
                    else{
                        colCur = ((charCur   ) % colSize)  ;
                    }
                    mvprintw(19, 0, "                                                                                                                          "  );
                    mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                    form_driver(my_form, REQ_PREV_CHAR );
                }
                else{
                    mvprintw(19, 0, "no move back                                                                                                                "  );
                }
                form_driver(my_form, '\0');

				break;
			case KEY_DC:
                form_driver(my_form,  REQ_DEL_CHAR );
				break;
//			case 360:
//                form_driver(my_form, REQ_END_FIELD );
//                //form_driver(my_form, REQ_NEXT_CHAR );
//				break;
			case KEY_RIGHT:

                {
                if(charCur <= charCount){
                    charCur +=1;
                    rowCur = ((charCur  -1 )/ colSize) + 1 ;
                    if((charCur    )% colSize ==0){
                        colCur = colSize;
                    }
                    else{
                        colCur = ((charCur   ) % colSize)  ;
                    }
                    mvprintw(19, 0, "                                                                                                                          "  );
                    mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                    form_driver(my_form, REQ_NEXT_CHAR );
                }
                else{
                    mvprintw(19, 0, "no move forward                                                                                                                "  );
                }
                form_driver(my_form, '\0');
                }
				break;
			case KEY_BACKSPACE:
				/* Go to previous field */
                form_driver(my_form, REQ_DEL_PREV);
				break;
			default:

			{
                    /* If this is a normal character, it gets */
                    /* Printed				  */
                    if((ch >=33 && ch <=126)){
                        charCount +=1;
                        charCur +=1;
                        rowCur = ((charCur -1) / colSize) + 1  ;
                        rowCount = (charCount / colSize) +1  ;
                        if((charCur   )% colSize ==0){
                            colCur = colSize;
                        }
                        else{
                            colCur = ((charCur ) % colSize)  ;
                        }
                    }
                    mvprintw(20, 0, "Item selected is : %d ", ch);
                    mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                    //if(ch == 263){
                        //mvprintw(20, 0, "Item selected is : %d ", ch);
                     //               form_driver(my_form, REQ_DEL_PREV);
                    //}
                    //else{
                    form_driver(my_form, ch);

                    //}

			}
				break;
		}
	}

	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]);

	endwin();
    return 0;
}

#include "Query.h"
#include "Field.h"
#include <form.h>
#include <panel.h>

//#include <pthread.h>
#include "FieldInfo.h"


void querySetup( WINDOW *my_query_form_win,FORM  *my_form,FIELD** field, int theColSize, char *queryString[]){
    //struct FieldInfo queryField;
    *queryString = "XX 3 XXX";
    *queryString = "DD";

//    queryField.colSize = theColSize;
//    queryField.rowCount = 1;
//    queryField.charCount = 0;
//    queryField.rowCur = 1;
//    queryField.colCur = 1;
//    queryField.charCur = 1;





	//set_field_back(field[0], A_UNDERLINE);
    field_opts_off(field[0], O_AUTOSKIP);
    set_field_opts(field[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE | O_WRAP   );

    post_form(my_form);
	wrefresh(my_query_form_win);
//    form_driver(my_form, '\0');

//update_panels();
//doupdate();

//    refresh();
    set_current_field(my_form, field[0]);
    //mvprintw(5, 2, "Q");
//    form_driver(my_form, '\0');
    refresh();


    manageField(  my_query_form_win, my_form, field,   theColSize,   queryString );

}

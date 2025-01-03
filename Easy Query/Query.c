#include "Query.h"
#include "Field.h"
#include <form.h>

//#include <pthread.h>
#include "FieldInfo.h"


void queryPanel(FORM  *my_form,FIELD** field, int theColSize, char *queryString[]){
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
    refresh();
    set_current_field(my_form, field[0]);
    mvprintw(6, 10, "Query :");
    form_driver(my_form, '\0');
    refresh();


    manageField( my_form, field,   theColSize,   queryString );

}

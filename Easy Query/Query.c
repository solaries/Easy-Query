#include "Query.h"
#include "Field.h"
#include <form.h>
#include <panel.h>

//#include <pthread.h>
#include "FieldInfo.h"


//void querySetup(PANEL *queryPanel, WINDOW *my_query_form_win,FORM  *my_form,FIELD** field, int theColSize, char *queryString[]){
void querySetup(struct AppInfo   *appInfo){
    //struct FieldInfo queryField;
//    appInfo->str= "XX 3 XXX";
//    appInfo->str = "DD";

//    queryField.colSize = theColSize;
//    queryField.rowCount = 1;
//    queryField.charCount = 0;
//    queryField.rowCur = 1;
//    queryField.colCur = 1;
//    queryField.charCur = 1;





	//set_field_back(field[0], A_UNDERLINE);
    field_opts_off(appInfo->field[0], O_AUTOSKIP);
    set_field_opts(appInfo->field[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE | O_WRAP   );

    post_form(appInfo->form);
	wrefresh(appInfo->win);
//    form_driver(my_form, '\0');

//update_panels();
//doupdate();

//    refresh();
    set_current_field(appInfo->form, appInfo->field[0]);
    //mvprintw(5, 2, "Q");
//    form_driver(my_form, '\0');
//    refresh();


//    manageQueryField( queryPanel, my_query_form_win, my_form, field,   theColSize,   queryString );
    setupQueryField( appInfo);

//        mvprintw(1, 0, " '%p'  ",  appInfo );
//    mvprintw(2, 0, " '%p'  ", *appInfo );
//    mvprintw(3, 0, " '%p'  ", *appInfo );


    //manageQueryField( appInfo);

}



int manageQuery(struct AppInfo   *appInfo){
    int ch;
//    appInfo->str= "XX 3 XXX";
//    appInfo->str = "DD";
    set_current_field(appInfo->form, appInfo->field[0]);

//    set_field_buffer(appInfo->field[0], 0, appInfo->str);

    while((ch = manageQueryField( appInfo)) !=0)
    {	switch(ch)
        {
            case 9  :
                { //tab
//                    return ch;
                }
                break;

            case 27  :
                { //esc
//                    return ch;
                }
                break;


            case 5  :
                { //ctrl + E
                    return ch;
                }
                break;

            case 23  :
                { //ctrl + W - for menu
                    return ch;
                }
                break;

            case 17  :
                { //ctrl + Q
//                    return ch;
                }
                break;


            case 18  :
                { //ctrl + R
                    return ch;
                }
                break;


            case 24  :
                { //ctrl + x
                    return ch;
                }
                break;
            default:

                {

                }
                break;
        }
    }

    return 0;
}





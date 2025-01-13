#include "Query.h"
#include "Field.h"
#include <form.h>
#include <panel.h>

//#include <pthread.h>
#include "FieldInfo.h"

void querySetup(struct AppInfo   *appInfo){
	//set_field_back(field[0], A_UNDERLINE);
    field_opts_off(appInfo->field2[0], O_AUTOSKIP);
    set_field_opts(appInfo->field2[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE | O_WRAP   );

    post_form(appInfo->form);
	wrefresh(appInfo->win);
    set_current_field(appInfo->form, appInfo->field2[0]);
    setupQueryField( appInfo);
}



int manageQuery(struct AppInfo   *appInfo){
    int ch;
    set_current_field(appInfo->form, appInfo->field2[0]);


//    mvprintw(22, 0, "Ctrl + Q or ESC: Query,  Ctrl + E : Execute,   Ctrl + R: Result" );
    mvprintw(22, 0, "Ctrl + E : Execute,   Ctrl + R: Result                            " );
//    mvprintw(23, 0, "Ctrl + W: Menu,  Alt + X: Exit, Space: toggle Select" );
    mvprintw(23, 0, "Ctrl + W: Menu,  Alt + X: Exit                                    " );




    while((ch = manageQueryField( appInfo)) !=0)
    {	switch(ch)
        {
//            case 9  :
//                { //tab
////                    return ch;
//                }
//                break;

//            case 27  :
//                { //esc
////                    return ch;
//                }
//                break;
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
//            case 17  :
//                { //ctrl + Q
////                    return ch;
//                }
//                break;
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





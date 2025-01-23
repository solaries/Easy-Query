#include "Message.h"
#include "Field.h"
#include <form.h>
#include <panel.h>

//#include <pthread.h>
#include "FieldInfo.h"

void messageSetup(struct AppInfo   *appInfo){
	//set_field_back(field[0], A_UNDERLINE);
    field_opts_off(appInfo->field2[0], O_AUTOSKIP | O_WRAP  );
    set_field_opts(appInfo->field2[0], O_VISIBLE  | O_PUBLIC );






    post_form(appInfo->form);
	wrefresh(appInfo->win);
    set_current_field(appInfo->form, appInfo->field2[0]);
    setupQueryField( appInfo);
}



int manageMessage(struct AppInfo   *appInfo,char* info){
    int ch;
//    char* info = trim_whitespaces(appInfo->str[0]);
    set_field_buffer(appInfo->field2[0], 0,  info  );
//    set_current_field(appInfo->form, appInfo->field2[0]);


//    mvprintw(22, 0, "Ctrl + Q or ESC: Query,  Ctrl + E : Execute,   Ctrl + R: Result" );
    mvprintw(22, 0, "ESC 1: Query                                                         " );
//    mvprintw(23, 0, "Ctrl + W: Menu,  Alt + X: Exit, Space: toggle Select" );
    mvprintw(23, 0, "                                                                   " );
    mvprintw(21, 0, "                                                                   " );



        form_driver(appInfo->form, REQ_END_FIELD);

        form_driver(appInfo->form, REQ_NEXT_CHAR);
        form_driver(appInfo->form, REQ_NEXT_CHAR);
        form_driver(appInfo->form, REQ_NEXT_CHAR);
        form_driver(appInfo->form, REQ_NEXT_CHAR);

    refresh();

//    while((ch = manageQueryField( appInfo)) !=0)
    while((ch =  wgetch(appInfo->win)  ) !=0)
    {	switch(ch)
        {
//            case 9  :
//                { //tab
////                    return ch;
//                }
//                break;

            case 27  :
                { //esc
                    return ch;
                }
                break;
//            case 5  :
//                { //ctrl + E
//                    return ch;
//                }
//                break;

//            case 23  :
//                { //ctrl + W - for menu
//                    return ch;
//                }
//                break;
//            case 17  :
//                { //ctrl + Q
////                    return ch;
//                }
//                break;
//            case 18  :
//                { //ctrl + R
//                    return ch;
//                }
//                break;
//            case 24  :
//                { //ctrl + x
//                    return ch;
//                }
//                break;
//            case 248  :
//                { //alt + x
//                    return ch;
//                }
//                break;
            default:
                {

                }
                break;
        }
    }

    return 0;
}





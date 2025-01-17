#include "Server_Connection.h"


#include "Field.h"
#include <form.h>
#include <panel.h>

//#include <pthread.h>
#include "FieldInfo.h"



void serverConnectionSetup(struct AppInfo   *appInfo){
	//set_field_back(field[0], A_UNDERLINE);



    for (int i =0; i < appInfo->numberOfFields;i++){
//        appInfo->field2[i] = new_field(  appInfo->numberOfRows , appInfo->fieldSize, 1, 1, 0, 0);
        if(i % 3 == 1 ){
//            appInfo->field2[i] = new_field(  appInfo->numberOfRows , appInfo->fieldSize - 41 ,   (i / 3) * 2 , 2, 0, 0);
            field_opts_off(appInfo->field2[i], O_ACTIVE);
//            set_field_buffer(appInfo->field2[i], 0, appInfo->labels[( i / 3) ]);
        }
        else if(i % 3 ==2 ){
            //appInfo->field2[i] = new_field(  appInfo->numberOfRows , appInfo->fieldSize - 47 ,     ( i / 3) * 2  , 63, 0, 0);
            field_opts_off(appInfo->field2[i], O_ACTIVE);
        }
        else{
//            appInfo->field2[i] = new_field(  appInfo->numberOfRows , appInfo->fieldSize,    ( i  / 3 ) * 2 , appInfo->fieldXPosition, 0, 0);
//            set_field_fore(appInfo->field2[i], COLOR_PAIR(5));/* Put the field with blue background */
//            set_field_back(appInfo->field2[i], COLOR_PAIR(5));/* and white foreground (characters */
            field_opts_off(appInfo->field2[i], O_AUTOSKIP);
            set_field_opts(appInfo->field2[i], O_VISIBLE  | O_EDIT | O_ACTIVE | O_STATIC );


            if(*appInfo->isPassword[i/3]){
                field_opts_off(appInfo->field2[i], O_PUBLIC);
            }
            else{
                field_opts_on(appInfo->field2[i], O_PUBLIC);
            }
        }
    }
    post_form(appInfo->form);
	wrefresh(appInfo->win);
    set_current_field(appInfo->form, appInfo->field2[0]);
    setupQueryField( appInfo);
}



int manageServerConnection(struct AppInfo   *appInfo){
    int ch;
    set_current_field(appInfo->form, appInfo->field2[0]);


//    mvprintw(22, 0, "Ctrl + Q or ESC: Query,  Ctrl + E : Execute,   Ctrl + R: Result" );
    mvprintw(22, 0, "ESC : Close Dailog and return to query                            " );
//    mvprintw(23, 0, "Ctrl + W: Menu,  Alt + X: Exit, Space: toggle Select" );
    mvprintw(23, 0, "UP or Shift + Tab: UP, Down or Tab: Down                                                " );


	box(appInfo->win, 0, 0);

	wrefresh(appInfo->win);


    while((ch = manageQueryField( appInfo)) !=0)
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
            case 5  :
                { //ctrl + E
//                    return ch;
                }
                break;

            case 23  :
                { //ctrl + W - for menu
//                    return ch;
                }
                break;
//            case 17  :
//                { //ctrl + Q
////                    return ch;
//                }
//                break;
            case 18  :
                { //ctrl + R
//                    return ch;
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

    return 0;
}




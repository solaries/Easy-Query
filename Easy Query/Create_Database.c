#include "Create_Database.h"

#include "Field.h"
#include <form.h>
#include <panel.h>

//#include <pthread.h>
#include "FieldInfo.h"


void createDatabaseSetup(struct AppInfo   *appInfo){
	//set_field_back(field[0], A_UNDERLINE);



    for (int i =0; i < appInfo->numberOfFields;i++){
        if(i % 3 == 1 ){
            field_opts_off(appInfo->field2[i], O_ACTIVE);
        }
        else if(i % 3 ==2 ){
            field_opts_off(appInfo->field2[i], O_ACTIVE);
        }
        else{
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


  field_opts_off(appInfo->field2[3], O_ACTIVE);
  field_opts_off(appInfo->field2[6], O_ACTIVE);
    if(appInfo->isCreateDB){
//      field_opts_off(appInfo->field2[6], O_VISIBLE);
//      field_opts_off(appInfo->field2[7], O_VISIBLE);
//      field_opts_off(appInfo->field2[8], O_VISIBLE);
//      field_opts_off(appInfo->field2[3], O_ACTIVE);
//      field_opts_off(appInfo->field2[6], O_ACTIVE);
    }


    post_form(appInfo->form);
	wrefresh(appInfo->win);
    set_current_field(appInfo->form, appInfo->field2[0]);
    setupQueryField( appInfo);
}



int manageCreateDatabase(struct AppInfo   *appInfo , struct AppInfo   *config   ){
    int ch;
    set_current_field(appInfo->form, appInfo->field2[0]);


//    mvprintw(22, 0, "Ctrl + Q or ESC: Query,  Ctrl + E : Execute,   Ctrl + R: Result" );
    mvprintw(22, 0, "Ctrl + E : Execute, ESC : Close Dailog and return to query                            " );
//    mvprintw(23, 0, "Ctrl + W: Menu,  Alt + X: Exit, Space: toggle Select" );
    mvprintw(23, 0, "                                                                                        " );
//    mvprintw(23, 0, "UP or Shift + Tab: UP, Down or Tab: Down                                                " );


	box(appInfo->win, 0, 0);

	wrefresh(appInfo->win);


    while((ch = manageQueryField( appInfo)) !=0)
    {	switch(ch)
        {
            case 27  :
                { //esc
                    return ch;
                }
                break;
            case 5  :
                { //ctrl + E
                    return 55555;
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




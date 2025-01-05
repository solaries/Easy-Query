#include "Result_Text_Or_Cells.h"

#include "FieldInfo.h"
#include <form.h>
#include <panel.h>
#include "Field.h"




void resultSetup(struct AppInfo   *appInfo){
//    appInfo->str= "XX 3 XXX";
//    appInfo->str = "DD";
    field_opts_off(appInfo->field[0], O_AUTOSKIP| O_EDIT );
    set_field_opts(appInfo->field[0], O_VISIBLE | O_PUBLIC | O_ACTIVE | O_WRAP   );

    post_form(appInfo->form);
	wrefresh(appInfo->win);

    set_current_field(appInfo->form, appInfo->field[0]);
    setupQueryField( appInfo);

}



int manageResult(struct AppInfo   *appInfo){
    int ch;
    appInfo->str= "XX 3 XXX";
    appInfo->str = "DD";
    set_field_buffer(appInfo->field[0], 0, appInfo->str);
    set_current_field(appInfo->form, appInfo->field[0]);
//    return ( appInfo);



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
                    return ch;
                }
                break;

            case 17  :
                { //ctrl + Q
                    return ch;
                }
                break;


            case 18  :
                { //ctrl + R
//                    return ch;
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




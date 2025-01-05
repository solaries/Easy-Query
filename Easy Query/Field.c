#include "Field.h"
#include "FieldInfo.h"
#include <form.h>
#include <panel.h>


//void manageQueryField( PANEL *queryPanel, WINDOW *my_form_win, FORM  *my_form,FIELD** field, int theColSize, char *queryString[]){




void setupQueryField( struct AppInfo   *appInfo){

//    int ch;

    int colSize = appInfo->fieldSize ;// theColSize;
    int rowCount = 1;
    int charCount = 0;
    int rowCur = 1;
    int colCur = 1;
//    int charCur = 1;



    mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );
    mvprintw(22, 0, "Alt + Q or ESC: Query,  Alt + E : Execute,   Alt + R: Result" );
    mvprintw(23, 0, "Alt + M: Menu,  Alt + X: Exit" );
    refresh();
    set_current_field(appInfo->form, appInfo->field[0]); /* Set focus to the colored field */
    form_driver(appInfo->form, '\0');


}




int manageQueryField( struct AppInfo   *appInfo){

    int ch;

    int colSize = appInfo->fieldSize ;// theColSize;
    int rowCount = 1;
    int charCount = 0;
    int rowCur = 1;
    int colCur = 1;
    int charCur = 1;



    mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );
    mvprintw(22, 0, "Alt + Q or ESC: Query,  Alt + E : Execute,   Alt + R: Result" );
    mvprintw(23, 0, "Alt + M: Menu,  Alt + X: Exit, Space: toggle Select" );
    refresh();
set_current_field(appInfo->form, appInfo->field[0]); /* Set focus to the colored field */
    form_driver(appInfo->form, '\0');


    int countt = 0;
    while((ch = wgetch(appInfo->win)) != 0)
    {	switch(ch)
        {
            case 9  :
                { //tab
                    return ch;
                }
                break;

            case 27  :
                { //esc
                    return ch;
                }
                break;

            case 229  :
                { //alt + E
                    return ch;
                }
                break;

            case 237  :
                { //alt + M
                    return ch;
                }
                break;

            case 241  :
                { //alt + Q
                    return ch;
                }
                break;

            case 242  :
                { //alt + R
                    return ch;
                }
                break;

            case 248  :
                { //alt + x
                    return ch;
                }
                break;

            case KEY_DOWN:
                {
                    if(rowCur < rowCount){
                        for(int i = 1; i <=colSize; i++){
                            if(charCur   <=charCount){
                                charCur +=1;
                            }
                        }
                        rowCur +=1;
                        if((charCur    )% colSize ==0){
                            colCur = colSize;
                        }
                        else{
                            colCur = ((charCur   ) % colSize)  ;
                        }
                        mvprintw(19, 0, "                                                                                                                          "  );
                        mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );
                        form_driver(appInfo->form, REQ_NEXT_LINE );
                        for (int i = 1; i < colCur     ;i++){
                            form_driver(appInfo->form, REQ_NEXT_CHAR);
                        }
                    }


                    mvprintw(23, 75, "%d", ch);
    refresh();
                }
                break;



            case KEY_UP:
                {
                    if(rowCur > 1){
                        charCur -=colSize;
                        rowCur -=1;
                        if((charCur    )% colSize ==0){
                            colCur = colSize;
                        }
                        else{
                            colCur = ((charCur   ) % colSize)  ;
                        }
                        mvprintw(19, 0, "                                                                                                                          "  );
                        mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );
                        form_driver(appInfo->form, REQ_PREV_LINE );
                        for (int i = 1; i < colCur     ;i++){
                            form_driver(appInfo->form, REQ_NEXT_CHAR);
                        }
                    }


                    mvprintw(23, 75, "%d", ch);

    refresh();
                }
                break;
            case KEY_LEFT:
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
                    mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );
                    form_driver(appInfo->form, REQ_PREV_CHAR );
                }

                    mvprintw(23, 75, "%d", ch);

    refresh();
                break;
            case KEY_DC:

                {
                    if(charCur -1 < charCount && charCur >= 1){
                        form_driver(appInfo->form, REQ_VALIDATION);
                        char * theTextCurrent= field_buffer(appInfo->field[0], 0) ;
                        char theText[charCount   -1];
                        int j =0;
                        for(int i =0;i < charCount+1;i++){
                            if(i==charCur-1){
                                j++;
                            }
                            else{
                            }
                            theText[i] = theTextCurrent[j];
                            j++;
                        }
                        charCur++;
                        theText[charCount -1  ] = '\0';
                        set_field_buffer(appInfo->field[0], 0, theText);
                        charCount -=1;
                        charCur -=1;
                        rowCur = ((charCur -1) / colSize) + 1  ;
                        rowCount = (charCount / colSize) +1  ;
                        if((charCur   )% colSize ==0){
                            colCur = colSize;
                        }
                        else{
                            colCur = ((charCur ) % colSize);
                        }
                        for (int i = 1; i < rowCur;i++){
                            form_driver(appInfo->form, REQ_NEXT_LINE);
                        }
                        for (int i = 1; i < colCur  ;i++){
                            form_driver(appInfo->form, REQ_NEXT_CHAR);
                        }
                    }

                    mvprintw(23, 75, "%d", ch);
                    mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );

    refresh();
                }
                break;
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
                        mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );
                        form_driver(appInfo->form, REQ_NEXT_CHAR );
                    }

                    mvprintw(23, 75, "%d", ch);

    refresh();
                }
                break;
            case 10:
                {
                    form_driver(appInfo->form, REQ_VALIDATION);
                    int extraChar = colSize -    colCur;
                    char * theTextCurrent= field_buffer(appInfo->field[0], 0) ;
                    char theText[charCount   + extraChar + 1];
                    int j =0;
                    for(int i =0;i <= charCount   + extraChar +1;i++){
                        if(i==charCur-1){
                            for(int k=0; k <= extraChar; k++ ){
                                theText[i] =32;
                                i++;
                            }
                        }
                        else{
                        }
                        theText[i] = theTextCurrent[j];
                        j++;
                    }
                    theText[charCount + extraChar + 1  ] = '\0';
                    set_field_buffer(appInfo->field[0], 0, theText);
                    charCount +=1  + extraChar;
                    charCur +=1  + extraChar;
                    rowCur = ((charCur -1) / colSize) + 1  ;
                    rowCount = (charCount / colSize) +1  ;
                    if((charCur   )% colSize ==0){
                        colCur = colSize;
                    }
                    else{
                        colCur = ((charCur ) % colSize);
                    }
                    for (int i = 1; i < rowCur;i++){
                        form_driver(appInfo->form, REQ_NEXT_LINE);
                    }
                    for (int i = 1; i < colCur;i++){
                        form_driver(appInfo->form, REQ_NEXT_CHAR);
                    }
                    form_driver(appInfo->form, REQ_VALIDATION);

                    mvprintw(23, 75, "%d", ch);


                    mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );

    refresh();
                }
                break;
            case KEY_BACKSPACE:
                {
                    if(charCur -2 < charCount && charCur >= 2){
                        form_driver(appInfo->form, REQ_VALIDATION);
                        char * theTextCurrent= field_buffer(appInfo->field[0], 0) ;
                        char theText[charCount   -1];
                        int j =0;
                        for(int i =0;i < charCount+1;i++){
                            if(i==charCur-2){
                                j++;
                            }
                            theText[i] = theTextCurrent[j];
                            j++;
                        }
                        theText[charCount -1  ] = '\0';
                        set_field_buffer(appInfo->field[0], 0, theText);
                        charCount -=1;
                        charCur -=1;
                        rowCur = ((charCur -1) / colSize) + 1  ;
                        rowCount = (charCount / colSize) +1  ;
                        if((charCur   )% colSize ==0){
                            colCur = colSize;
                        }
                        else{
                            colCur = ((charCur ) % colSize);
                        }
                        for (int i = 1; i < rowCur;i++){
                            form_driver(appInfo->form, REQ_NEXT_LINE);
                        }
                        for (int i = 1; i < colCur;i++){
                            form_driver(appInfo->form, REQ_NEXT_CHAR);
                        }
                    }

                    mvprintw(23, 75, "%d", ch);
                    mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );

    refresh();
                }
                break;
            default:

                {
                    if((ch >=32 && ch <=126)){
                        bool doMovenext = false;
                        if(charCur < charCount){
                            doMovenext = true;
                            form_driver(appInfo->form, REQ_VALIDATION);
                            char * theTextCurrent= field_buffer(appInfo->field[0], 0) ;
                            char theText[charCount  + 2];
                            int j =0;
                            for(int i =0;i < charCount+1;i++){
                                if(i==charCur-1){
                                    theText[i] = ch;
                                    countt++;
                                    i++;
                                }
                                theText[i] = theTextCurrent[j];
                                j++;
                            }
                            theText[charCount +1  ] = '\0';
                            set_field_buffer(appInfo->field[0], 0, theText);
                            for (int i = 1; i < rowCur     ;i++){
                                form_driver(appInfo->form, REQ_NEXT_LINE);
                            }
                            for (int i = 1; i < colCur     ;i++){
                                form_driver(appInfo->form, REQ_NEXT_CHAR);
                            }
                            mvprintw(19, 0, "-   ", theTextCurrent);
                        }
                        charCount +=1;
                        charCur +=1;
                        rowCur = ((charCur -1) / colSize) + 1  ;
                        rowCount = (charCount / colSize) +1  ;
                        if((charCur   )% colSize ==0){
                            colCur = colSize;
                        }
                        else{
                            colCur = ((charCur ) % colSize);
                        }
                        if(doMovenext){
                            form_driver(appInfo->form, REQ_NEXT_CHAR );
                        }
                        else{
                            form_driver(appInfo->form, ch);
                        }
                    }




                    mvprintw(23, 75, "%d", ch);
                    mvprintw(21, 0, "c size: %d ,r count: %d ,char count: %d ,row cur: %d ,col Cur: %d ", colSize , rowCount , charCount ,rowCur  , colCur );


    refresh();
//                    form_driver(my_form, '\0');
                }
                break;
        }

                   form_driver(appInfo->form, '\0');

    }

return 0;

}


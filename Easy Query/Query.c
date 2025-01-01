#include "Query.h"

#include <form.h>
#include "FieldInfo.h"


void queryPanel(FORM  *my_form,FIELD** field, int theColSize, char *queryString[]){
    int ch;
    struct FieldInfo queryField;

    *queryString = "XX 3 XXX";

    *queryString = "DD";

    queryField.colSize = theColSize;
    queryField.rowCount = 1;
    queryField.charCount = 0;
    queryField.rowCur = 1;
    queryField.colCur = 1;
    queryField.charCur = 1;

    int colSize = queryField.colSize ;
    int rowCount = queryField.rowCount ;
    int charCount = queryField.charCount ;
    int rowCur = queryField.rowCur ;
    int colCur = queryField.colCur ;
    int charCur = queryField.charCur ;



	//set_field_back(field[0], A_UNDERLINE);
    field_opts_off(field[0], O_AUTOSKIP);
    set_field_opts(field[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE | O_WRAP   );
    post_form(my_form);
    refresh();
    set_current_field(my_form, field[0]);
    mvprintw(6, 10, "Query :");
    mvprintw(21, 0, "col size: %d ,row count: %d ,char count: %d ,row current: %d ,col Current: %d ", colSize , rowCount , charCount ,rowCur  , colCur );
    form_driver(my_form, '\0');
    refresh();






    //set_field_buffer(field[0], 0, "mmmm");

    int countt = 0;
    while((ch = getch()) != KEY_F(1))
    {	switch(ch)
        {
            case KEY_DOWN:
                {
                    if(rowCur < rowCount){
                        for(int i = 1; i <=4; i++){
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
                        mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                        form_driver(my_form, REQ_NEXT_LINE );
                        for (int i = 1; i < colCur     ;i++){
                            form_driver(my_form, REQ_NEXT_CHAR);
                        }
                    }
                    form_driver(my_form, '\0');
                }
                break;
            case KEY_UP:
                {
                    if(rowCur > 1){
                        charCur -=4;
                        rowCur -=1;
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
                    form_driver(my_form, '\0');
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
                    mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                    form_driver(my_form, REQ_PREV_CHAR );
                }
                form_driver(my_form, '\0');
                break;
            case KEY_DC:

                {
                    if(charCur -1 < charCount && charCur >= 1){
                        form_driver(my_form, REQ_VALIDATION);
                        char * theTextCurrent= field_buffer(field[0], 0) ;
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
                        set_field_buffer(field[1], 0, theText);
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
                            form_driver(my_form, REQ_NEXT_LINE);
                        }
                        for (int i = 1; i < colCur  ;i++){
                            form_driver(my_form, REQ_NEXT_CHAR);
                        }
                    }
                    mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                    form_driver(my_form, 0);
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
                        mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                        form_driver(my_form, REQ_NEXT_CHAR );
                    }
                    form_driver(my_form, '\0');
                }
                break;
            case 10:
                {
                    form_driver(my_form, REQ_VALIDATION);
                    int extraChar = colSize -    colCur;
                    char * theTextCurrent= field_buffer(field[0], 0) ;
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
                    set_field_buffer(field[0], 0, theText);
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
                        form_driver(my_form, REQ_NEXT_LINE);
                    }
                    for (int i = 1; i < colCur;i++){
                        form_driver(my_form, REQ_NEXT_CHAR);
                    }
                    form_driver(my_form, REQ_VALIDATION);
                    mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                    form_driver(my_form, 0);
                }
                break;
            case KEY_BACKSPACE:
                {
                    if(charCur -2 < charCount && charCur >= 2){
                        form_driver(my_form, REQ_VALIDATION);
                        char * theTextCurrent= field_buffer(field[0], 0) ;
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
                        set_field_buffer(field[0], 0, theText);
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
                            form_driver(my_form, REQ_NEXT_LINE);
                        }
                        for (int i = 1; i < colCur;i++){
                            form_driver(my_form, REQ_NEXT_CHAR);
                        }
                    }
                    mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d ,",   rowCount , charCount ,rowCur  , colCur,charCur );
                    form_driver(my_form, 0);
                }
                break;
            default:

                {
                    if((ch >=32 && ch <=126)){
                        bool doMovenext = false;
                        if(charCur < charCount){
                            doMovenext = true;
                            form_driver(my_form, REQ_VALIDATION);
                            char * theTextCurrent= field_buffer(field[0], 0) ;
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
                            set_field_buffer(field[0], 0, theText);
                            for (int i = 1; i < rowCur     ;i++){
                                form_driver(my_form, REQ_NEXT_LINE);
                            }
                            for (int i = 1; i < colCur     ;i++){
                                form_driver(my_form, REQ_NEXT_CHAR);
                            }
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
                            form_driver(my_form, REQ_NEXT_CHAR );
                        }
                        else{
                            form_driver(my_form, ch);
                        }
                    }
                    mvprintw(20, 0, "Item selected is : %d ", ch);
                    mvprintw(21, 0, " row count: %d ,char count: %d ,row current: %d ,col Current: %d ,char Current: %d , ",   rowCount , charCount ,rowCur  , colCur,charCur );
                    form_driver(my_form, '\0');
                }
                break;
        }
    }




}

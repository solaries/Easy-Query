#include <panel.h>
#include <form.h>

#ifndef FIELDINFO_H_INCLUDED
#define FIELDINFO_H_INCLUDED


struct AppInfo {
	PANEL *panel;
	WINDOW *win;
	FORM  *form;

	FIELD **field2;

    int numberOfFields ;
    int numberOfRows ;
    int fieldXPosition ;
    int windXPosition ;

//	FIELD *field[2] ;
	int fieldSize;
	char *str  ;



    int rowCount ;
    int charCount  ;
    int rowCur  ;
    int colCur  ;
    int charCur ;


	FIELD **multiField ;
	char *strMsg  ;


	bool msg;
};


#endif // FIELDINFO_H_INCLUDED


//struct FieldInfo {
//	int colSize ;
//	int rowCount ;
//	int charCount ;
//	int rowCur ;
//	int colCur ;
//	int charCur ;
//};




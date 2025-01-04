#include <panel.h>
#include <form.h>

#ifndef FIELDINFO_H_INCLUDED
#define FIELDINFO_H_INCLUDED


struct AppInfo {
	PANEL *panel;
	WINDOW *win;
	FORM  *form;
	FIELD *field[2] ;
	int fieldSize;
	char *str  ;


	FIELD *multiField[1][1] ;
	char *strMsg  ;
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




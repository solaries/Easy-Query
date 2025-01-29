
#include "FieldInfo.h"

#ifndef DB_COM_H_INCLUDED
#define DB_COM_H_INCLUDED

//char*  createDatabase(char *server,  char *user, char *password, char *database ) ;
//char*  connectDatabase(char *server,  char *user, char *password, char *database ) ;
char*  createDatabase(struct AppInfo *appInfo) ;
char*  connectDatabase(struct AppInfo *appInfo ) ;
char*  getDatabases(struct AppInfo *appInfo ) ;
#endif // DB_COM_H_INCLUDED

#include <form.h>
#include <panel.h>
#include "FieldInfo.h"


#ifndef SERVER_CONNECTION_H_INCLUDED
#define SERVER_CONNECTION_H_INCLUDED


//serverConnection
    void serverConnectionSetup( struct AppInfo *appInfo);
    int serverConnectionQuery( struct AppInfo *appInfo);



#endif // SERVER_CONNECTION_H_INCLUDED

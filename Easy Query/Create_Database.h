#include <form.h>
#include <panel.h>
#include "FieldInfo.h"


#ifndef CREATE_DATABASE_H_INCLUDED
#define CREATE_DATABASE_H_INCLUDED




    void createDatabaseSetup( struct AppInfo *appInfo);
    int manageCreateDatabase( struct AppInfo *appInfo, struct AppInfo *config);

#endif // CREATE_DATABASE_H_INCLUDED

#include <string.h>
#include <ctype.h>
#include <mysql.h>
#include "DB_com.h"
#include "FieldInfo.h"
//#include <stdio.h>

//char *server1 = "localhost";
//                localhost



//char* createDatabase(char *server,  char *user, char *password, char *database ) {
char* createDatabase(struct AppInfo   *appInfo) {
	MYSQL *conn;
//	MYSQL_RES *res;
//	MYSQL_ROW row;

//	char *server = "localhost";
	char sql[256];

//    int l0 = strlen(trim_whitespaces(server) );
//    int l1= strlen(server1);

//	char *user1 = "root";
//	char *password1 = "lordisjesus"; /* set me first */
//	char *database = "code_joh";


/*


messageInfo.str[0] = connectDatabase(
(&createDatabaseInfo)->str[0] /-char *server-/ ,
(&createDatabaseInfo)->str[1] /-char *user-/ ,
(&createDatabaseInfo)->str[2] /-char *password-/ ,
(&createDatabaseInfo)->str[3] /-char *database-/  );
//                    v = 1;

*/


	conn = mysql_init(NULL);
    char* return_message ;

	/* Connect to database */
//	if (!mysql_real_connect(conn, server, user, password,  database, 0, NULL, 0)) {
	if (!mysql_real_connect(conn,trim_whitespaces( appInfo->str[0]) ,trim_whitespaces(appInfo->str[1]) ,trim_whitespaces(appInfo->str[2]) ,  NULL, 0, NULL, 0)) {
        char error_message[256];
//        char* error_message ;
        strcpy(error_message, mysql_error(conn));
        return_message =  trim_whitespaces(error_message) ;
//        char * err = mysql_error(conn);
		//fprintf(stderr, "%s\n", mysql_error(conn));
		return return_message;
	}

    strcpy(sql , "create database ");
    strcat(sql, trim_whitespaces(trim_whitespaces(appInfo->str[3])) );
    char *sqlExec = trim_whitespaces(sql);

//	/* send SQL query */
	if (mysql_query(conn, sqlExec)) {
//		fprintf(stderr, "%s\n", mysql_error(conn));
//		exit(1);
        char error_message[256];
        strcpy(error_message, mysql_error(conn));
        return_message =  trim_whitespaces(error_message);
        mysql_close(conn);
        return return_message;
	}
//
//	res = mysql_use_result(conn);
//
//	/* output table name */
//	printf("MySQL Tables in mysql database:\n");
//
//	while ((row = mysql_fetch_row(res)) != NULL)
//		printf("%s ** \n", row[0]);
//
//	/* close connection */
//	mysql_free_result(res);
	mysql_close(conn);
    return_message ="Database creation successful";
	return return_message;
}


char* getDatabases(struct AppInfo   *appInfo) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

//	char *server = "localhost";
	char sql[256];

//    int l0 = strlen(trim_whitespaces(server) );
//    int l1= strlen(server1);

//	char *user1 = "root";
//	char *password1 = "lordisjesus"; /* set me first */
//	char *database = "code_joh";


/*


messageInfo.str[0] = connectDatabase(
(&createDatabaseInfo)->str[0] /-char *server-/ ,
(&createDatabaseInfo)->str[1] /-char *user-/ ,
(&createDatabaseInfo)->str[2] /-char *password-/ ,
(&createDatabaseInfo)->str[3] /-char *database-/  );
//                    v = 1;

*/


	conn = mysql_init(NULL);
    char* return_message ;

	/* Connect to database */
//	if (!mysql_real_connect(conn, server, user, password,  database, 0, NULL, 0)) {
	if (!mysql_real_connect(conn,trim_whitespaces( appInfo->str[0]) ,trim_whitespaces(appInfo->str[1]) ,trim_whitespaces(appInfo->str[2]) ,  NULL , 0, NULL, 0)) {
        char error_message[256];
//        char* error_message ;
        strcpy(error_message, mysql_error(conn));
        return_message =  trim_whitespaces(error_message) ;
//        char * err = mysql_error(conn);
		//fprintf(stderr, "%s\n", mysql_error(conn));
		return return_message;
	}

    strcpy(sql , "show databases ");
//    strcat(sql, trim_whitespaces(trim_whitespaces(appInfo->str[3])) );
//    char *sqlExec = trim_whitespaces(sql);

//	/* send SQL query */
//	if (mysql_query(conn, sqlExec)) {
	res = mysql_list_dbs(conn, "") ;

//
//	/* output table name */
//	printf("MySQL Tables in mysql database:\n");
    int numOfRows = mysql_num_rows(res);

    if(appInfo->databases != NULL){
        free(appInfo->databases);
        appInfo->databases = NULL;
    }
    if(numOfRows > 0){
        appInfo->databases =  malloc(numOfRows * sizeof(char *));
        int rowPos = 0;
        while ((row = mysql_fetch_row(res)) != NULL){
           appInfo->databases[rowPos] =  row[0];
           rowPos++;
        }
    }
//	while ((row = mysql_fetch_row(res)) != NULL)
//		printf("%s ** \n", row[0]);
//
//	/* close connection */
//	mysql_free_result(res);
	mysql_close(conn);
    return_message ="Database list successful";
	return return_message;
}




//char* connectDatabase(char *server,  char *user, char *password, char *database ) {
char* connectDatabase(struct AppInfo   *appInfo ) {
	MYSQL *conn;
//	char sql[256];
	conn = mysql_init(NULL);
    char* return_message ;
//	if (!mysql_real_connect(conn,trim_whitespaces(server) ,trim_whitespaces(user) ,trim_whitespaces(password) ,  NULL, 0, NULL, 0)) {
	if (!mysql_real_connect(conn,trim_whitespaces( appInfo->str[0]) ,trim_whitespaces(appInfo->str[1]) ,trim_whitespaces(appInfo->str[2]) ,  trim_whitespaces(appInfo->str[3]), 0, NULL, 0)) {
        char error_message[256];
        strcpy(error_message, mysql_error(conn));
        return_message =  trim_whitespaces(error_message) ;
		return return_message;
	}
	mysql_close(conn);
    return_message ="Database connection successful";
	return return_message;
}




// /home/sphinx/code/c_programs/easy_query/Easy Query/DB_com.c|1|fatal error: mysql.h: No such file or directory|


// sudo apt-get install libmysqlclient-dev

//  gcc -o connect_mysql $(mysql_config --cflags) connect_mysql.c $(mysql_config --libs)





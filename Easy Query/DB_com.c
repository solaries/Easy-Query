#include <string.h>
#include <ctype.h>
#include <mysql.h>
#include "DB_com.h"
#include "FieldInfo.h"
//#include <stdio.h>

//char *server1 = "localhost";
//                localhost



char* createDatabase(char *server,  char *user, char *password, char *database ) {
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

	conn = mysql_init(NULL);
    char* return_message ;

	/* Connect to database */
//	if (!mysql_real_connect(conn, server, user, password,  database, 0, NULL, 0)) {
	if (!mysql_real_connect(conn,trim_whitespaces(server) ,trim_whitespaces(user) ,trim_whitespaces(password) ,  NULL, 0, NULL, 0)) {
        char error_message[256];
//        char* error_message ;
        strcpy(error_message, mysql_error(conn));
        return_message =  trim_whitespaces(error_message) ;
//        char * err = mysql_error(conn);
		//fprintf(stderr, "%s\n", mysql_error(conn));
		return return_message;
	}

    strcpy(sql , "create database ");
    strcat(sql, trim_whitespaces(database) );
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

// /home/sphinx/code/c_programs/easy_query/Easy Query/DB_com.c|1|fatal error: mysql.h: No such file or directory|


// sudo apt-get install libmysqlclient-dev

//  gcc -o connect_mysql $(mysql_config --cflags) connect_mysql.c $(mysql_config --libs)





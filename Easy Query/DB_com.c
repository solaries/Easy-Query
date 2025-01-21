#include <string.h>
#include <ctype.h>
#include <mysql.h>
#include "DB_com.h"
//#include <stdio.h>

//char *server1 = "localhost";
//                localhost


static char* trim_whitespaces(char *str)
{
	char *end;
	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}


int createDatabase(char *server,  char *user, char *password, char *database ) {
	MYSQL *conn;
//	MYSQL_RES *res;
//	MYSQL_ROW row;

//	char *server = "localhost";

//    int l0 = strlen(trim_whitespaces(server) );
//    int l1= strlen(server1);

//	char *user1 = "root";
//	char *password1 = "lordisjesus"; /* set me first */
//	char *database = "code_joh";

	conn = mysql_init(NULL);

	/* Connect to database */
//	if (!mysql_real_connect(conn, server, user, password,  database, 0, NULL, 0)) {
	if (!mysql_real_connect(conn,trim_whitespaces(server) ,trim_whitespaces(user) ,trim_whitespaces(password) ,  NULL, 0, NULL, 0)) {
        char error_message[256];
        strcpy(error_message, mysql_error(conn));
//        char * err = mysql_error(conn);
		//fprintf(stderr, "%s\n", mysql_error(conn));
		return 1;
	}

//	/* send SQL query */
//	if (mysql_query(conn, "show tables")) {
//		fprintf(stderr, "%s\n", mysql_error(conn));
//		exit(1);
//	}
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
	return 0;
}

// /home/sphinx/code/c_programs/easy_query/Easy Query/DB_com.c|1|fatal error: mysql.h: No such file or directory|


// sudo apt-get install libmysqlclient-dev

//  gcc -o connect_mysql $(mysql_config --cflags) connect_mysql.c $(mysql_config --libs)





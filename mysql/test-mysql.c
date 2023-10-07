#include </usr/include/mysql/mysql.h>
#include <stdio.h>

int main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server = "163.10.3.73";
	int port = 33060;
	char *user = "taller2g2";
	char *password = "taller2g2";
	char *database = "taller2";

	conn = mysql_init(NULL);

	if(!mysql_real_connect(conn,server,user,password,database,port,NULL,0)) {
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}

	if(mysql_query(conn,"show tables")) {
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);

	printf("MySQL tables in mysql database:\n");
	while((row = mysql_fetch_row(res)) != NULL)
		printf("%s \n",row[0]);

	mysql_free_result(res);
	mysql_close(conn);
}

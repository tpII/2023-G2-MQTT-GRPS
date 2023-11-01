#include </usr/include/mysql/mysql.h>
#include <stdio.h>

MYSQL_RES* res;

// esta funcion va a imprimir un mensaje de error del sistema sql y
// va a terminar la ejecucion.
void error_stop(MYSQL* conn) {
	fprintf(stderr,"%s\n",mysql_error(conn));
	exit(1);
}

// esta funcion va a ejecutar una consulta a la db especificada en
// la configuracion del main. Si hay errores, informa y termina
// la ejecucion del programa. Si no hay errores, muestra los
// resultados en la pantalla, con un encabezado recibido como
// argumento. El ultimo argumento indica si tengo o no que imprimir
// los resultados. Lo necesito porque sino falla en los casos que
// no haya salida (como insert, delete, etc).
void run_query(MYSQL* conn, char* query, char* header, int rq_res) {

	// intenta realizar una consulta a la db
	// si hubo error, informa y termina el programa
	if (mysql_query(conn, query))
		error_stop(conn);

	// imprimir encabezado
	printf("\n%s\n", header);

	MYSQL_ROW row;

	// imprimir resultados de la consulta
	// en caso de no haber un error y en caso de que la
	// operacion requiera la impresion de un resultado
	if (rq_res) {
		res = mysql_use_result(conn);

		while((row = mysql_fetch_row(res)) != NULL) {
			for(int i=0;i<mysql_num_fields(res);i++)
				printf("%s\t",row[i]);
			printf("\n");
		}
	}
}

int main() {
	MYSQL* conn;

	// el usuario que se vaya a usar tiene que estar asentado en la bd como
	// 'usuario'@'%' para permitir que se conecte desde cualquier host remoto.

	// en el archivo de config de mysql (/etc/mysql/my.cnf) se debe dejar
	// explícitamente el permiso de conexión (bind address) desde 0.0.0.0, es
	// decir, cualquier direccion -> podria ser una falla en la seguridad,
	// pero para trabajar en proyectos alcanza y sobra.

	char* server = "163.10.3.73";
	int port = 3306;
	char* user = "taller2g2";
	char* password = "taller2g2";
	char* database = "taller2";

	conn = mysql_init(NULL);

	if(!mysql_real_connect(conn,server,user,password,database,port,NULL,0))
		error_stop(conn);

	// imprimir la estructura de la tabla MEDIDAS
	run_query(conn, "describe medidas;", "Estructura de la tabla MEDIDAS:",1);

	// listar las tuplas de la tabla MEDIDAS
	run_query(conn, "select * from medidas", "Contenido de la tabla MEDIDAS:",1);

	// insertar la tupla ('1980-01-01 00:00:00',25.0) en la tabla MEDIDAS
	char* tupla = "insert into medidas (fecha_hora,temp) values ('1980-01-01 00:00:00',25.0)";
	run_query(conn, tupla, "Carga de una tupla en MEDIDAS ...",0);

	// volver a listar, a ver qué tal
	run_query(conn, "select * from medidas", "Contenido de la tabla MEDIDAS:",1);

	// liberar el puntero (se hace al final del programa SOLO si se uso el resultado de la consulta)
	mysql_free_result(res);

	// cerrar la conexion al servidor
	mysql_close(conn);
}

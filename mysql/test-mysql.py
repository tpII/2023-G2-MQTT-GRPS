# python 3.5

import mysql.connector
from mysql.connector import Error

config = {
	'user':'taller2g2',
	'password':'taller2g2',
	'host':'163.10.3.73',
	'database':'taller2',
	'raise_on_warnings':True
}

try:
	connection = mysql.connector.connect(**config)

	if connection.is_connected():
		db_Info = connection.get_server_info()
		print("Connected to MySQL Server version ", db_Info)
		cursor = connection.cursor()
		cursor.execute("select database();")
		record = cursor.fetchone()
		print("You are connected to database: ", record)

except Error as e:
	print("Error while connecting to MySQL",e)
finally:
	if connection.is_connected():
		cursor.close()
		connection.close()
		print("MySQL connection is closed")

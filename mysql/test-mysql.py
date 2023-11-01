import mysql.connector

mydb = mysql.connector.connect(
	user='taller2g2',
	password='taller2g2',
	host='163.10.3.73',
	database='taller2'
)

print(mydb)

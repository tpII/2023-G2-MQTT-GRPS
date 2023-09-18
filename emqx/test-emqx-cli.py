# python 3.5
# prueba de emqx con python

import random
import time

from paho.mqtt import client as mqtt_client
from paho.mqtt.properties import Properties
from paho.mqtt.packettypes import PacketTypes

broker = '163.10.3.73'
port = 1883
topic = 'emqx/test'
client_id = 'netbook'
username = 'taller2g2'
password = 'taller2g2'

def on_connect(client,userdata,flags,rc):
	if rc == 0:
		print("Conectado al broker "+broker+":"+str(port))
	else:
		print("Conexion a "+broker+":"+str(port)+" fallo, codigo "+str(rc))
	client.subscribe("emqx/test")

def publish(client):
	msg_count = 1
	while True:
		time.sleep(1)

		properties = Properties(PacketTypes.PUBLISH)
		properties.MessageExpiryInterval = 30 				# en segundos

		msg="Mensajes: "+str(msg_count)
		result = client.publish(topic,msg,0,properties=properties)

		status = result[0]
		if status == 0:
			print("Enviado mensaje "+msg+" a topico "+topic)
		else:
			print("Envio de mensaje a topico "+topic+" fallo.")
		msg_count += 1
		if msg_count > 5:
			break

def run():
	client = mqtt_client.Client()

	client.on_connect=on_connect

	client.username_pw_set(username,password)

	client.connect(broker,port,60)

	client.loop_start()
	publish(client)
	client.loop_stop()

if __name__ == '__main__':
	run()

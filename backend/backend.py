import paho.mqtt.client as mqtt
import logging

# Configura el logging
logging.basicConfig(filename='/app/logs/app.log', level=logging.INFO)

# Callback cuando se conecta al broker
def on_connect(client, userdata, flags, rc):
    logging.info(f"Conectado con código de resultado {rc}")
    # Nos suscribimos al tópico (en este caso "test/topic")
    client.subscribe("test/topic")


# Callback cuando se recibe un mensaje del tópico
def on_message(client, userdata, msg):
    logging.info(f"Mensaje recibido: {msg.payload.decode()} en el tópico {msg.topic}")


logging.info("test")
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

logging.info("conectando")
client.username_pw_set("admin", "admin")

# Conexión al broker
client.connect("mosquitto", 1883, 60)

# Loop para mantener el cliente activo y escuchando mensajes
client.loop_forever()

# ProyectoTaller2

# Requisitos
    - Linux
    - Docker
    - Docker-compose
# Levantar el proyecto

1. Clonar el repositorio
2. Ejecutar el script ./app/startup.sh

# Logs
## Mosquitto
    - tail -f /app/mosquitto/log/mosquitto.log
## Backend
    - tail -f /app/backend/logs/app.log

## Broker
[Referencia guia mosquitto](https://www.manelrodero.com/blog/instalacion-de-mosquitto-mqtt-broker-en-docker)
### Suscripción a topico /test/message
docker exec -it mosquitto mosquitto_sub -u admin --pw admin -v -t /test/message
### Envío de mensaje a topico /test/message
docker exec -it mosquitto mosquitto_pub -u admin --pw admin -t /test/message -m 'Hello World!'

## DB
[Referencia InfluxDB](https://www.influxdata.com/blog/running-influxdb-2-0-and-telegraf-using-docker/)
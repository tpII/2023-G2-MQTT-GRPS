El proyecto Arduino esta configurado para funcionar con los componentes otorgados por la catedra y con una tarjeta SIM Tuenti. Para configurar el Arduino con otro modulo GPRS o con una tarjeta SIM de otra compañia se debe realizar lo siguiente:

- Configurar Modulo GPRS en la linea 8
- (Opcional) Configurar pin de la tarjeta en la linea 22
- Configurar el APN en las lineas 25-27 para que correspondan a la APN de la compañia telefonica.
- EMQX: La URL del servidor se configura en la linea 30. Por defecto intenta conectarse al servidor por el puerto 1883. En caso de ser otro puerto, configurarlo en la linea 123. En caso de conectarse con usuario y contraseña, se configura en la linea 58.

Pin 5 es el Data del DHT11.
Pin 2 es el RX para conectar al TX del modulo GPRS
Pin 3 es el TX para conectar al RX del modulo GPRS

Por defecto se envia el sensado cada 10 segundos, para cambiar el periodo, modifcar el else if de la linea 167. Como referencia 1000L = 1 segundo. 
#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void on_connect(struct mosquitto *mosq, void *obj, int reason_code) {
	printf("on connect: %s\n",mosquitto_connack_string(reason_code));

	if(reason_code != 0)
		mosquitto_disconnect(mosq);
}

void on_publish(struct mosquitto *mosq, void *obj, int mid) {
	printf("Message with mid %d has been published.\n",mid);
}

int get_temperature(void) {
	sleep(1);
	return random()%100;
}

void publish_sensor_data(struct mosquitto *mosq) {
	char payload[20];
	int temp;
	int rc;

	temp = get_temperature();

	snprintf(payload,sizeof(payload),"%d", temp);

	rc = mosquitto_publish(mosq,NULL,"/test/temperature",strlen(payload),payload,0,false);
	if(rc != MOSQ_ERR_SUCCESS)
		fprintf(stderr,"Error publishing: %s\n",mosquitto_strerror(rc));
}

int main(int argc, char *argv[]) {
	struct mosquitto *mosq;
	int rc;

	printf("Inicializando...\n");

	mosquitto_lib_init();

	mosq = mosquitto_new(NULL,true,NULL);
	if(mosq == NULL) {
		fprintf(stderr,"Error: out of memory.\n");
		return 1;
	}

	mosquitto_username_pw_set(mosq,"mosquitto","mosquitto");	// usuario, passw

	printf("Conectando...\n");

	mosquitto_connect_callback_set(mosq,on_connect);
	mosquitto_publish_callback_set(mosq,on_publish);

	rc = mosquitto_connect(mosq,"163.10.3.73",15883,60);	// IP, puerto, keepalive
	if(rc != MOSQ_ERR_SUCCESS) {
		mosquitto_destroy(mosq);
		fprintf(stderr,"Error: %s\n",mosquitto_strerror(rc));
		return 1;
	}

	while(1) {
		publish_sensor_data(mosq);
	}

	mosquitto_lib_cleanup();

	return 0;
}

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

void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos) {
	int i;
	bool have_subscription = false;

	for(i=0;i<qos_count;i++) {
		printf("on_subscribe: %d: granted qos = %d\n",i,granted_qos[i]);
		if(granted_qos[i] <= 2)
			have_subscription = true;
	}

	if(have_subscription == false) {
		fprintf(stderr,"Error: all subscriptions rejected.\n");
		mosquitto_disconnect(mosq);
	}
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
	printf("%s %d %s\n",msg->topic,msg->qos,(char *)msg->payload);
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
	mosquitto_subscribe_callback_set(mosq,on_subscribe);
	mosquitto_message_callback_set(mosq,on_message);

	rc = mosquitto_connect(mosq,"163.10.3.73",15883,60);	// IP, puerto, keepalive
	if(rc != MOSQ_ERR_SUCCESS) {
		mosquitto_destroy(mosq);
		fprintf(stderr,"Error: %s\n",mosquitto_strerror(rc));
		return 1;
	}

	rc = mosquitto_subscribe(mosq,NULL,"/test/temperature",0);	// topic /test/temperature, qos=0
	if(rc != MOSQ_ERR_SUCCESS) {
		mosquitto_destroy(mosq);
		fprintf(stderr,"Error: %s\n",mosquitto_strerror(rc));
		return 1;
	}

	mosquitto_loop_forever(mosq,-1,1);

	mosquitto_lib_cleanup();

	return 0;
}

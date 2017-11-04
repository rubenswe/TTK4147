#include "functions.h"

double y = 0;

void init_simulation(){

    udp_init_client(&conn, PORT, SERVER);

	pthread_mutex_init(&udp, NULL);
	pthread_mutex_init(&y_mutex, NULL);

	pthread_mutex_lock(&udp);
	udp_send(&conn, "START", BUFLEN);
	pthread_mutex_unlock(&udp);
}

void request_output(){

	pthread_mutex_lock(&udp);
	udp_send(&conn, "GET", BUFLEN);
	pthread_mutex_unlock(&udp);
}

void stop_simulation(){

	pthread_mutex_lock(&udp);
	udp_send(&conn, "STOP", BUFLEN);
	pthread_mutex_unlock(&udp);
	udp_close(&conn);
}

double extract_output(){

	const char search[] = ":";
    char *token;
    char *number;
   
    /* get the first token */
    token = strtok(receive_buffer, search);
   
    /* walk through other tokens */
    while( token != NULL ) {
        number = token;
        token = strtok(NULL, search);
   	}
   	return atof(number);
}

void set_input(double u){

	char msg[BUFLEN];
	snprintf(msg, BUFLEN, "SET:%f\n", u);
	printf(msg);

	pthread_mutex_lock(&udp);
	udp_send(&conn, msg, BUFLEN);
	pthread_mutex_unlock(&udp);
}

void signal_ack(){

	pthread_mutex_lock(&udp);
	udp_send(&conn, "SIGNAL_ACK", BUFLEN);
	pthread_mutex_unlock(&udp);
}

void *pi(){

	double u;
	int i;
	double error;
	double integral = 0;
	struct timespec next;
	clock_gettime(CLOCK_REALTIME, &next);
		
	for(i=0; i < 500000/PERIOD; i++){
		request_output();
		sem_wait(&sem_pi);
		pthread_mutex_lock(&y_mutex);
		error = REF - y;
		pthread_mutex_unlock(&y_mutex);
		integral = integral + (error * PERIOD/1000000);
		u = Kp * error + Ki * integral;
		set_input(u);
		timespec_add_us(&next, PERIOD);
		clock_nanosleep(&next);
	}
	return NULL;
}

void *udp_listener(){

	while(1){
		if(!(udp_receive(&conn, receive_buffer, BUFLEN) > 0)) {
			continue;
		}
		if(strncmp(receive_buffer, "SIGNAL", 6) == 0){
			sem_post(&sem_responder);

		}else if(strncmp(receive_buffer, "GET_ACK",7) == 0){
			pthread_mutex_lock(&y_mutex);
			y = extract_output();
			pthread_mutex_unlock(&y_mutex);
			sem_post(&sem_pi);
		}
	}
	return NULL;
}

void *signal_responder(){

	while(1){
		sem_wait(&sem_responder);
		signal_ack();
	}
	return NULL;
}
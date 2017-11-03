#include "functions.h"

double y = 0;

void init_simulation(){

	int init = udp_init_client(&conn, PORT, SERVER);
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

	char receive_buffer[BUFLEN];
	int length = udp_receive(&conn, &receive_buffer, BUFLEN);

	const char search[] = ":";
    char *token;
    char *number;
   
    /* get the first token */
    token = strtok(receive_buffer, search);
   
    /* walk through other tokens */
    while( token != NULL ) {
        //printf( " %s\n", token );
        number = token;
        token = strtok(NULL, search);
   	}

   	return atof(number);
}

void set_input(double u){

	char msg[BUFLEN];
	snprintf(msg, BUFLEN, "SET:%f", u);

	pthread_mutex_lock(&udp);
	udp_send(&conn, &msg, BUFLEN);
	pthread_mutex_unlock(&udp);
}

void *pi(){

	double u;
	int i;
	double integral = 0;
	struct timespec next;
	clock_gettime(CLOCK_REALTIME, &next);
	
	for(i=0; i < 500000/PERIOD; i++){
		timespec_add_us(&next, PERIOD);
		request_output();
		double y = extract_output();
		double error = REF - y;
		integral = integral + (error * PERIOD/1000000);
		u = Kp * error + Ki * integral;
		set_input(u);
		clock_nanosleep(&next);
	}
	return NULL;
}


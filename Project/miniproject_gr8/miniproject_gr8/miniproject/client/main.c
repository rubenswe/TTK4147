#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>

#include "miniproject.h"
#include "functions.h"


struct udp_conn conn;
double integral = 0;
double y = 0;

char receive_buffer[BUFLEN];

int main(){

	init_simulation();
	pthread_t pi_thread;
	pthread_create(&pi_thread, NULL, pi, NULL);
	pthread_join(pi_thread, NULL);
	stop_simulation();

	return 0;
}
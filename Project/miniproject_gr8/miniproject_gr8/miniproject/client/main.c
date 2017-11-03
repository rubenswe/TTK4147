#include "functions.h"

int main(){

	init_simulation();
	pthread_t pi_thread;
	pthread_create(&pi_thread, NULL, pi, NULL);
	pthread_join(pi_thread, NULL);
	stop_simulation();

	return 0;
}
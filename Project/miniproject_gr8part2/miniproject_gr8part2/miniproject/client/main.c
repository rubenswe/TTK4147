#include "functions.h"


int main(){

	init_simulation();

	pthread_t pi_thread;
	pthread_t udp_listener_thread;
	pthread_t signal_responder_thread;

	sem_init(&sem_responder, 0, 0);
	sem_init(&sem_pi, 0, 0);

	pthread_create(&pi_thread, NULL, pi, NULL);
	pthread_create(&udp_listener_thread, NULL, udp_listener, NULL);
	pthread_create(&signal_responder_thread, NULL, signal_responder, NULL);

	pthread_join(pi_thread, NULL);
	
	stop_simulation();

	sem_destroy(&sem_responder);
	sem_destroy(&sem_pi);
	pthread_mutex_destroy(&udp);
	pthread_mutex_destroy(&y_mutex);

	return 0;
}
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>


pthread_mutex_t forks[5];
pthread_mutex_t waiter;

void* phil (void* i) {

	int phil_id = *((int *) i);
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	// assign these pointers to left and right mutex(fork)	
	// use i (which is the phil number)

	if(i == 0) {
		//	right = i;
			left = &forks[4]; 
			right = forks; // points to the head of the array
		} else if(i == 4){
			right = &forks[4];
			left = &forks[3];
		}
		else {
			left = &forks[phil_id-1];
			right = &forks[phil_id];
		}


	while(1) {
		sleep(2);
		/*if(i == 0) {
		//	right = i;
			left = &forks[4]; 
			right = forks; // points to the head of the array
		} else if(i == 4){
			right = &forks[4];
			left = &forks[3];
		}
		else {
			left = &forks[phil_id-1];
			right = &forks[phil_id];
		}*/

		pthread_mutex_lock(&waiter);
		pthread_mutex_lock(left);
		pthread_mutex_lock(right);
		printf("Philosopher %i is eating...\n", phil_id);
		sleep(2);
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(&waiter);

	}		
	return NULL;	
}



int main(){

	int i;
	int philosophers = 5;

	pthread_t phil_thread[philosophers];

	for (i=0; i<philosophers; i++) {
		pthread_mutex_init(&forks[i], NULL);
	}

	for (i=0; i<philosophers; i++) {
		pthread_create (&phil_thread[i], NULL, phil, &i);
	}

	for (i=0; i<philosophers; i++) {
		pthread_join (&phil_thread[i], NULL);
	}
}



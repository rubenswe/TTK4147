#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t mySem;

void sem(number) {

int i;
sem_wait(&mySem);
	for (i=1; i<5; i++){
	printf("Thread number %i\n",number);
	sleep(5);
	}
sem_post(&mySem);

}

int main() {


	int number;


	if( sem_init(&mySem,1,3) <0) {
	perror("semaphore initialization");
	exit(0);
	}

	pthread_t one_thread;
	pthread_t two_thread;
	pthread_t three_thread;
	pthread_t four_thread;
	pthread_t five_thread;

	number=1;
	if (pthread_create(&one_thread, NULL, sem, number )) {
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	number=2;
	if (pthread_create(&two_thread, NULL, sem, number )) {
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	number=3;
	if (pthread_create(&three_thread, NULL, sem, number )) {
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	number=4;
	if (pthread_create(&four_thread, NULL, sem, number )) {
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}	

	number=5;
	if (pthread_create(&five_thread, NULL, sem, number )) {
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	if(pthread_join(two_thread, NULL)) {
	
		fprintf(stderr, "Error joining thread\n");
		return 2;		
	}

}



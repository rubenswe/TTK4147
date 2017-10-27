#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int global=0;

void  *one() {

	int j;
	int local = 0;

	for(j=0; j<5; j++) {
			global=global++;
			printf("First thread global= %i\n",global);
			local=local++;
			printf("First thread local= %i\n",local);
		}	
	return NULL;	
}

void  *two() {

	int i;
	int local = 0;
	for(i=0; i<5; i++) {
			global=global++;
			printf("Second thread global= %i\n",global);
			local=local++;
			printf("Second thread local= %i\n",local);
		}	
	return NULL;	
}


int main() {

	int local=0;
	//int j;

	pthread_t one_thread;
	pthread_t two_thread;
	
	if (pthread_create(&one_thread, NULL, one, NULL )) {
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	if (pthread_create(&two_thread, NULL, two, NULL )) {
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	
	/*for(j=0; j<5; j++) {
			global=global++;
			printf("First thread global= %i\n",global);
			local=local++;
			printf("First thread local= %i\n",local);
		}
*/
	
	
	if(pthread_join(two_thread, NULL)) {
	
		fprintf(stderr, "Error joining thread\n");
		return 2;		
	}
	
	
return 0;
}

#include <stdio.h>
#include <unistd.h>


int global=0;


void main(){

	int local=0;
	int i;
	int j;
	
	pid_t pid = fork();
	if (pid ==0) {  //child process
		for(i=0; i<5; i++) {
			global=global++;
			printf("Child global= %i\n",global);
			local=local++;
			printf("Child local= %i\n",local);
		}
	}
	else if( pid > 0) { // parent process
		for(j=0; j<5; j++) {
			global=global++;
			printf("Parent global= %i\n",global);
			local=local++;
			printf("Parent local= %i\n",local);
		}
	}
	else{
		printf("fork failed \n");
	}
}



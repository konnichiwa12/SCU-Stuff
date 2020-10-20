// Name: Dillon Kanai 
// Date: 10/1/20 
// Title: sample.c 
// Description: Use fork() to create a parent and child process that will print out IDs of the process 100 times each

/*Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    	pid_t  pid;
    	int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    	printf("\n Before forking.\n");
    	//fork
	pid = fork();
	//if fork was unsucessful, print error message
    	if (pid == -1) {
        	fprintf(stderr, "can't fork, error %d\n", errno);
    	}
	//if parent process, print out message
    	if (pid){
        	// Parent process
        	for (i=0;i<100;i++) {
            	printf("\t \t \t Parent Process %d \n",i);
            	usleep(n);
        	}
    	}   
	//if child process, print out message
    	else{
        	// Child process
        	for (i=0;i<100;i++) {
            	printf("Child process %d\n",i);
            	usleep(n);
        	}
    	}    
    	return 0;
}

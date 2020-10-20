// Name: Dillon Kanai
// // Date: 10/1/20
// // Title: thread.c
// // Description: Use threads to create a parent and child process that creates a 100 messages that print pid

/*Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>

/* main function with command-line arguments to pass */
//thread function
void* threading(void* delay){
        int i;
	for (i = 0; i < 100; i++){
                printf("Child Thread ID: %d \n", i);
                usleep(*(int *)delay);
        }
        return NULL;
}

int main(int argc, char *argv[]) {
    	pid_t  pid;
    	int delay = atoi(argv[1]); // n microseconds to input from keyboard for delay
    	//create pointer to an int
	int* i = malloc(sizeof(*i));
	//asign that dynamic variable as delay
	*i = delay;
	printf("\n Before threading.\n");
    	pthread_t threadnum;
	int j;
	//create thread that will manage shild process
	pthread_create(&threadnum, NULL, threading,(void*) i);
	//meanwhile, use normal for loop in non-stack environment for parent process
    	for (j = 0; j< 100; j++){
		printf("Parent Thread %d\n", j);
		usleep(*i);
	}
	//wait for thread to finish
	pthread_join(threadnum, NULL);
	return 0;
}



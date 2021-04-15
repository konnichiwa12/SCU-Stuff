// Name: Dillon Kanai
// Date: 1/5/2020 
// Title: Lab1 – Part5.c
// Description: This file demonstrates the behavior of Part1 but with threads


/*Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 

//child process
void* go(void* delay){
    int j;
    for (j = 0; j < 100; j++){
        printf("Child Process %d\n", j);
        usleep(*(int*)delay);
    }
}
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pthread_t threadnum;
    int delay = atoi(argv[1]);
    int i;
    int* n = malloc(sizeof(int));
    *n = delay;
    //create thread/child process
    pthread_create(&threadnum, NULL, go, (void*)n);
    //parent/main process
    for (i = 0; i < 100; i++){
        printf("\t\t\tParent Process %d\n", i);
        //delay
        usleep(delay);
    }
    //wait for threads to finish
    pthread_join(threadnum, NULL);
    return 0;
}

// Thread Sychronization

//Name: Dillon Kanai
//Date: 10/22/2020
//Title: threadSync.c
//Description: Use semaphores to sync up threads

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>


#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *mutex; 

void* go(void* arg) {
        sem_wait(mutex); //entry section
        printf("Thread %d Entered Critical Section..\n", (int)(size_t)arg); //critical section
        sleep(1);
        sem_post(mutex); //exit section
        return (NULL);
}

int main() {
	sem_unlink("mutex2");	
        mutex = sem_open("mutex2", O_CREAT, 0644, 1);
        static int i;
        for (i = 0; i < NTHREADS; i++)
                pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
        for (i = 0; i < NTHREADS; i++) {
                pthread_join(threads[i],NULL);
                printf("\t\t\tThread %d returned \n", i);
        }
        printf("Main thread done.\n");
        sem_unlink("mutex2");
        return 0;
}

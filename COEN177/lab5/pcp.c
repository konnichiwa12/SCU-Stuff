// Thread Sychronization

//Name: Dillon Kanai
//Date: 10/22/2020
//Title: Producer Consumer Problem
//Description: Solve the Producer Consumer  problem using semaphores

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>


#define NTHREADS 10
#define n 20
pthread_t threads[NTHREADS];
sem_t *mutex; 
sem_t *empty;
sem_t *full;
char buff[n];
int a, b;



void* producer(void* arg) { 
	int item1;
	do{
  		sleep(1);
		//produce item
		item1 = rand()%5;
		printf("Produced %d\n", item1);	
  		sem_wait(empty); //entry section
  		sem_wait(mutex); 
		//thread entered critical section
  		buff[a] = item1;
		a = (a + 1)%n;
		sem_post(mutex);
  		sem_post(full); //exit section 
       }while(1);
}

void* consumer(void* arg) {
	int item2;
	do{
  		sleep(1);
		//wait
		sem_wait(full);
		sem_wait(mutex);
		//thread entered critical section
		//consume item
		item2 = buff[b];
		b = (b + 1)%n;
		sem_post(mutex);
		sem_post(empty);
		//exit critical section
		printf("Consumed %d\n", item2);
	}while(1);	
}

int main() { 

sem_unlink("mutex2");
sem_unlink("empty2");
sem_unlink("full2");

mutex = sem_open("mutex2", O_CREAT, 0644, 1);
empty = sem_open("empty2", O_CREAT, 0644, n);
full = sem_open("full2", O_CREAT, 0644, 0);

static int i;
//create threads for producer
for (i = 0; i < NTHREADS/2; i++)  
   	pthread_create(&threads[i], NULL, producer, (void *)(size_t)i);

//create threads for consumer
for (i = NTHREADS/2; i < NTHREADS; i++)
   	pthread_create(&threads[i], NULL, consumer, (void *)(size_t)i);

//wait for threads to finish
for (i = 0; i < NTHREADS; i++) {
   	pthread_join(threads[i],NULL);
   	printf("\t\t\tThread %d returned \n", i);
	}
printf("Main thread done.\n");
sem_unlink("mutex"); 
return 0; 
} 

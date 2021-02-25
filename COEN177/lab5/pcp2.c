// Thread Sychronization

//Name: Dillon Kanai
//Date: 10/22/2020
//Title: Producer Consumer Problem 2
//Descrption: Solve the Producer Consumer Problem using pthread conditions

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <time.h>

#define NTHREADS 10
#define n 20
pthread_t threads[NTHREADS];
pthread_mutex_t mutex; 
pthread_cond_t empty;
pthread_cond_t full;
int buff[n];
int a, b, count;



void* producer(void* arg) { 
	int item1;
	do{
		item1 = rand()%10;
		sleep(1);
		printf("Thread %d Produced %d\n", (int)arg, item1); 
		//check mutex
		pthread_mutex_lock(&mutex);
		//while the buffer is full, wait
		while (count >= n){
			pthread_cond_wait(&empty, &mutex);
		}
		//enter critical section
		buff[a] = item1;
		a = (a + 1)%n;
		count++;
		//exit critical, trigger appropriate signal
		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
	}while(1);
}

void* consumer(void* arg) {
	int item2;
        do{
	  //check mutex
	        pthread_mutex_lock(&mutex);
		//while the buffer is empty, wait
                while (count <= 0){
                        pthread_cond_wait(&full, &mutex);
                }
		//enter critical
               	item2 = buff[b];
               	b = (b + 1)%n;
                count--;
		//exit critical, trigger appropriate signals
                pthread_cond_signal(&empty);
                pthread_mutex_unlock(&mutex);
		sleep(1);
		printf("Consumed %d\n", item2); 
        }while(1);	
}
int main() { 

srand(time(NULL));
pthread_mutex_init(&mutex, NULL);

static int i;
//make threads for producer
for (i = 0; i < NTHREADS/2; i++)  
   	pthread_create(&threads[i], NULL, producer, (void *)(size_t)i);
//make threads for consumer
for (i = NTHREADS/2; i < NTHREADS; i++)
   	pthread_create(&threads[i], NULL, consumer, (void *)(size_t)i);
//wait for threads to finish
for (i = 0; i < NTHREADS; i++) {
   	pthread_join(threads[i],NULL);
   	printf("\t\t\tThread %d returned \n", i);
	}
printf("Main thread done.\n");
pthread_mutex_destroy(&mutex); 
return 0; 
} 

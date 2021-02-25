// Thread Sychronization

//Name: Dillon Kanai
//Date: 10/22/2020
//Title: threadSync2.c
//Description: Use mutex to sync up threads

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <string.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock;

void* go(void* arg) { 
  pthread_mutex_lock(&lock); //entry section
  printf("Thread %d Entered Critical Section..\n", (int)(size_t)arg); //critical section 
   sleep(1); 
  pthread_mutex_unlock(&lock); //exit section 
  return (NULL);
} 

int main() {
pthread_mutex_init(&lock, NULL); 
int i, error = 0;
if (pthread_mutex_init(&lock, NULL) != 0){
	printf("\n mutex fail \n");
}
for (i = 0; i < NTHREADS; i++){  
   usleep(i);
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
}
for (i = 0; i < NTHREADS; i++) {
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
pthread_mutex_destroy(&lock); 
return 0; 
} 

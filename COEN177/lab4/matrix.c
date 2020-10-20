//matrix.c
//Name: Dillon Kanai
//Date: 10/15/20 
//Title: Lab4 - Step 3 
//Description: Performs matrix multiplication 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define NTHREADS 1024
#define MAX 2

double matrixA[MAX][MAX];
double matrixB[MAX][MAX];
double matrixC[MAX][MAX];
int N, M, L;
pthread_t threads[MAX];


void *mult(void * arg) {
	int i = *(int *) arg;
	int x, y;
	//generate dot products
	for(x = 0; x < MAX; x++) {
		double temp = 0;
		//generate dot product and add to appropriate location
		for(y = 0; y < MAX; y++) {
			temp += matrixA[i][y] * matrixB[y][x];
		}
		matrixC[i][x] = temp;
	}
}

int main() {
	int N = MAX, M = MAX, L = MAX;
	int i, j;

	
	//generate matrix A
	printf("Generate Matrix A: \n");
	srand(time(NULL));
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++) {
			matrixA[i][j] = rand() % 10;
			printf("  %.2f \t", matrixA[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	//generate matrix B
	printf("Generate Matrix B: \n");
        for(i = 0; i < M; i++){
                for(j = 0; j < L; j++) {
                        matrixB[i][j] = rand() % 10;
			printf("  %.2f \t", matrixB[i][j]);
                }
		printf("\n");
	}
	printf("\n");
	
	//generate values for matrixC
	for(i = 0; i < N; i++) {
		usleep(i);
		//generate one thread per row of C
		pthread_create(&threads[i], NULL, mult, &i);
	}

	//wait for all threads to finish
	for(i = 0; i < MAX; i++) {
		pthread_join(threads[i], NULL);
		printf("Thread %d returned.\n", i);
	}

	//Print matrix c
	for(i = 0; i < N; i++) {
		for(j = 0; j < L; j++) {
			printf("  %.2f  \t", matrixC[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}


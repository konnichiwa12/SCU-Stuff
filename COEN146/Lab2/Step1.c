// Name: Dillon Kanai 
// Date: 1/12/21
// Title: Lab2 – Step1.c
// Description: 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char* argv[]){
	//start clock
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	//create buffer
    int size = 30;
	char buffer[size]; 
	//open input and output files in correct mode
	FILE *fp;
	fp = fopen("file1.dat", "rb"); 
	FILE *op;
	op = fopen(argv[1], "wb");

	//checks
	if (fp == NULL){
		printf("Could not open file: %s\n", argv[1]);
		return 0;
	}
	if (size <= 0){
		printf("Invalid Buffer Size\n");
	}

	//copy from input file to output file
	int counted = 0;
	while (counted = fread(buffer, sizeof(char), sizeof(buffer), fp)){
		printf("%d\n", counted);
		fwrite(buffer, sizeof(char), counted, op);
	}

	//release pointers and compute time
	fclose(fp);
	fclose(op);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %f\n", cpu_time_used);
	return 0;
}

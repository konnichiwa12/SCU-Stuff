// Name: Dillon Kanai 
// Date: 11/12/20
// Title: Lab9 – Step3.c
// Description: Prints how much time it takes to read a file with varying buffer sizes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char* argv[]){
	int size = atoi(argv[2]);
	char buffer[size]; 
	FILE *fp;
	fp = fopen(argv[1], "rb"); 

	if (fp == NULL){
		printf("Could not open file: %s\n", argv[1]);
		return 0;
	}
	if (size <= 0){
		printf("Invalid Buffer Size\n");
	}

	while (fread(buffer, sizeof(buffer), 1, fp)){
	}
	fclose(fp);
	return 0;
}

// Name: Dillon Kanai 
// Date: 11/12/20
// Title: Lab9 – Step4.c
// Description: Prints how much time it takes to read a file with varying buffer sizes and copy it into a new file

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
	FILE *op;
	op = fopen("Step4out.txt", "wb");

	if (fp == NULL){
		printf("Could not open file: %s\n", argv[1]);
		return 0;
	}
	if (size <= 0){
		printf("Invalid Buffer Size\n");
	}

	while (fread(buffer, sizeof(buffer), 1, fp)){
		fwrite(buffer, sizeof(buffer), 1, op);
	}
	fclose(fp);
	fclose(op);
	return 0;
}

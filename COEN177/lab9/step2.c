// Name: Dillon Kanai 
// Date: 11/12/20
// Title: Lab9 – Step2.c
// Description: Prints how much time it takes to read a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char* argv[]){
	char buffer[10000]; 
	FILE *fp;
	fp = fopen(argv[1], "rb"); 

	if (fp == NULL){
		printf("Could not open file: %s\n", argv[1]);
		return 0;
	}

	while (fread(buffer, sizeof(buffer), 1, fp)){
	  
	}
	fclose(fp);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

//global variables
int threadnum, size;
char name[13];

//use functions for file management
void* tfunc(void* a){
	//get names of both input and output files and open them
    int num = (int)(size_t)a;
    char inname[12];
    sprintf(inname, "step4In%d.dat", num);
	FILE *fp = fopen(inname, "rb");
	char outname[strlen(name) + 1];
	sprintf(outname, "%d%s", num, name);
	FILE *op = fopen(outname, "wb");
	//create buffer
	char buffer[size];
	int counted = 0;
	//copy
	while(counted = fread(buffer, sizeof(char), sizeof(buffer), fp)){
	  fwrite(buffer, counted, 1, op);
	}
	fclose(fp);
	fclose(op);
    
}

int main(int argc, char* argv[]){
	size = 2000;
    threadnum = 10;
	strcpy(name, argv[1]);
	pthread_t pthread[10];
	int i;
	//activate threads
	for (i = 0; i < threadnum; i++){
		pthread_create(&pthread[i], NULL, tfunc, (void*)(size_t)i);
	}
	//wait for threads to finish
	for (i = 0; i < threadnum; i++){
		pthread_join(pthread[i], NULL);
	}
	
	return 0;
}

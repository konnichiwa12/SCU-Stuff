// Name: Dillon Kanai 
// Date: 11/12/20
// Title: Lab9 – Step5.c
// Description: Prints how much time it takes to read a file with varying buffer sizes and copy it into a new file, using threads

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

int threadnum, size;
char filename[9];

void* tfunc(void* buffsize){
  int num = (int)(size_t)buffsize;
	FILE *fp = fopen(filename, "rb");
	char outname[12];
	sprintf(outname, "Step5Out%d.txt", num);
	FILE *op = fopen(outname, "wb");
	char buffer[size];
	while(fread(buffer, size, 1, fp)){
	  fwrite(buffer, size, 1, op);
	}
	fclose(fp);
	fclose(op);
}

int main(int argc, char* argv[]){
        strcpy(filename, argv[1]);
	size = atoi(argv[2]);
	threadnum = atoi(argv[3]);
	pthread_t pthread[threadnum];
	int i;
	for (i = 0; i < threadnum; i++){
		pthread_create(&pthread[i], NULL, tfunc, (void*)(size_t)i);
	}
	for (i = 0; i < threadnum; i++){
		pthread_join(pthread[i], NULL);
	}
	
	return 0;
}

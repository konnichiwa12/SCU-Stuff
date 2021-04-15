// Name: Dillon Kanai 
// Date: 11/12/20
// Title: Lab9 – Step4.c
// Description: Prints how much time it takes to read a file with varying buffer sizes and copy it into a new file

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
	//open files in correct modes
	int ip;
	ip = open("file2.dat", O_RDONLY); 
	int op;
	op = open(argv[1], O_WRONLY | O_TRUNC| O_CREAT, 0644);
	int count = 0;
	//copy
	while (count = read(ip, buffer, sizeof(buffer))){
		write(op, buffer, count);
	}
	//close files
	close(ip);
	close(op);
	//compute time
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	return 0;
}

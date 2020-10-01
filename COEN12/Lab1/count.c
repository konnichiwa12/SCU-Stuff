//libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

//initialize functions
int count(char filename[]);


//global variables
#define MAX_WORD_LENGTH 30
int words = 0;

//arguemnts: an int (number of arguemtns in command line), and a pointer to each arguemnt
//return value: int, total number of words
//function: check number of arguments in command line (deny if wrong amount), call count function,  and print total number of words
int main(int argc, char *argv[]){
	if (argc < 2){
		printf("Missing file name");
		return -1;
	}
	else if (argc > 2){
		printf("Too many inputs");
		return -1;
	}
	words = count(argv[1]);
	printf("%d total words\n", words);
	return 0; 
}
//arguements: name of the file
//return: int, return number of words or -1 if there is an error
//function: go through text file and count how many strings there are
int count(char filename[]){
	char str[MAX_WORD_LENGTH], *p;
	int flag = 0;
	FILE *fp;
	if ((fp=fopen(filename, "r"))==NULL){
		printf("error\n");
		return -1;
	}
	//count how many strings until you reach end of file
	while (fscanf(fp, "%s", str) == 1){
		words++;
	}
	fclose(fp);
	return words;
}

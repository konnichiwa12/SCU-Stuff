#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Ver2F.h"

//arguments: none
//return: an int
//function: main; trigger all functions in data set
//O(n)
int main(){
	printf("-----------------------------------\n");
	SET *p;
	int maxElts = 3000;
	int preID = 0;
	int age;
	int ID;
	p = createSet(maxElts);
	printf("generate 1000 students and insert\n");
	printf("-----------------------------------\n");
	srand(time(NULL));
	for(int i = 0; i < 1000; i++){
		age = rand()%13 + 18;
		ID = rand()%4 + 1 + preID;
		printf("%d, %d\n", age, ID);
		insertID(p, age, ID);
		preID = ID;
	}
	printf("-----------------------------------\n");
	printf("Generating Random Student\n");
	int RandAge = rand()%13 + 18;
	int RandID = rand()%10;
	printf("Generated Random Student|| Age: %d | ID: %d ||\n", RandAge, RandID);
	if (search(p, RandAge, RandID) == true){
		printf("Match Found!\n");
		printf("Student [ID: %d] is already in the database\n", RandID);
		deleteID(p, RandAge, RandID);
	}
	else{
		printf("Student ||Age: %d | ID: %d || not found\n", RandAge, RandID);
	}
	printf("-----------------------------------\n");
	printArray(p);
	printf("-----------------------------------\n");
	destroySet(p);
	printf("Set Destroyed\n");
	printf("-----------------------------------\n");
	return 0;
}
	
	
		
		

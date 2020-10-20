#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#define MAX 10
#define ELT struct elt
#define SET struct set
#include "Ver2F.h"

struct elt{
	int num;
};

struct set{
	ELT* age;
	ELT* id;
	int length;
	int count;
};
//arguments: int
//return: SET pointer
//function: creates a SET and two arrays of ELT elements. Initialize length and count
//O(1)
SET* createSet(int maxElts){
	assert(maxElts != 0);
	SET* sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->age = malloc(sizeof(ELT)*maxElts);
	sp->id = malloc(sizeof(ELT)*maxElts);
	assert(sp->age != NULL && sp->id != NULL);
	sp->length = maxElts;
	sp->count = 0;
	return sp;
}
//arguments: SET pointer, 2 ints
//return: boolean
//function: search for an ID and return true/false
//O(1)
bool search(SET* sp, int searchage, int searchid){
	assert(sp != NULL);
	if (sp->id[searchid].num != '\0'){
		return true;
	}
	else{
		return false;
	}
}
//arguments: SET pointer, 2 ints
//return: void
//function: use search function and insert into arrays
//O(1)
void insertID(SET *sp, int insertage, int insertid){
	assert(sp != NULL);
	if (search(sp, insertage, insertid) == false){
		sp->age[insertid].num = insertage;
		sp->id[insertid].num = insertid;
		printf("Insert successful\n");
		return;
	}
	printf("Insert unsuccessful\n");
	return;
}
//arguments: SET pointer, two ints
//return: void
//function: use search function and delete elt from arrays
//O(1)
void deleteID(SET *sp, int insertage, int insertid){
	assert(sp != NULL);
	if (search(sp, insertage, insertid) == true){
		sp->id[insertid].num = '\0';
		sp->age[insertid].num = '\0';
		printf("Delete Successful\n");
		return;
	}
	printf("Delete Unsuccessful\n");
	return;
}
//arguments: SET pointer
//return: void
//function: print out elements from both arrays
//O(n)
void printArray(SET *sp){
	assert(sp != NULL);
	printf("Printing List\n");
	printf("AGE:       ID:\n");
	for (int i = 0; i < sp->length; i++){
		if (sp->id[i].num != '\0'){
			printf(" %d        %d\n", sp->age[i].num, sp->id[i].num);
		}
	}
	printf("Printing Finished\n");
}
//arguments:SET pointer
//return: void
//function: free SET pointer
//O(1)
void destroySet(SET *sp){
	free(sp->id);
	free(sp->age);
	free(sp);
}

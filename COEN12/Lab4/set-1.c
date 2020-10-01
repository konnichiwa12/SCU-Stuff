#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#include <math.h>
#include "list.h"
#define CHAIN 20

typedef struct set{
	int count;
	int length;
	LIST** data;
	int (*compare)();
	unsigned (*hash)();
}SET;

//Arguments: int Maxelts, compare function and hash function
//Return: A Set
//Function: Creates an array with pointers that point to lists. Initialize count and length as well
//O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned(*hash)()){
	assert(maxElts > 0);
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts/CHAIN;
	sp->compare = compare;
	sp->hash = hash;
	sp->data = malloc(sizeof(LIST*)*sp->length);
	for (int i = 0; i < sp->length; i++){
		sp->data[i] = createList(sp->compare);
	}
	return sp;
}

//Arguments: a set pointer
//return: void
//function: delete a set
//O(n)
void destroySet(SET *sp){
	assert(sp != NULL);
	for(int i = 0;i < sp->length; i++){
		destroyList(sp->data[i]);
	}
	free(sp->data);
	free(sp);
	return;
}

//arguments: set pointer
//return: void
//function: return the total number of elements in the set
//O(1)
int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;
}

//arguments: set pointer and void pointer
//return: void
//function: add an element into a list using the hash function
//O(1)
void addElement(SET *sp, void *elt){
	assert(sp!=NULL);
	assert(elt!=NULL);
	int index = (*sp->hash)(elt)%(sp->length);
	if (findItem(sp->data[index], elt) != NULL){
		return;
	}
	sp->count++;
	addFirst(sp->data[index], elt);
	return;
}

//arguments: set pointer and void pointer
//return: void
//function: remove an element from a list using the hash function
//O(1)
void removeElement(SET *sp, void *elt){
	assert(sp!= NULL);
	int index = (*sp->hash)(elt)%(sp->length);
	sp->count--;
	removeItem(sp->data[index], elt);
	return;
}

//arguments: set pointer and void pointer
//return: void
//function: find an element in the lists using the hash function
//O(1)
void *findElement(SET *sp, void *elt){
	assert(sp!=NULL);
	int index = (*sp->hash)(elt)%(sp->length);
	return findItem(sp->data[index], elt);
}

//arguments: set pointer only
//return: void pointer
//get all of the existing elements in the lists, memcpy to an array, and return a void pointer that points to that array
//O(n)
void *getElements(SET *sp){
	assert(sp!=NULL);
	assert(sp->count > 0);
	int a = 0;
	void** elts = malloc(sizeof(void*)*sp->count);
	assert(elts != NULL);
	for (int i = 0; i < sp->length; i++){
		void ** seq = getItems(sp->data[i]);
		for (int j = 0; j < numItems(sp->data[i]); j++){
			elts[a] = seq[j];
			a++;
		}
	}
	return elts;
}	

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

typedef struct set{
	char **data;
	int length;//how long array is
	int count;//how many things are in array
}SET;
//function: search through array **data and see if elt is in there. Return index or -1(if not found)
//arguemnts: a SET structure pointer and a char pointer
//return value: an int
//O(n)
static int search(SET *sp, char *word){
	assert(sp != NULL);
	for (int i = 0; i < sp->count; i++){
		if (strcmp(sp->data[i], word)==0){
			return i;
		}
	}
	return -1;
}
//function: create a set with **data having MaxElts slots
//arguments: an int
//return: a SET structure
//O(1)
SET *createSet(int maxElts){
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count= 0;
	sp->data=malloc(sizeof(char *)*maxElts);
	assert(sp->data != NULL);
	return sp;
}
//function: delete a SET
//arguments: a SET pointer
//return: void
//O(n)
void destroySet(SET *sp){
	assert(sp != NULL);
	for (int i = 0; i < sp->count; i++){
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
}
//function: return number of elements in sp->data
//arguments: a SET pointer
//return: an int
//O(1)
int numElements(SET *sp){
	assert(sp != NULL);
	return (sp->count);
}
//function: add an element and shift elements
//arugements: SET pointer and char pointer
//return: void
//O(n)
void addElement(SET *sp, char *elt){
	assert(sp != NULL);
	assert(elt != NULL);
	if ((sp->count) == sp->length){
		return;
	}
	if (search(sp, elt)!=-1){
		return;
	}
	else{
		elt = strdup(elt);
		sp->data[sp->count] = elt;
		(sp->count)++;
	}
}
//function: remove an element and shift elements
//arguments: SET pointer and char pointer
//return: void
//O(n)
void removeElement(SET *sp, char *elt){
	assert(sp!=NULL);
	if (sp->count == -1){
		return;
	}
	else{
		int i = search(sp, elt);
		free(sp->data[i]);
		for(;i < (sp->count)-1; i++){
			sp->data[i] = sp->data[i + 1];
		}
		sp->count--;
	}
	return;
}
//function: find a specific element
//arguments: SET pointer and char pointer
//return: char
//O(1)
char *findElement(SET *sp, char *elt){
	assert(sp != NULL);
	if (search(sp, elt)== -1){
		return NULL;
	}
	return sp->data[search(sp, elt)];
}
//function: return SET->data
//arguments: SET pointer
//return: array of char pointers
//O(1)
char **getElements(SET *sp){
	assert(sp!=NULL);
	char **array;
	array = malloc(sizeof(char)*(sp->count));
	assert(array!=NULL);
	memcpy(array, sp->data, sp->count);
	return array;
}


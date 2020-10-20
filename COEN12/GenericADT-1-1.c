#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#define EMPTY 0
#define DELETED 1
#define FILLED 2


typedef struct set{
	void **data;
	int length;//how long array is
	int count;//how many things are in array
	int *flags;
	int (*compare)();
	unsigned (*hash)();
}SET;
//function: search through array **data and array flags to see if elt is in there. Return index or -1(if not found). Set pointer tru to true is found
//arguemnts: a SET structure pointer and a char pointer, and boolean pointer
//return value: an int
//O(n)

static int search(SET *sp, char *word, bool *tru){
	assert(sp != NULL);
	*tru = false;
	int placeholder = -1;
	int  index;
	unsigned key = (*sp->hash)(word);
	for (int i = 0; i < sp->length; i++){
		index = (key + i)%(sp->length);
		if (sp->flags[index] == FILLED){
			if((*sp->compare)(word,sp->data[index])==0){
				*tru = true;
				return index;
			}
		}
		else if (sp->flags[index] == DELETED){
			if (placeholder == -1){
				placeholder = index;
			}
		}
		else if (sp->flags[index] == EMPTY){
			if (placeholder != -1){
				return placeholder;
			}
			return index;
		}
	}
	return placeholder;
}

//function: create a set with **data having MaxElts slots and initalize functions compare and hash
//arguments: an int
//return: a SET structure
//O(1)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count= 0;
	sp->data=malloc(sizeof(void *)*maxElts);
	assert(sp->data != NULL);
	sp->flags=malloc(sizeof(int)*maxElts);
	assert(sp->flags != NULL);
	for (int i = 0; i < maxElts; i++){
		sp->flags[i] = EMPTY;
	}
	sp->compare = compare;
	sp->hash = hash;
	return sp;
}
//function: delete elements we have only created
//arguments: a SET pointer
//return: void
//O(1)
void destroySet(SET *sp){
	assert(sp != NULL);
	free(sp->data);
	free(sp->flags);
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
//function: add an element and change value of flags to FILLED
//arugements: SET pointer and char pointer
//return: void
//O(1)
void addElement(SET *sp, void *elt){
	assert(sp != NULL);
	assert(elt != NULL);
	if(sp->count == sp->length){
		return;
	}
	bool found = false;
	int placeholder = search(sp, elt, &found);
	if (found){
		return;
	}
	if (placeholder == -1){
		return;
	}
	sp->data[placeholder]=elt;
	sp->count++;
	sp->flags[placeholder]=FILLED;
	return;
}
//function: remove an element
//arguments: SET pointer and char pointer
//return: void
//O(1)
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL);
	bool found = false;
	int i = search(sp, elt, &found);
	assert(i >= 0);
	if (found){	
		sp->data[i] = NULL;
		sp->count--;
		sp->flags[i]=DELETED;
	}			
	return;
}
//function: find a specific element
//arguments: SET pointer and char pointer
//return: char
//O(1)
void *findElement(SET *sp, void *elt){
	assert(sp != NULL);
	bool found;
	int i = search(sp, elt, &found);
	if (found){
		return sp->data[i];
	}
	return NULL;
}
//function: return array with elements of sp->data
//arguments: SET pointer
//return: array of char pointers
//O(n)
void *getElements(SET *sp){
	assert(sp!=NULL);
	void **array;
	array = malloc(sizeof(void *)*(sp->count));
	assert(array!=NULL);
	for(int i = 0, j = 0; i < sp->length; i++){
		if (sp->flags[i] == FILLED){
			array[j] = sp->data[i];
			j++;
		}
	}
	return array;
}



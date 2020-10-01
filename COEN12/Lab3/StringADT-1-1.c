#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"
#define EMPTY 0
#define DELETED 1
#define FILLED 2
static unsigned srthash(char *s);

typedef struct set{
	char **data;
	int length;//how long array is
	int count;//how many things are in array
	int *flags;
}SET;
//function: search through array **data and see if elt is in there. Return index or -1(if not found). Set pointer tru to true is found
//arguemnts: a SET structure pointer and a char pointer, and boolean pointer
//return value: an int
//O(n)

static unsigned strhash(char *s){
        unsigned hash = 0;
        while (*s != '\0'){
                hash = 31 * hash + *s++;
        }
        return hash;
}
static int search(SET *sp, char *word, bool *tru){
	assert(sp != NULL);
	int placeholder = -1;
	int  index;
	unsigned key = strhash(word);
	for (int i = 0; i < sp->length; i++){
		index = (key + i)%(sp->length);
		if (sp->flags[index] == FILLED){
			if(strcmp(word,sp->data[index])==0){
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
	*tru = false;
	return placeholder;
}

//function: create a set with **data having MaxElts slots and array flag with all EMPTY slots
//arguments: an int
//return: a SET structure
//O(n)
SET *createSet(int maxElts){
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count= 0;
	sp->data=malloc(sizeof(char *)*maxElts);
	assert(sp->data != NULL);
	sp->flags=malloc(sizeof(int *)*maxElts);
	assert(sp->flags != NULL);
	for (int i = 0; i < maxElts; i++){
		sp->flags[i] = EMPTY;
	}
	return sp;
}
//function: delete a SET
//arguments: a SET pointer
//return: void
//O(n)
void destroySet(SET *sp){
	assert(sp != NULL);
	for (int i = 0; i < sp->length; i++){
		if (sp->flags[i] == FILLED){
			free(sp->data[i]);
		}
	}
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
//function: add an element and change flag values to FILLED
//arugements: SET pointer and char pointer
//return: void
//O(1)
void addElement(SET *sp, char *elt){
	assert(sp != NULL);
	assert(elt != NULL);
	if(sp->count == sp->length){
		return;
	}
	bool found = false;
	int placeholder = 0;
	placeholder = search(sp, elt, &found);
	if (found){
		return;
	}
	if (placeholder == -1){
		return;
	}
	sp->data[placeholder]=strdup(elt);
	sp->count++;
	sp->flags[placeholder]=FILLED;
}
//function: remove an element and change flag values to EMPTY
//arguments: SET pointer and char pointer
//return: void
//O(1)
void removeElement(SET *sp, char *elt){
	assert(sp!=NULL);
	bool found = false;
	int i = search(sp, elt, &found);
	if (found){	
		free(sp->data[i]);
		sp->count--;
		sp->flags[i]=DELETED;
	}			
	return;
}
//function: find a specific element
//arguments: SET pointer and char pointer
//return: char
//O(1)
char *findElement(SET *sp, char *elt){
	assert(sp != NULL);
	bool found;
	int i = search(sp, elt, &found);
		if (found){
			return sp->data[i];
		}
		else{
			return NULL;
		}
}
//function: return values of set->data
//arguments: SET pointer
//return: array of char pointers
//O(n)
char **getElements(SET *sp){
	assert(sp!=NULL);
	char **array;
	array = malloc(sizeof(char)*(sp->count));
	assert(array!=NULL);
	for(int i = 0, j = 0; i < sp->length; i++){
		if (sp->flags[i] == FILLED){
			array[j] = sp->data[i];
			j++;
		}
	}
	return array;
}



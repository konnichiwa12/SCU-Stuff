#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "pqueue.h"
#define P(x) ((x-1)/2)
#define L(x) ((x*2)+1)
#define R(x) ((x*2)+2)

typedef struct pqueue{
	int count;
	int length;
	void** data;
	int (*compare)();
}PQ;

PQ *createQueue(int (*compare)()){
	assert(compare != NULL);
	PQ *pointer = malloc(sizeof(PQ));
	assert(pointer != NULL);
	pointer->data = malloc(sizeof(void*)*10);
	assert(pointer->data != NULL);
	pointer->compare = compare;
	pointer->length = 10;
	pointer->count = 0;
	return pointer;
}

void destroyQueue(PQ *pq){
	assert(pq != NULL);
	free(pq->data);
	free(pq);
	return;
}

int numEntries(PQ *pq){
	assert(pq != NULL);
	return pq->count;
}

void addEntry(PQ *pq, void *entry){
	assert(pq != NULL);
	assert(entry != NULL);
	if(pq->count == pq->length){
		pq->length*=2;
		pq->data=realloc(pq->data, sizeof(void*)*(pq->length));
	}
	int ind = pq->count;
	while(ind > 0 && (*pq->compare)(pq->data[P(ind)], entry)>0){
		
		//void* temp = pq->data[ind];
		pq->data[ind]=pq->data[P(ind)];
		//pq->data[P(ind)]=temp;
		ind = P(ind);
	}
	pq->count++;
	pq->data[ind]=entry;
	return;
}

void *removeEntry(PQ *pq){
	assert(pq!=NULL);
	void* p = pq->data[0];
	void* temp = pq->data[pq->count-1];
	int i = 0;
	while(L(i) < pq->count-1){
		int flag = L(i);
		if (R(i) < pq->count-1){
			if((*pq->compare)(pq->data[R(i)],pq->data[L(i)]) < 0){
				flag=R(i);
			}
		}
		if ((*pq->compare)(temp, pq->data[flag]) <= 0){
			break;
		}
		else{
			pq->data[i] = pq->data[flag];
		}
		i = flag;
	}
	pq->data[i] = temp;
	pq->count--;
	return p;
}
		


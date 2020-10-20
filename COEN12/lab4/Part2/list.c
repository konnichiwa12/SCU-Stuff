#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

typedef struct list{
	int count;
	struct node *head;
	int (*compare)();
}LIST;

typedef struct node{
	void *data;
	struct node *next;
	struct node *prev;
}NODE;

//arguments: compare function
//return: a LIST pointer
//function: initialize a list, with dummy node, malloc space, and initialize count and head
//O(1)
LIST *createList(int (*compare)()){
	LIST *lp = malloc(sizeof(LIST));
	assert(lp !=NULL);
	lp->count = 0;
	lp->head = malloc(sizeof(NODE)); 
	assert(lp->head != NULL);
	NODE *dn = lp->head;
	lp->compare = compare;
	dn->prev = dn;
	dn->next = dn;
	return lp;
}

//arguments: list pointer
//return: void
//function: delete a list and its contents
//O(n)
void destroyList(LIST *lp){
	assert(lp != NULL);
	NODE *pdel, *pnext;
	pdel = lp->head;
	do{
		pnext = pdel->next;
		free(pdel);
		pdel = pnext;
	}while(pdel != lp->head);
	free(lp);
}

//arguments: list pointer
//return: int
//function: return the number of items in the list
//O(1)
int numItems(LIST *lp){
	assert(lp != NULL);
	return lp->count;
}

//arguments: list pointer and void pointer
//return: void
//function: add a node the front of the list
//O(1)
void addFirst(LIST *lp, void *item){
	assert(lp != NULL);
	NODE *temp = malloc(sizeof(NODE));
	assert(temp != NULL);
	temp->data = item;
	NODE *dn = lp->head;
	dn->next->prev = temp;
	temp->next = dn->next;
	temp->prev = dn;
	dn->next = temp;
	lp->count++;
	return;
}

//arguments: list pointer and void pointer
//return: void
//function: add a node to the back of the list
//O(1)
void addLast(LIST *lp, void *item){
	assert(lp != NULL);
	NODE *temp = malloc(sizeof(NODE));
	assert(temp != NULL);
	NODE *dn = lp->head;
	temp->data = item;
	dn->prev->next = temp;
	temp->next = dn;
	temp->prev = dn->prev;
	dn->prev = temp;
	lp->count++;
	return;
}

//arguments: list pointer
//return: void pointer
//function: remove the first node of the list
//O(1)
void *removeFirst(LIST *lp){
	assert(lp != NULL);
	NODE *pdel = lp->head->next;
	void *N = pdel->data;
	NODE *dn = lp->head;
	dn->next = pdel->next;
	pdel->next->prev = dn;
	free(pdel);
	lp->count--;
	return N;
}

//arguments: list pointer
//return: void pointer
//function: remove the last node of the list
//O(1)
void *removeLast(LIST *lp){
	assert(lp != NULL);
	NODE *pdel = lp->head->prev;
	void *N = pdel->data;
	NODE *dn = lp->head;
	dn->prev = pdel->prev;
	pdel->prev->next = dn;
	free(pdel);
	lp->count--;
	return N;
}

//arguments: list pointer
//return: void pointer
//function: return a pointer to the first item of the list
//O(1)
void *getFirst(LIST *lp){
	assert(lp != NULL);
	if (lp->count >=1){
		return lp->head->next->data;
	}
	return NULL;
}

//arguments: list pointer
//return: void pointer
//return a pointer to the last item of the list
//O(1)
void *getLast(LIST *lp){
	assert(lp != NULL);
	if (lp->count >= 1){
		return lp->head->prev->data;
	}
	return NULL;
}

//arguments: list pointer and void pointer
//return: void
//function: remove a certain item from anywhere in the list
//O(n)
void removeItem(LIST *lp, void *item){
	assert(lp != NULL);
	assert(lp->compare != NULL);
	assert(lp->count >= 1);
	NODE *dn = lp->head;
	NODE *flag = dn->next;
	while(flag != lp->head){
		if ((*lp->compare)(flag->data, item)==0){
			flag->prev->next = flag->next;
			flag->next->prev = flag->prev;
			free(flag);
			lp->count--;
			break;
		}
		else{
			flag = flag->next;
		}
	}
	return;
}

//arguments: list pointer and void pointer
//return: void pointer
//function: return a pointer to a certain item in the list
//O(n)
void *findItem(LIST *lp, void *item){
	assert(lp != NULL);
	NODE *dn = lp->head;
	NODE *flag = dn->next;
	while(flag != lp->head){
		if ((*lp->compare)(flag->data, item)==0){
			return flag->data;
		}
		else{
			flag = flag->next;
		}
	}
	return NULL;
}

//arguments: list pointer
//return: void pointer
//function: return a pointer to an array with all of the elements in the list
//O(n)
void *getItems(LIST *lp){
	assert(lp != NULL);
	void **num = malloc(sizeof(void*)*lp->count);
	assert(num != NULL);
	NODE *dn = lp->head;
	NODE *flag = dn->next;
	int i = 0;
	while (flag != dn){
		num[i] = flag->data;
		flag = flag->next;
		i++;
	}
	return num;
}

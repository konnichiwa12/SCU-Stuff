#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "pqueue.h"
#include "pack.h"
#define END 256
#define NODE struct node

int counts[END + 1];

static int depth(NODE *np);
static NODE* mkNode(int data, NODE *left, NODE *right);
static void readFile(char* filename);
static int NodeCmp(NODE *n1, NODE *n2);

NODE* nodes[END + 1];
//arguments: int and character pointer
//return: int
//function: first check whether there are enough arguments, then make an array of chars based on frequencies, then order then into a new array, then print out elements with frequency and number of bits
//O(n)
int main(int argc, char *argv[]){
	if (argc != 3){
		printf("Not enough command line arguments\n");
		return 0;
	}
	else{
		readFile(argv[1]);
	}
	PQ *pq = createQueue(NodeCmp);
	for (int i = 0; i < END; i++){
		if (counts[i] > 0){
			nodes[i] = mkNode(counts[i], NULL, NULL);
			addEntry(pq, nodes[i]);
		}
	}
	nodes[END] = mkNode(0 , NULL, NULL);
	addEntry(pq, nodes[END]);
	while(numEntries(pq) > 1){
		NODE* left = removeEntry(pq);
		NODE* right = removeEntry(pq);
		addEntry(pq, mkNode(left->count + right->count, left, right));
	}
	for (int i = 0; i <= END; i++){
		if (nodes[i] != NULL){
			if (isprint(i)){
				printf(" ' %c ' ", i);
			}
			else{
				printf("  %03o  ", i);
			}
			printf("%d x %d bits = %d bits\n", counts[i], depth(nodes[i]), counts[i]*depth(nodes[i]));
		}
	}
	pack(argv[1], argv[2], nodes);
	destroyQueue(pq);
	return 0;
}
//arguments: node pointer
//return: int
//function: return depth of a node
static int depth(NODE *np){
	assert(np != NULL);
	if (np->parent == NULL){
		return 0;
	}
	return 1 + depth(np->parent);
}
//arguments: int, 2 node pointers
//return: NODE pointer
//function: generate a node with two other nodes pointing to it
//O(1)
static NODE* mkNode(int data, NODE* left, NODE* right){
	NODE* np = malloc(sizeof(NODE));
	np->count = data;
	if (left != NULL){
		left->parent = np;
	}
	if (right != NULL){
		right->parent = np;
	}
	np->parent = NULL;
	return np;
}
//arguments: string
//return: void
//function: read a file and store frequency values
//O(n)
static void readFile(char* fileName){
	FILE* fp = fopen(fileName, "r");
	int c;
	if (fp == NULL){
		printf("readFile unsuccessful");
		return;
	}
	while ((c = getc(fp)) != EOF){
		counts[c]++;
	}
	fclose(fp);
	return;
}
//arguments: 2 node pointers
//return: int
//function: compare two ints and return result
//O(1)
static int NodeCmp(NODE* n1, NODE* n2){
	assert(n1 != NULL);
	assert(n2 != NULL);
	return n1->count - n2->count;
}


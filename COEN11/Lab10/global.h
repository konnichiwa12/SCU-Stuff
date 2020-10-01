#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

//initialize global variables/arrays/constants/structures
#define SIZE 10
#define LENGTH 10
#define NODE struct node
#define LIST struct list
struct node{
        char names[LENGTH];
        int size;
        NODE *next;
        NODE *prev;
};
struct list{
        NODE *first;
        NODE *last;
};
extern LIST  stuff[4];

extern pthread_mutex_t mutex;

void Insert(char *name, int number);
void Remove();
void showlist();
void SearchSize();
void Readfile(char *file, int k);
void Writefile(char *file, int k);
int searchCopies(char s[]);
void recursearrays();
void backwards(NODE *p);
void recursearraysname();
void recursenames(char *p);
void quitrecursive(NODE *p);
void quitarrays();
void* AutoSave(void *bname);
void ReadBfile(char *file);
void WriteBfile(char *file);

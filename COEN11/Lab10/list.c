#include "global.h"
//Arguments: character pointer, int
//return void
//function: reject command if list full, receive input(a string and an int) from user, put input into end of list
void Insert(char *name, int number){
        NODE *temp;
        temp = (NODE *)malloc (sizeof(NODE));
        pthread_mutex_lock(&mutex);
        if ((number == 1)||(number ==2)){
                if (stuff[0].first == NULL){
                        temp->next=NULL;
                        stuff[0].first = stuff[0].last = temp;
                        temp->prev=NULL;
                }
                else{
                        temp->next= NULL;
                        temp->prev=stuff[0].last;
                        stuff[0].last->next = temp;
                        stuff[0].last = temp;
                }
        strcpy(temp->names, name);
        temp->size = number;
        }
        else if ((number == 3)||(number == 4)){
                if (stuff[1].first == NULL){
                        temp->next = NULL;
                        stuff[1].first = stuff[1].last = temp;
                        temp->prev = NULL;
                }
                else{
                        temp->next=NULL;
                        temp->prev=stuff[1].last;
                        stuff[1].last->next = temp;
                        stuff[1].last = temp;
                }
        strcpy(temp->names, name);
        temp->size = number;
        }
        else if ((number == 5)||(number ==6)){
                if (stuff[2].first == NULL){
                        temp->next = NULL;
                        stuff[2].first = stuff[2].last = temp;
                        temp->prev = NULL;
                }
                else{
                        temp->next = NULL;
                        temp->prev=stuff[2].last;
                        stuff[2].last->next = temp;
                        stuff[2].last = temp;
                }
        strcpy(temp->names, name);
        temp->size = number;
        }
        else if (number > 6){
                if (stuff[3].first == NULL){
                        temp->next = NULL;
                        stuff[3].first = stuff[3].last = temp;
                        temp->prev = NULL;
                }
                else{
                        temp->next = NULL;
                        temp->prev = stuff[3].last;
                        stuff[3].last->next = temp;
                        stuff[3].last = temp;
                }
        strcpy(temp->names, name);
        temp->size = number;
        }
        pthread_mutex_unlock(&mutex);
        return;
}
//Arguments: A string (array of chars)
//return: an int (if a duplicate was found, return 1. Otherwise 0)
//function: go through the list and search for duplicates; return 1 if a duplicate was found, otherwise return 0
int searchCopies(char s[]){
        NODE *p;
        for (int x = 0; x < 4; x++){
                p = stuff[x].first;
                while(p != NULL){
                        if (strcmp(p->names, s) == 0){
                                return 1;
                        }
                        p = p->next;
                }
        }
        return 0;
}

//arguments: NODE point p
//return: void
//function: it will go through each  list element pointed by p and free each NODE
void quitrecursive(NODE *p){
        if (p == NULL){
                return;
        }
        else{
                quitrecursive(p->next);
                free(p);
        }
        return;
}

//arguments: void
//return: void
//function: go through each array and tell function quitrecursive which list to go through
void quitarrays(){
        NODE *p;
        for (int x = 0; x < 4; x++){
                p = stuff[x].first;
                if (p==NULL){
                        continue;
                }
                else{
                        quitrecursive(p);
                }
        }
        return;
}

//arguments: void
//return: void
//function: reject command if list empty, receive input(an int) from user, and remove first group with equal to or greater size
void Remove(){
        NODE *p;
        NODE *q;
        int x;
        int flag =0;
        int input = 0;
        printf("Please input the size of the party you want to delete\n");
        scanf("%d", &input);
        pthread_mutex_lock(&mutex);
        for (int x = 0; x <= input/2.1; x++){
                p = q = stuff[x].first;
                while (p!=NULL){
                        if (input >= p->size){
                                flag = 1;
                                if(stuff[x].first == stuff[x].last){
                                        stuff[x].first = NULL;
                                        stuff[x].last = NULL;
                                        free(p);
                                }
                                else if(p == stuff[x].first){
                                        stuff[x].first->next->prev = NULL;
                                        stuff[x].first = stuff[x].first->next;
                                        free(p);
                                }
                                else if(p == stuff[x].last){
                                        stuff[x].last->prev->next=NULL;
                                        stuff[x].last = q;
                                        stuff[x].last->next = NULL;
                                        free(p);
                                }
                                else{
                                        p->next->next->prev = q;
                                        q->next = p->next;
                                        free(p);
                                }
                                pthread_mutex_unlock(&mutex);
                                return;
                        }
                        q = p;
                        p = p->next;
                }
        }
        pthread_mutex_unlock(&mutex);
        if (flag == 0){
                printf("There is no reservation of that size\n");
        }
        return;
}

//arguments: void
//return: void
//function: show all elements of names and size in list
void showlist(){        
        NODE *p;        
        int x = 0;      
        p = stuff[0].first;
        for (x = 0; x < 4; x++){
                p = stuff[x].first;
                while (p != NULL){ 
                        printf("%s, %d\n", p->names, p->size);
                        p = p->next;
                }
        }
        return;
}       
        
//arguments: void
//return: void
//function: show all names whose size is less than or equal to input from user
void SearchSize(){
        NODE *p;
        int x;
        int flag =0;
        int input = 0;
        printf("Please input the size of the party you want to search for\n");
        scanf("%d", &input);
        for (x = 0; x <= input/2.1; x++){
                p = stuff[x].first;
                while (p != NULL){
                        if (p->size <= input){
                                flag = 1;
                                printf("%s\n", p->names);
                        }
                p = p->next;
                }
        }
        if (flag == 0){
                printf("There was no party found with that size\n");
                return;
        }
        return;
}
//arguments: void
//return void
//function: go through each array and tell function backwards which array it should printf backwards
void recursearrays(){
        NODE *p;
        for (int b = 3; b >= 0; b--){
                p = stuff[b].first;
                if (p==NULL){
                        continue;
                }
                else{
                        backwards(p);
                }
        }
        return;
}

//arguments: NODE pointer p
//return: void
//function: print each list, indicated by pointer p, backwards
void backwards(NODE *p){
        if (p->next == NULL){
                printf("%s\t\t%d\n", p->names, p->size);
                return;
        }
        backwards(p->next);
        printf("%s\t\t%d\n", p->names, p->size);
        return;
}
//arguments: void
//return: void
//function: go through arrays and give each name in list to function recursenames

void recursearraysname(){
        NODE *p;
        for (int x = 0; x < 4; x++){
                p = stuff[x].first;
                if (p==NULL){
                        continue;
                }
                else{
                        while (p!=NULL){
                                recursenames(p->names);
                                p = p->next;
                                printf("\n");
                        }
                }
        }
        return;
}
//arguments: char pointer s
//return: void
//function: receive each string in lists and print them backwards

void recursenames(char *s){
        if (*s =='\0'){
                return;
        }
        else{
                recursenames(s+1);
                printf("%c", *s);
        }
        return;
}

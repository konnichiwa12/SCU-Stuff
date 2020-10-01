//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//initialize global variables/arrays/constants/structures
#define SIZE 10
#define LENGTH 10
#define NODE struct node
#define LIST struct list
struct node{
        char names[LENGTH];
        int size;
	NODE *next;
};
struct list{
	NODE *first;
	NODE *last;
};
LIST  stuff[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

void Insert();
void Remove();
void showlist();
void SearchSize();

//arguments: void
//return: an int (0 only, to quit)
//Main function, loop forever to accept commands and call functions based on commands(1 to call Insert(), 2 to call Remove(), 3 to call showList(), 4 delete all reamining info and quit)
int main(void){
        int quitvariable = 1;
        int command = 0, number = 0;
        char name[LENGTH];
        for(;;){
                printf("Please put in one of the following commands: \n1 to insert \n2 to remove \n3 to show list \n4 to Search sizes\n0 to quit\n\n");
                scanf("%d", &command);
                if (command == 1){
                        Insert();
                }
                else if(command == 2){
                        Remove();
		}
                else if (command == 3){
                        showlist();
                }
                else if (command == 0){
			NODE *p;
                        for (int x = 0; x < 4; x++){
				p = stuff[x].first;
				while (stuff[x].first != NULL){
					stuff[x].first = stuff[x].first->next;
					free(p);
					p = stuff[x].first;
				}
			}
			return 0;
                }
                else if (command == 4){
                        SearchSize();
                }
                else{
                        printf("That is not one of the choices.\n");
                }
        }
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



//Arguments: none
//return: void
//function: reject command if list full, receive input(a string and an int) from user, put input into end of list
void Insert(){
	NODE *temp;
	temp = (NODE *)malloc (sizeof(NODE));
        char name[SIZE];
	int number;
	printf("What is your name? Put in up to 10 characters.\n");
        scanf("%s", name);
	if (searchCopies(name)==1){
		printf("There is already a group with that name\n");
		return;
	}
        printf("What is the size of your party?\n");
        scanf("%d", &number);	
        if ((number == 1)||(number ==2)){
		if (stuff[0].first == NULL){
			temp->next=NULL;
			stuff[0].first = stuff[0].last = temp;
		}
		else{
			temp->next= NULL;
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
		}
                else{
                	temp->next=NULL;
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
		}
                else{
			temp->next = NULL;
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
                }       
                else{
			temp->next = NULL;
                        stuff[3].last->next = temp;
                        stuff[3].last = temp;
                }
        strcpy(temp->names, name);
        temp->size = number;
        }
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
					stuff[x].first = stuff[x].first->next;
					free(p);
				}
				else if(p == stuff[x].last){
					stuff[x].last = q;
					stuff[x].last->next = NULL;
					free(p);
				}
				else{
					q->next = p->next;
					free(p);
				}
				return;
			}
			q = p;
			p = p->next;
		}
	}
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


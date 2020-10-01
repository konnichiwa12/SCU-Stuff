//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//initialize global variables/arrays/constants/structures
#define SIZE 10
#define LENGTH 10
#define NODE struct node
struct node{
        char names[LENGTH];
        int size;
	NODE *next;
};
NODE *head = NULL;
NODE *tail = NULL;

void Insert();
void Remove();
void showlist();
void SearchSize();

//arguments: void
//return: an int (0 only, to quit)
//Main function, loop forever to accept commands and call functions based on commands(1 to call Insert(), 2 to call Remove(), 3 to call showList(), 4 to quit program)
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
                        if (head == NULL){
				printf("Sorry, the list is empty\n");
			}
			else {
				Remove();
                	}
		}
                else if (command == 3){
                        showlist();
                }
                else if (command == 0){
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
        NODE *p=head;
        while (p!=NULL){
                if (strcmp(s, p->names)==0){
                        return 1;
                }
		p=p->next;
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
        strcpy(temp->names, name);	
	temp->size=number;
	if (head == NULL){
                temp->next=NULL;
		head = temp;
		tail = temp;
        }
        else{
        	temp->next=NULL;
		tail->next = temp;
		tail = temp;
        }
}
//arguments: void
//return: void
//function: reject command if list empty, receive input(an int) from user, and remove first group with that size
void Remove(){
        NODE *p=head;
	NODE *g=head->next;
        int flag =0;
        if (head == NULL){
                printf("Sorry, the list is already empty\n");
        }
        else{
                int input = 0;
                printf("Please input the size of the party you want to delete\n");
                scanf("%d", &input);
                int num = 0;
		if (p->size == input){
			head = g;
			p->next = NULL;
			free(p);
			return;
		}
                while (g!=NULL){
                        if (g->size == input){
                                if (p == head){
					p->next = g->next;
                                	free(g);
				}
				else if(g == tail){
					tail = p;
					p->next=NULL;
					free(g);
				}
				else{
					p->next = g->next;
					free(g);
				}
			return;
                        }
		g = g->next;
		p = p->next;
                }
                if (flag == 0){
                        printf("There is no reservation of that size\n");
             
                }
        }
}

//arguments: void
//return: void
//function: show all elements of names and size in list
void showlist(){
        NODE *p;
        p = head;
        if (head == NULL){
                printf("We are sorry, the list is empty\n");
                return;
        }
        while (p != NULL){
                printf ("Name: %s     Size of party: %d\n", p->names, p->size);
        	p=p->next;
	}
}
//arguments: void
//return: void
//function: show all names whose size is less than or equal to input from user
void SearchSize(){
        NODE *p;
	int flag = 0;
        p = head;
        int input;
        printf("What size are you looking for?\n");
        scanf("%d", &input);
        while (p != NULL){
                if (p->size <= input){
                        printf ("Name: %s     Size of party: %d\n", p->names, p->size);
                	p = p->next;
			flag = 1;
		}
        }
	if (flag == 0){
		printf("No parties were found");
	}
	return;
}


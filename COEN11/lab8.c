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
	NODE *prev;
};
struct list{
	NODE *first;
	NODE *last;
};
LIST  stuff[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

void Insert(char *name, int number);
void Remove();
void showlist();
void SearchSize();
void Readfile(char *file);
void Writefile();
int searchCopies(char s[]);
void recursearrays();
void backwards(NODE *p);
void recursearraysname();
void recursenames(char *p);
void quitrecursive(NODE *p);
void quitarrays();

//arguments: how many arguments there are (including ./a.out) and the file name (after ./a.out)
//return: an int (0 only, to quit)
//Main function, loop forever to accept commands and call functions based on commands(1 to call Insert(), 2 to call Remove(), 3 to call showList(), 4 delete all reamining info and quit)
int main(int argc, char *argv[]){
	if (argc==1){
		printf("The file name is missing\n");
		return 0;
	}
	else if (argc > 2){
		printf("Too many inputs\n");
		return 0;
	}
	Readfile(argv[1]);
	char name[10];
	int number;
        int quitvariable = 1;
        int command = 0;
        for(;;){
                printf("Please put in one of the following commands: \n1 to insert \n2 to remove \n3 to show list \n4 to Search sizes\n5 to show each list backwards\n6 to show all names backwards\n0 to quit\n\n");
                scanf("%d", &command);
                if (command == 1){
                        printf("What is your name? Put in up to 10 characters.\n");
        		scanf("%s", name);
        		if (searchCopies(name)==1){
                		printf("There is already a group with that name\n");
				break;
			}
			printf("What is the size of your group?\n");
			scanf("%d", &number);
			Insert(name, number);
		}
                else if(command == 2){
                        Remove();
		}
                else if (command == 3){
                        showlist();
                }
                else if (command == 0){
			NODE *p;
                        Writefile(argv[1]);
			quitarrays();
			return 0;
                }
                else if (command == 4){
                        SearchSize();
                }
		else if (command == 5){
			recursearrays();
		}
		else if (command == 6){
			recursearraysname();
		}
                else{
                        printf("That is not one of the choices.\n");
                }
        }
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



//Arguemtns: A char pointer that points a string with the file name
//return: void
//function: receive info from the file
void Readfile(char *file){
	FILE *fp;
	NODE *p;
	char s[] = " ";
	int d = 0;
	if ((fp = fopen(file, "r"))==NULL){
		printf("Cannot open file\n");
		return;
	}
	fseek(fp, 42, SEEK_SET);
	while (fscanf(fp, "%s\t\t%d\n", s, &d)==2){
		Insert(s, d);
	}
	fclose(fp);
	return;
}

//Arguemtns: A char pointer that points a string with the file name
//return: void
//function: orint info to the file
void Writefile(char *file){
	FILE *fp;
	char FL[] = "Name\t\tGroup Size\n";
	char SL[]= "________________________\n";
	if ((fp = fopen(file, "w"))==NULL){
		printf("Cannot open file\n");
		return;
	}
	fprintf(fp, "%s\n%s\n", FL, SL);
	NODE *p;
	for (int x = 0; x < 4; x++){
		p = stuff[x].first;
		while (p != NULL){
			fprintf(fp, "%s\t\t%d\n", p->names, p->size);
			p=p->next;
		}
	}
	fclose(fp);
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



//Arguments: none
//return: void
//function: reject command if list full, receive input(a string and an int) from user, put input into end of list
void Insert(char *name, int number){
	NODE *temp;
	temp = (NODE *)malloc (sizeof(NODE));
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

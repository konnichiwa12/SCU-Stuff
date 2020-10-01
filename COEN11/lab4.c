#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//initialize global variables/arrays/constants/structures
#define SIZE 10
#define LENGTH 10
union union_a{
	char named[LENGTH];
	int years;
	float ave;
};

typedef struct entry{
        char names[LENGTH];
        int size;
	int occasion;
	union union_a more;
}LIST;

int counter = 0;
LIST list[10];

//Arguments: A string (array of chars)
//return: an int (if a duplicate was found, return 1. Otherwise 0)
//function: go through the list and search for duplicates; return 1 if a duplicate was found, otherwise return 0
int searchCopies(char s[]){
        LIST *p;
        p = list;
        for (int x = 0; x < SIZE; p++,  x++){
                if (strcmp(s, p->names)==0){
                        return 1;
                }
        }
        return 0;
}



//Arguments: none
//return: void
//function: reject command if list full, receive input(a string, an int, an int for occasion, and a birthday name/anniversary year/average age in a union) from user, put input into arrays
void Insert(){
	int choice = 0;
        char name[SIZE];
        int number = 0;
        if (counter == SIZE - 1){
                printf("We are sorry, the queue is full\n");
        }
        else{
		printf("What is your name?\n");
                scanf("%s", name);
                printf("What is the size of your party?\n");
                scanf("%d", &number);
                if (searchCopies(name) == 1){
                        printf("There is already a party with that name\n");
                        return;
                }
		printf("What is the occasion? 1 for Birthday, 2 for Anniversary, 3 for other\n");
		scanf("%d", &choice);
		if (choice == 1){
			list[counter].occasion = 1;
		}
		else if (choice == 2){
			list[counter].occasion = 2;
		}
		else{
			list[counter].occasion = 3;
		}
                int actualnum = counter+1;
                strcpy(list[counter].names, name);
                list[counter].size = number;
		if (choice == 1){
			printf("Who's birthday is it?\n");
			scanf("%s", list[counter].more.named);
		}
		if (choice == 2){
			printf("How many years?\n");
			scanf("%d", &list[counter].more.years);
		}
		if (choice == 3){
			printf("Please put in the average age of the group\n");
			scanf("%f", &list[counter].more.ave);
		}
                printf("You are number %d on the list\n", actualnum);
                counter++;
        }
}
//arguments: void
//return: void
//function: reject command if list empty, receive input(an int) from user, and remove group with that size along with the occasion, and data inside union; move everything after up by one
void Remove(){
        LIST *p;
        int flag =0;
        if (counter == 0){
                printf("Sorry, the list is already empty\n");
        }
        else{
                int input = 0;
                printf("Please input the size of the party you want to delete\n");
                scanf("%d", &input);
                int num = 0;
                p = list;
                for (num = 0; num < SIZE; p++, num++){
                        if (p->size == input){
                                flag = 1;
                                for (int count = num; count < SIZE; p++, count++){
                                        strcpy(p->names, (p+1)->names);
                                        (p->size = (p+1)->size);
					(p->occasion = (p+1)->occasion);
					if ((p+1)->occasion == 1){
						strcpy(p->more.named, (p+1)->more.named);
					}
					if ((p+1)->occasion == 2){
						p->more.years = (p+1)->more.years;
					}
					if ((p+1)->occasion ==3){
						p->more.ave = (p+1)->more.ave;
					}
                                }
                        counter--;
                        num = SIZE;
                        }
                }
                if (flag == 0){
                        printf("There is no reservation of that size\n");
            	}
	}
}

//arguments: void
//return: void
//function: show all elements of names, size, occasion, and (based on the occasion) stuff inside the union
void showlist(){
        LIST *p;
        p = list;
        if (counter == 0){
                printf("We are sorry, the list is empty\n");
                return;
        }
        for (int x = 0; x < counter; p++, x++){
                printf("-------------------------------------------------------------------------------------\n");
		printf("Name: %s     Size of party: %d      \n", p->names, p->size);
		if (p->occasion == 1){
			printf("Occasion: Birthday       Birthday Name: %s\n", p->more.named);
		}
		else if (p->occasion == 2){
			printf("Occasion: Anniversary    Years: %d\n", p->more.years);
		}       
		else if (p->occasion ==3){
			printf("Occasion: Other          Avg Age: %.2f\n", p->more.ave);
		}
        }
	printf("-------------------------------------------------------------------------------------\n");
}
//arguments: void
//return: void
//function: show all names whose size is less than or equal to input from user
void SearchSize(){
        LIST *p;
        p = list;
        int input;
        printf("What size are you looking for?\n");
        scanf("%d", &input);
        for (int x = 0; x < counter; p++,  x++){
                if (p->size <= input){
			printf("%s    Size: %d     ", p->names, p->size);
			if (p->occasion == 1){
                        	printf("Occasion: Birthday       Birthday Name: %s\n", p->more.named);
                	}
                	else if (p->occasion == 2){
                        	printf("Occasion: Anniversary    Years: %d\n", p->more.years);
                	}
               		 else if (p->occasion ==3){
                       		printf("Occasion: Other          Avg Age: %.2f\n", p->more.ave);
                	}
                }
        }
	printf("---------------------------------------------\n");
}


//arguments: void
//reutrn: an int (0 only, to quit)
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
                if (command == 2){
                        Remove();
                }
                if (command == 3){
                        showlist();
                }
                if (command == 0){
                        return 0;
                }
                if (command == 4){
                        SearchSize();
                }
        }
}

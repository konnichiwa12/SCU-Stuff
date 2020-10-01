//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//initialize global variables/arrays/constants
#define SIZE 10
#define LENGTH 10
char names[SIZE][LENGTH];
int size[SIZE];
int counter = 0;

//Arguments: none
//return: void
//function: reject command if list full, receive input(a string and an int) from user, put input into arrays
void Insert(){
	char name[SIZE];
	int number = 0;
	if (counter == SIZE - 1){
		printf("We are sorry, the queue is full\n");
	}
	else{
		printf("What is your name? Put in up to 10 characters.\n");
		scanf("%s", name);
		printf("What is the size of your party?\n");
		scanf("%d", &number);
		int actualnum = counter+1;
		strcpy(names[counter], name);
		size[counter] = number;
		printf("You are number %d on the list\n", actualnum);
		counter++;
	}
}
//arguments: void
//return: void
//function: reject command if list empty, receive input(an int) from user, and remove group with that size
void Remove(){
	int flag =0;
	if (counter == 0){
		printf("Sorry, the list is already empty\n");
	}
	else{
	int input = 0;
	printf("Please input the size of the party you want to delete\n");
	scanf("%d", &input);
	int num = 0;
	for (num = 0; num < SIZE; num++){
		if (size[num] == input){
			flag = 1;
				for (int count = num; count < SIZE; count++){
					strcpy(names[count], names[count+1]);
					size[count] = size[count+1];
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
//function: show all elements of names and size arrays
void showlist(){
	for (int x = 0; x < counter; x++){
		printf ("Name: %s     Size of party: %d\n", names[x], size[x]);
	}
}



//arguments: void
//reutrn: an int (0 only, to quit)
//Main function, loop forever to accept commands and call functions based on commands(1 to call Insert(), 2 to call Remove(), 3 to call showList(), 4 to quit program)
int main(void){
	int quitvariable = 1;
	for (int x = 0; x < SIZE; x++){
	names[x][0] = '\0';
	}
	int command = 0, number = 0;
	char name[LENGTH];
	for(;;){
		printf("Please put in one of the following commands: \n1 to insert \n2 to remove \n3 to show list \n0 to quit\n\n");
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
	}	
}


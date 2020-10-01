//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function for getting input from user
int getInput (int top , int bottom){
	//initialize variables
        int value = top*bottom;
        int input = 0;
	int solution = value/bottom;
	//ask for input
        printf("What is the answer to %d / %d?\n", value, bottom);
        scanf("%d", &input);
	//return correct/incorrect value
        if (input == solution){
                return 1;
        }
        else{
                return 0;
        }
}

//to return right/wrong message based on input from user and ask questions
int main(void){
	//initialize variables and call rand() command
	srand((int)time(NULL));
	int answer = 0, numerator = 0, denominator = 0, score = 0;
	//ask questions
	for (int x=0; x < 10; x++){
		denominator = rand()%12+1;
		answer = rand()%13;
		call input getInput method
		if (getInput(answer, denominator) == 1){
			printf("That is correct!\n");
			score++;
		}
		else{
			printf("That is incorrect! The answer is %d\n", answer);
		}
	}
	//return score
	printf("You got %d/12 correct!\n", score);
	return 0;
}


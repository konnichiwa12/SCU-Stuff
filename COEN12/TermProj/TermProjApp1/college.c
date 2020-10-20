#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Ver1.h"
//arguments: void
//return: int
//function: trigger all functions in data set, print status updates of those functions, and print all elts at the end
//O(n)
int main(){
	printf("-----------------------------------\n");
	STRUCT *p;
	int maxElts = 3000;
	int preID = 0;
	p = createDataSet(maxElts);
	printf("generate 1000 students and insert\n");
    printf("-----------------------------------\n");
	srand(time(NULL));
	for(int i = 0; i < 1000; i++){
		int age = rand()%13 + 18;
		int ID;
		ID = rand()%2 + 1 + preID;
		printf("Inserting AGE: %d ID: %d\n", age, ID);
        insertDataSet(p, age, ID);
		preID = ID;
	}
    printf("-----------------------------------\n");
    printf("Initial List\n");
	printArray(p);
    printf("-----------------------------------\n");
	printf("generate one random student\n");
	int newID, newAge;
	newAge = rand()%13 + 18;
	newID = rand()%preID;
	int lobound, hibound;
    printf("Searching for Student AGE: %d, ID: %d\n", newAge, newID);
    int i;
    printf("-----------------------------------\n");
    if (searchBoundary(p, newAge, newID, &lobound, &hibound)==true){
        if (search2(p, lobound, hibound, newID, &i) == true){
            printf("Student Found at %d\n", i);
        }
        else{
            printf("Student not found\n");
        }
    }
    printf("-----------------------------------\n");
    printf("Generating Random Age to delete.\n");
    int delAge = rand()%13 + 18;
    int delLo, delHi;
    printf("Deleting Age: %d\n", delAge);
    if(searchBoundary(p, delAge, 0, &delLo, &delHi)==false){
        printf("No student to delete\n");
    }
    else{
        printf("%d to %d\n", delLo, delHi);
        deleteAge(p, delLo, delHi);
    }
    printf("-----------------------------------\n");
    printArray(p);
	int AgeGap = maxAgeGap(p);
	printf("Max Age Gap is %d\n" , AgeGap);
    printf("-----------------------------------\n");
	printf("End of main\n");
    destroyDataSet(p);
	printf("______________________\n");
}
	
	
		
		

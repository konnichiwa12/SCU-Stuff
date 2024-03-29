#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#define MAX 10
#include "Ver1F.h"

typedef struct st{
    int *age;
	int *id;
	int count;
	int length;
}STRUCT;


//by chaining
STRUCT *createDataSet(int maxElts){
	assert(maxElts > 0);
	STRUCT *sp = malloc(sizeof(STRUCT));
	assert(sp != NULL);
    sp->age = malloc(sizeof(int)*maxElts);
    sp->id = malloc(sizeof(int)*maxElts);
    assert(sp->age != NULL && sp->id != NULL);
	sp->count = 0;
	sp->length = maxElts;
	return sp;
}

void destroyDataSet(STRUCT *sp){
	assert (sp != NULL);
	free(sp->age);
	free(sp->id);
	free(sp);
	return;
}

bool search(STRUCT *sp, int searchage, int searchid, int *returnindex){
    assert(sp != NULL);
	int hi = sp->count - 1;
	int lo = 0;
	int mid = 0;
	while (lo <= hi){
		mid = (hi + lo)/2;
		if (searchage == sp->age[mid]){
            *returnindex = mid;
			return true;//student found
		}
		if (searchage > sp->age[mid]){
			lo = mid + 1;
		}
		else{
            hi = mid - 1;
		}
	}
    *returnindex = mid;
	return false;//student not found
}

bool search2(STRUCT *sp, int lo, int hi, int searchID, int *returnindex){
    assert(sp != NULL);
    int mid;
    while (lo <= hi){
        mid = (hi + lo)/2;
        if (searchID == sp->id[mid]){
            *returnindex = mid;
            return true;//student found
        }
        if (searchID > sp->id[mid]){
            lo = mid + 1;
        }
        else{
            hi = mid - 1;
        }
    }
    return false;//student not found
}

void insertDataSet(STRUCT *sp, int searchage, int searchid){
	assert(sp != NULL);
	if (sp->count == sp->length){
		printf("list is full\n");
		return;
	}
	int index;
    int endindex = sp->count;
    bool condition = search(sp, searchage, searchid, &index);
    if(condition == true){
        while(endindex > index){
            sp->age[endindex] = sp->age[endindex - 1];
            sp->id[endindex] = sp->id[endindex - 1];
            endindex--;
        }
        sp->age[index] = searchage;
        sp->id[index] = searchid;
        sp->count++;
    }
    else{
        if(index != sp->count && sp->age[index] < searchage){
            while(endindex > index + 1){
                sp->age[endindex] = sp->age[endindex - 1];
                sp->id[endindex] = sp->id[endindex - 1];
                endindex--;
            }
            sp->age[index + 1] = searchage;
            sp->id[index + 1] = searchid;
        }
        else{
            while (endindex > index){
                sp->age[endindex] = sp->age[endindex - 1];
                sp->id[endindex] = sp->id[endindex - 1];
                endindex--;
            }
            sp->age[index] = searchage;
            sp->id[index] = searchid;
        }
        sp->count++;
    }
    return;
}
bool searchBoundary(STRUCT *sp, int searchage, int searchid, int *low, int *high){
    assert(sp != NULL);
    int index;
    if(search(sp, searchage, searchid, &index)==false){
        printf("Student/Age not found\n");
        return false;
    }
    int after = index, before = index;
	while((after < sp->count)&&(sp->age[after + 1] == searchage)){
		after++;
	}
	while ((before > 0)&&(sp->age[before - 1] == searchage)){
		before--;
	}
    *low = before;
    *high = after;
	//print range of students
	return true;
}
void deleteAge(STRUCT *sp, int lobound, int hibound){
    assert(sp != NULL);
    int difference = hibound - lobound + 1;
    int *newAGE = malloc(sizeof(int)*sp->length);
    int *newID = malloc(sizeof(int)*sp->length);
    for(int i = 0; i < lobound; i++){
        newAGE[i] = sp->age[i];
        newID[i] = sp->id[i];
    }
    int j = lobound;
    for(int i = lobound + difference; i < sp->count; i++){
        newAGE[j] = sp->age[i];
        newID[j] = sp->id[i];
        j++;
    }
    sp->age = newAGE;
    sp->id = newID;
    sp->count-=difference;
    return;
}



int maxAgeGap(STRUCT *sp){
	int min = sp->age[0];
	int max = sp->age[sp->count-1];
	printf("min = %d, max = %d\n", min, max);
	return (max - min);
}

void printArray(STRUCT *sp){
	for (int i = 0; i < sp->count; i++){
		printf("Age: %d, ID: %d\n", sp->age[i], sp->id[i]);
	}
	printf("Print done\n");
	return;
}

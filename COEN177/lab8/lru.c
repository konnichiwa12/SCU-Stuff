// Name: Dillon Kanai 
// Date: 11/12/20
// Title: Lab8 – FIFO.c
// Description: Implements FIFO

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
  int pageno;
  int age;
} ref_page;



int main(int argc, char *argv[]) {
  int cacheSize = atoi(argv[1]);	
  ref_page cache[cacheSize]; // Cache that stores pages 
  char pageCache[100]; // Cache that holds the input from test file
  int totalFaults = 0, totalRequests = 0; // keeps track of the total page faults and total requests
  int placeInArray = 0, page_num = 0, i, j, a;
  bool foundInCache = false;

  for (i = 0; i < cacheSize; i++){//initialize all pageno and age values
    cache[i].pageno = -1;
    cache[i].age = 0;
  }
  
  int oldestage, oldestindex;

  while (fgets(pageCache, 100, stdin)) { 
    page_num = atoi(pageCache); // Stores number read from file as an int
    totalRequests++;//update count of total requests
    oldestage = cache[0].age;//set temp value
    for (i = 0; i < cacheSize; i++){//while there are still numbers to be read
      if (cache[i].pageno == page_num){
	foundInCache = true;//if a pagenum is found, set bool to true and set age of accessed page to 0
        cache[i].age = 0;
	break;
      }
    }
    if (foundInCache == false){//if there is a page fault
      printf("Page %d has faulted\n", page_num);
      totalFaults++;//update number of page faults
      oldestage = 0;
      for (j = 0; j < cacheSize; j++){//find oldest cache member
	if (cache[j].age > oldestage){
	  oldestage = cache[j].age;
	  oldestindex = j;
	}
      }
      cache[oldestindex].pageno = page_num;//replace oldest cache member
      cache[oldestindex].age = -1;
      for (a = 0; a < cacheSize; a++){
	cache[a].age++;//increment age of everything in cache
      }
    }
    foundInCache = false;
  }
  //printf("Total of %d requests received\n", totalRequests);
  //printf("Total of %d pages faulted\n", totalFaults);
  double hitrate = (totalRequests-totalFaults)/(double)totalRequests;
  //printf("Hit rate: %f\n", hitrate);
  return 0;
}


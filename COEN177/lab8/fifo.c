// Name: Dillon Kanai 
// Date: 11/12/20
// Title: Lab8 – FIFO.c
// Description: Implements FIFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno; 
} ref_page;



int main(int argc, char *argv[]) {
	int cacheSize = atoi(argv[1]);	
	ref_page cache[cacheSize]; // Cache that stores pages 
	char pageCache[100]; // Cache that holds the input from test file
	int totalFaults = 0, totalRequests = 0; // keeps track of the total page faults and total requests
	int placeInArray = 0, page_num = 0, i;
	bool foundInCache = false;
	
	for(i = 0; i < cacheSize; i++){//initialize all numbers to -1
	  cache[i].pageno = -1; 
	}
	
	while (fgets(pageCache, 100, stdin)) {//while there are still numbers to be read              
		page_num = atoi(pageCache); // Stores number read from file as an int
		totalRequests++;//count how many requests are made
		for (i=0; i<cacheSize; i++){//find pagenum in cache
		  if (cache[i].pageno == page_num){
        	       foundInCache = true;
        	       break; //break out loop because found page_num in cache  
		  }        	
		  if (i == cacheSize - 1){//if we reach the end
		    //You may print the page that caused the page fault
		    printf("Page %d has faulted\n", page_num);
		    cache[placeInArray].pageno = page_num;//replace page number
		    totalFaults++;//update count of page faults
		    placeInArray = (placeInArray + 1)%cacheSize; //Need to keep the value within the cacheSize
		  }
    	
		}
	}   

	printf("Total of %d requests received\n", totalRequests);
	printf("Total of %d pages faulted\n", totalFaults);
    double hitrate = (totalRequests-totalFaults)/(double)totalRequests;
    printf("Hit rate: %f\n", hitrate);	
}

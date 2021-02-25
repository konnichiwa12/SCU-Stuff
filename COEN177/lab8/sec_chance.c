#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct{     
        int pageno;
        int chance;
}   ref_page;

int main(int argc, char *argv[]) {
    int cacheSize = atoi(argv[1]);
    ref_page cache[cacheSize]; 
    char pageCache[100];
    int totalFaults = 0, totalRequests = 0;
    int counter = 0;
    int page_num,i, j;
    bool notfound;
    for(i = 0; i < cacheSize; i++) { //initialize cache values                              
        cache[i].pageno = -1;
        cache[i].chance = 0;
    }

    while(fgets(pageCache, 100, stdin)) {//while there are still values to be read
        page_num = atoi(pageCache);
        totalRequests++;//update count of total requests
        for(i = 0; i < cacheSize; i++) {     //search for pageno                      
	  if(cache[i].pageno == page_num) { //if found, set second chance variable to 1                  
                cache[i].chance = 1;                     
                notfound = false;                                     
                break;
            }
	  if(i == cacheSize - 1) //if not found, set bool to true, enable code to enter next if statement                                  
                notfound = true;                                      
        }
        if(notfound) {   //if there is a page fault                                          
	  printf("Page %d has faulted\n", page_num);
            totalFaults++;
            for(j = counter; j < cacheSize; j++) {  //resume iterating from where we left off and search for elt where second chance = 0               
	      if(cache[j].chance == 1) {  //if element still has a second chance, set chance of elt to 0             
                    cache[j].chance = 0;                 
                    counter++;                  
                    if(counter == cacheSize) { //equivalent of mod, but also change j                    
                        counter = 0;                            
                        j = -1;                                  
                    }
                }
	      else { //if an elt with chance = 0, replace that page                                         
                    cache[j].pageno = page_num;                
                    cache[j].chance = 0;
                    counter = (counter+1) % cacheSize;
                    break;
                }
            }
        }
	notfound = false;
    }
    double hitrate = (totalRequests - totalFaults) / (double)totalRequests;
    //printf("Total Requests: %d\n", totalRequests);
    //printf("Total Faults: %d\n", totalFaults);
    //printf("Hitrate of %f\n", hitrate);
    return 0;
}

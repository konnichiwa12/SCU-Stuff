#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

//in msecs
int RTT0 = 3, RTT1 = 20, RTT2 = 26, RTTHTTP = 47, n;
int i = 0;

int main(int argc, char* argv){
    A();
    B();
    C();
    return 0;
}

int A(){
    printf("Part A: %dms\n", RTT0 + RTT1 + RTT2 + 2*RTTHTTP);
}

int B(){
    printf("Part B: %dms\n", RTT0 + RTT1 + RTT2 + 14*RTTHTTP);
}

int C(){
    int list[12];
    int RTT012 = RTT0 + RTT1 + RTT2;
    //non-persistent
    list[0] = RTT012 + 14*RTTHTTP;//1 parallel
    list[1] = RTT012 + 8*RTTHTTP;//2 parallel
    list[2] = RTT012 + 6*RTTHTTP;//3 parallel
    list[3] = RTT012 + 6*RTTHTTP;//4 parallel
    list[4] = RTT012 + 6*RTTHTTP;//5 parallel
    list[5] = RTT012 + 4*RTTHTTP;//6 parallel
    for (i = 0; i < 6; i++){
        printf("Non-persistent %d parallel connections: %dms\n", i + 1, list[i]);
    }

    //persistent
    list[6] = RTT012 + 8*RTTHTTP;//1 parallel
    list[7] = RTT012 + 5*RTTHTTP;//2 parallel
    list[8] = RTT012 + 4*RTTHTTP;//3 parallel
    list[9] = RTT012 + 4*RTTHTTP;//4 parallel
    list[10] = RTT012 + 4*RTTHTTP;//5 parallel
    list[11] = RTT012 + 3*RTTHTTP;//6 parallel

    for (i = 6; i < 12; i++){
        printf("Persistent %d parallel connections: %dms\n", i + 1, list[i]);
    }
}



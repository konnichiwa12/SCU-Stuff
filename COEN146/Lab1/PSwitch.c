// Name: Dillon Kanai
// Date: 1/5/2020 
// Title: Lab1 – CSwitch
// Description: This file demonstrates the behavior of a Packet Switch


#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>
#include <math.h>

//factorial function
double fact(int a){
	double total = 1;
	int i = 1;
	for (i = 1; i <= a; i++){
		total = total * i;
	}
	return total;
}

int main(int argc, char *argv[]){
	
	double pPSusers, tPSusers = 0.10;
	int nPSusers = 19;
	pPSusers = tPSusers;
	
	printf("A - pPSusers = %f\n", pPSusers);//a
	
	double pPSusersNotBusy = 1 - pPSusers;//b
	printf("B - pPSusersNotBusy = %f\n", pPSusersNotBusy);
	
	printf("C - The probability that all of the other specific other users are not busy: %f\n", pow((double)1 - pPSusers, (double)nPSusers - (double)1));//c
	
	printf("D - The probability that one specific user is transmitting and the remaining users are not transmitting: %f\n", pPSusers * pow(pPSusersNotBusy, (double)nPSusers - (double)1));//d
	
	printf("E - The probability that exactly one (anyone) of thenPSusersusers is busy is: %f\n", nPSusers * pPSusers * pow(pPSusersNotBusy, (double)nPSusers - (double)1));//e

	printf("F - The probability that 10 specific users of nPSusers are transmitting and the others are idle: %g\n", pow(pPSusers, (double)10) * pow(pPSusersNotBusy, (double)(nPSusers - 10)));//f

	printf("G - The probability that any 10 users of nPSusersare transmitting and the others are idle: %g\n", (fact(nPSusers) / (fact(10) * fact(nPSusers - 10))) * pow(pPSusers, (double) 10) * pow(pPSusersNotBusy, (double)(nPSusers - 10)));
	
//H
	double h;
	int i;
	for (i = 11; i < nPSusers; i++){
		h += (fact(nPSusers) / (fact(i) * fact(nPSusers - i))) * pow(pPSusers, i) * pow(pPSusersNotBusy, (double)(nPSusers - i));
	}
	printf("H - The probability that more than 10 users of nPSusersare transmitting and the others are idle %g\n", h);
	return 0;
}

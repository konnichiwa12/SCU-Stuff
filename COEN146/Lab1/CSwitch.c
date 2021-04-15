// Name: Dillon Kanai
// Date: 1/5/2020 
// Title: Lab1 – CSwitch
// Description: This file demonstrates the behavior of a Circuit Switch


#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>

int main(int argc, char *argv[]){
	
	//hardcoded values
	int nCSusers, linkBandwidth = 200, userBandwidth = 20;
	//print
	printf("nCSusers = %d users\n", linkBandwidth/userBandwidth);

	return 0;
}

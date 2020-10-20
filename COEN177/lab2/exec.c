// Name: Dillon Kanai
// // Date: 10/1/20
// // Title: exec.c
// // Description: Use execlp() to make the console do the ls command

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <sys/wait.h>
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    	pid_t  pid;
    	printf("\n Before executing.\n");
    	pid = fork();
    	if (pid == -1) {
        	fprintf(stderr, "can't fork, error %d\n", errno);
    	}
  	else if(pid == 0){
		execlp("/bin/ls", "ls", NULL);
    	}
	else{
	        wait(NULL);
	        printf("Child Complete");
	        exit(0);
	}
}

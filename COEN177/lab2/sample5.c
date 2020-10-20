// Name: Dillon Kanai
// // Date: 10/1/20
// // Title: sample5.c
// // Description: Use fork() to create 7 processes including the original parent process

/*Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function with command-line arguments to pass */

//main function
int main(int argc, char *argv[]) {
        pid_t  pid;
        printf("\n Before forking.\n");
	//call make2 function to create two children
        pid = make2();
	//if pid is a child, create two more children
        //newly created children from first iteration of make2() are now parents
	if (!pid){
                make2();
                wait();//wait for children to finish
                printf("\t \t \t \tChild Process ID: %d, Parent Process ID: %d\n", getpid(), getppid());
        }
	//if pid is a parent, print
        else{
                wait();
                printf("Original Process ID: %d\n", getpid());
        }
        return 0;

}

pid_t make2(){
        pid_t pid;
	//create a child
        pid = fork();
        if (pid == -1){
                printf("Error\n");
        }
	//create child if parent is calling
        else if (pid){
                pid = fork();
		if (pid == -1){
			printf("Error\n");
		}
        }//we should have two children for the parent process
        return pid;
}



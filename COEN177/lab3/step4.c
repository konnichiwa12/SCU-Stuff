/*Sample C program for Lab assignment 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 
// main
int main(int argc,char *argv[]){
	int  fds[2];   
	char buff[60];   
	int count;   
	int i;   
	pipe(fds);      
	if (fork()==0){  //stdout     
		printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);       
		//designate as writer
		dup2(fds[1], 1);
		close(fds[0]);       
		//send command to reader
		execlp("/bin/cat", "cat", "/etc/passwd", 0);
		exit(0);
	}
	else if(fork()==0){ //stdin      
		printf("\nReader on the downstream end of the pipe \n");       
		dup2(fds[0], 0);
		close(fds[1]);     
		//print out all elements that contain "root"
		execlp("/bin/grep", "grep", "root", 0);
		exit(0);    
	}   
	else{           
		//close pipe
		close(fds[0]);      
		close(fds[1]);      
		wait(0);      
		wait(0);   
	}
	return 0;
}

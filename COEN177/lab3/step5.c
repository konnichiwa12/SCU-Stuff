#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 
// main
int main(int argc,char *argv[]){
 	int  fds[2];   
 	char buff[60];
	char buff2[60];
 	int i;   
 	// fd[0] = read
 	// fd[1] = write
	pipe(fds);
	if (fork()==0){//stdout       
		printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);       
		//designate as writer
		close(fds[0]); 
		//get input      
		scanf("%s", &buff2);
		//send through pipe to reader
		write(fds[1], buff2, strlen(buff2));
		exit(0);
	}
	else if(fork()==0){       
		printf("\nReader on the downstream end of the pipe \n");       
		//designate as reader
		close(fds[1]);       
		//receive from writer
		read(fds[0], buff, 60);
		//print out message
		write(1, buff, strlen(buff));
		printf("\n");
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


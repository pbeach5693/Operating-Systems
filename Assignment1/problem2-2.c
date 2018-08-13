//problem2-2.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//The size of the buffer will be 400 because that is the 
//size of the char array (20 x 20) in sort.c and pre.c
//anything larger will be a waste of memory
#define MSGSIZE 400


int main() {
	
    char inbuf[MSGSIZE];
    int p[2];
    pid_t pid;

    if (pipe(p) == -1)
     {
        perror("pipe call"); // from example code pipe2.c
        exit(1);
    }
	pid = fork();
	
	if(pid == -1)
	{
		perror("fork call");
		exit(2);
	}
	else if(pid == 0)
	{
		close(1);
        dup(p[1]); 
        close(p[0]);
        close(p[1]);
        //call pre.c
        //output from pre.c will be stored in the buffer
        execl("./pre", "pre",(char *)0);
        perror("execl() failed!");
     }
     else
     {
		 close(0);
         dup(p[0]);
         close(p[0]);
         close(p[1]);
         //call sort.c, and send the data from the buffer taken from pre.c
         execl("./sort", "sort", (char *)0);    
	  }

    exit(0);
}

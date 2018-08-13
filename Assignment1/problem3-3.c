//problem3-3
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

main(int argc, char* argv[])
{
	pid_t pid;
	char arguments[100][10] = {""}; //can hold up to 100 arguments
	char argumentString[500] = {""};	
	int stringCounter = 0;

	switch(pid = fork()) 
	{
	case -1: perror("fork failed");
			break;

	case 0: 
			execvp(argv[1], &argv[1]);
	
			printf("The child's pid is %d\n", getpid());
			printf("The parent's pid is %d.\n", getppid());
			printf("\n");		

			perror("exec failed");
			
			break;

	default: // parent uses wait to suspend execution until child finishes
			wait((int *)0);
			printf("command completed\n");
			exit(0);
  }
}
       

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
/*
			if(argc > 1)
				for(int i = 1; i < argc; i++)
					{
						strcpy(arguments[i-1], argv[i]);
						
						for(int a = 0; a < strlen(argv[i]); a++)
						{
							argumentString[stringCounter++] = arguments[i-1][a];
						}
						argumentString[stringCounter++] = ' ';
*/
//					}			
					
	//		 char * const av[] = {"ls", "-l", "-t", (char *)0};
			//char * const a[] = &argumentString;		
			
//			argumentString[stringCounter] = NULL;
//			char* a = &argumentString[0];
	
	execvp(argv[1], &argv[1]);
	
			
//			printf(a, "\n");
//			execv("/bin/ls", arguments);
//			execvp(path, argv);			premission denied
//			system(argumentString);
//			execv(argumentString, (char*) NULL);	
//			execvp			
//			execl(argumentString, (char*) NULL);

			printf("The child's pid is %d\n", getpid());
			printf("The parent's pid is %d.\n", getppid());
			printf("\n");		

			perror("exec failed");
			
		
			break;

	default: // parent uses wait to suspend execution until child finishes
			wait((int *)0);
			printf("command completed\n");
//			printf("The child's pid is %d\n", getpid());
//			printf("The parent's pid is %d.\n", getppid());
			exit(0);
  }
}
       

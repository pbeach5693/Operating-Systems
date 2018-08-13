/*			Patrick Beach			*/
#include <stdio.h>
#include <sys/types.h>#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

main()
{
	
	char *path, *argv[20], buf[80], n, *p;
	int m, status, inword, continu;
	
	//pipe resources
	int leftPipe[2], rightPipe[2], argumentCount, pipeCount;
	pid_t pid;
	
	//redirection
	int inputRedirect, outputRedirect;

	
	while(1)
	{	
		inword = 0;
		p = buf;
		m = 0;
		continu=0;
		pipeCount = 0;			
		argumentCount = 0;		//argument count (used in redirection)
		pid = 0;
		inputRedirect = 0;		//for redirection, says if < is used
		outputRedirect = 0;		//for redirection, says if > is used
		int arguments[20] = {0};	//array keeping track of arguments
		
		
		printf( "\nshhh> ");
	
		while ( ( n = getchar() ) != '\n'  || continu ) 
		{
			if ( n ==  ' ' ) 
			{ 
				if ( inword ) 
				{
					inword = 0;
					*p++ = 0;
				} 	
			}
			else if ( n == '\n' ) continu = 0;
			else if ( n == '\\' && !inword ) continu = 1;
			else 
			{
				if ( !inword ) 
				{
					inword = 1;
					argv[m++] = p;
					*p++ = n;
				}
				else 
					*p++ = n;			}		}		
		*p++ = 0;

		argv[m] = 0;
		
		if(strcmp(argv[0], "exit") == 0)
			exit(0);
		
        while(argv[argumentCount] != 0) 
        {
			//checks if argument is a pipe command
            if(strcmp(argv[argumentCount], "|") == 0)
             {
				//argument will be set to zero in this case
				//since we will manage the redirection ourselves
                argv[argumentCount] = 0;
                arguments[pipeCount + 1] = argumentCount + 1;
                ++pipeCount;
            }
            //checks if argument is a redirect left command
            else if(strcmp(argv[argumentCount], "<") == 0)
             {
				// < and > will affect the argument arrays and 
				//paths euqally.
				//the only difference is that we will set redirect
				//to true contengent upon which one is activated.
                path = strdup(argv[argumentCount + 1]); 
                argv[argumentCount] = 0;
                argv[argumentCount + 1] = 0;
                inputRedirect = 1;		//sets input to true
            }
            //checks if argument is a redirect right command
            else if(strcmp(argv[argumentCount], ">") == 0) 
            {
				// the </> arguments will be set to zero
				//so will the command after it, because it 
				//will be a file and not an argument.
                path = strdup(argv[argumentCount + 1]);
                argv[argumentCount] = 0;
                argv[argumentCount + 1] = 0;
                outputRedirect = 1;		//sets output to true
            }
            else 
                arguments[argumentCount] = argumentCount;

            argumentCount++;
        } 
			
			
			
			
        for (int i = 0; i <= pipeCount; i++) 
        {
            if(i < pipeCount) 
                pipe(rightPipe); 
                
                pid = fork();
		
		        if(pid == -1)
		        {
					perror("fork failed");
					exit(2);
				}
                else if(pid == 0)
                {
					if((i == 0 )&& (inputRedirect == 1))
					{
						//open input file, or from STDout of last program
						//will only read
						int input = open(path, O_RDONLY, 0600);
						
						if(input == -1)
						{
							printf("failed to open file");
							return(EXIT_FAILURE);
						}
						else
						{
							dup2(input, 0);	
							close(input);	//closes input file
						}
					}
					else if((i == pipeCount) && (outputRedirect == 1))
					{
						//open output file
						// | O_CREAT will make a file if one doesn't exist yet
						int output = open(path, O_WRONLY | O_CREAT, 0600);
						
						if(output == -1)
						{
							//if for some reason output cannot be generated
							printf("output failed");
							return(EXIT_FAILURE);
						}
						else
						{
							//copies output to file created/opened earlier
							dup2(output, 1);
							close(output);	//closes output file
						}		
					}
					
					//pipe management 
				    if (pipeCount > 0) 
				    {
                        if (i == 0)
                        { 
							//through the first iteration of the loop
							//i will equal 0 and the first child process
							//will be created
							//first child process only has rightPipe to close
                            close(1);
                            dup(rightPipe[1]);
                            close(rightPipe[1]);
                            close(rightPipe[0]);
                        }
                        else if (i < pipeCount)
                        { 
							//all child processes other than the first
							//and the the last will be managed here
							//middle processes have left and right pipes to close
                            close(0);
                            dup(leftPipe[0]);
                            close(leftPipe[0]);
                            close(leftPipe[1]);
                            close(1);
                            dup(rightPipe[1]);
                            close(rightPipe[0]);
                            close(rightPipe[1]);
                        }
                        else 
                        { 
							//last child process
							//last process only has remaining left pipe to close
                            close(0);
                            dup(leftPipe[0]);
                            close(leftPipe[0]);
                            close(leftPipe[1]);
                            }
                        }
									
					//execute the arguments
					execvp(argv[arguments[i]], &argv[arguments[i]]);
	
				}
				else //parent process
				{
					//parent process will set left pipes to right pipes
					if(i > 0)
					{
						close(leftPipe[0]);
						close(leftPipe[1]);
					}
					
					leftPipe[0] = rightPipe[0];
					leftPipe[1] = rightPipe[1];		
					
				}
            }

        if(strcmp(argv[0], "exit") == 0)
			exit(0);

		wait(&status);
	}
}

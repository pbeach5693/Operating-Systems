//pre.c
#include<stdio.h>

main()
{

	char name[20][20];
	int class[20] = {0};
	int userCount = 0;
	int charCount = 0;
	int c = 0;
	
	/*
	printf("Directions\n");
	printf("Please enter a student and the number of classes they're taking\n");
	printf("leave a space after the name and then enter the number of classes\n");
	printf("Hit the enter key after entering the number of courses the student is taking\n");
	printf("Press Ctrl-D to terminate input\n\n");
	printf("Here is an example of how user should input data:\n");
	printf("Susan 0\n");
	printf("Mary 8\n");
	printf("Bob 1\n");
	printf("John 7\n");
	printf("\nEnter your data:\n");
	*/
	while((c = getchar()) != EOF)
	{
		if(c >= '0' && c <= '9')
			if(class[userCount] != 0)
				class[userCount] = 10 + (c - '0');
			else
				class[userCount] += (c - '0');
		else if(c == '\n')
		{
			userCount++;
			charCount = 0;
		}
		else
		{
			name[userCount][charCount] = c;
			charCount++;
		}		
	}
	
	
//	printf("\n\nStudents taking more than 5 courses\n\n");
	
	for(int i = 0; i < userCount; i++)
	{
		int a = 0;

		if(class[i] > 5)
		{
			while(name[i][a] != ' ')
			{
				putchar(name[i][a]);
				a++;
			}
			printf("\n");
		}
	}
	
	
	


}

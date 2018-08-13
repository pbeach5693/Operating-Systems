#include <stdio.h>

//void swap(


main()
{
	char name[20][20] = {0};
	int index[20] = {0};
	int temp[20] = {0};
	int userCount = 0;
	int charCount = 0;
	int c = 0;
	int indexCount = 0;
	/*
	printf("Directions\n");
	printf("Please enter name followed by the enter key\n");
	printf("When you are finished entering names, press Ctrl - D\n");
	printf("Example:\n");
	printf("Susan\n");
	printf("Mary\n");
	printf("John\n");
	printf("Enter your data:\n");
	*/	
	
	
	while((c = getchar()) != EOF)
	{
		if(c == '\n')
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

	
	//Sorting function
	int a = 0;
	while(a <= 26)
	{
		for(int nameCounter = 0; nameCounter < userCount; nameCounter++)
		{
				if(65 + a == name[nameCounter][0])
					index[indexCount++] = nameCounter;
			
				if(97 + a == name[nameCounter][0])
					index[indexCount++] = nameCounter;	
		}	
		a++;
	}
	printf("\n\n");	
	
//	printf("Names in alphabetic order:\n");
	
	
	for(int i = 0; i < userCount; i++)
	{

		if((name[index[i]][0] + 32) == name[index[i]+1][0])
		{
			for(int a = 0; a < 20; a++)
				{
					temp[a] = name[index[i]][a];
					name[index[i]][a] =  name[index[i]+1][a];
					name[index[i]+1][a] = temp[a];
				}	
		}
	}
		
	
	for(int i = 0; i < userCount; i++)
	{
		for(int a = 0; a < 20; a++)
			putchar(name[index[i]][a]);
		
		printf("\n");
	}

}

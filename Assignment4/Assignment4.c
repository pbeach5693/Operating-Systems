//Patrick Beach
//Operating Systems - Assignment 4
#include <stdio.h>

void LRU(int inputSet[], int setSize, int frames);
void Optimal(int inputSet[], int setSize, int frames);
void FIFO(int inputSet[], int setSize, int frames);

int main()
{
	
	int inputSet[30] = {};
	int setSize = 0;
	int frames;
	
			
	//initialize inputSet to -1
	for(int i = 0; i < 30; i++)
		inputSet[i] = -1;
	
	
	printf("Please enter a reference string in the format ");
	printf("e.g. 2 1 3 4 5 2 3\n");
	printf("Your string: ");
	
	while((inputSet[setSize++] = getchar()) != '\n')
	{
			if(inputSet[setSize-1] == ' ')
				setSize--;
	}
	
	setSize--;
	
	printf("\n");
	printf("Please enter the number of frames: ");
	scanf("%d", &frames);
	printf("\n\n");



	printf("\n\n\nLRU Algorithm:");
	for(int i = 0; i < setSize; i++)
	{
		putchar(inputSet[i]);
		putchar(' ');
	}
	LRU(inputSet, setSize, frames);
	
	printf("\n\n\nOptimal Algorithm:");
	for(int i = 0; i < setSize; i++)
	{
		putchar(inputSet[i]);
		putchar(' ');
	}
	Optimal(inputSet, setSize, frames);
	
	printf("\n\n\nFIFO Algorithm");
	for(int i = 0; i < setSize; i++)
	{
		putchar(inputSet[i]);
		putchar(' ');
	}
	FIFO(inputSet, setSize, frames);



}

void LRU(int inputSet[], int setSize, int frames)
{
    int frameCounter[frames], temp[frames];
    int position;
    int a, b;
    int faults = 0;

    for(int i = 0; i < frames; i++)
          frameCounter[i] = -1;

    for(int n = 0; n < setSize; n++)
    {
          a = 0;
          b = 0;
            
          for(int m = 0; m < frames; m++)
                if(frameCounter[m] == inputSet[n])
                {
                      a = 1;
                      b = 1;
                      break;
                }
            
          if(a == 0)
                for(int m = 0; m < frames; m++)
                      if(frameCounter[m] == -1)
                      {
                            frameCounter[m] = inputSet[n];
                            b = 1;
                            break;
                      }
         
          if(b == 0)
          {
                for(int m = 0; m < frames; m++)
                      temp[m] = 0;
          
                for(int k = n - 1, l = 1; l <= frames - 1; l++, k--)
                      for(int m = 0; m < frames; m++)
                            if(frameCounter[m] == inputSet[k])
                                  temp[m] = 1;

                for(int m = 0; m < frames; m++)
                {
                      if(temp[m] == 0)
                      position = m;
                }
                
                frameCounter[position] = inputSet[n];
                
                faults++;
        }
            
        printf("\n");
        for(int m = 0; m < frames; m++)
        {
			if(frameCounter[m] == -1)
			 	    printf("\t-");
			else
			{
				printf("\t");
				putchar(frameCounter[m]);
			}
        }
     }
     printf("\nLRU Page Faults:\t%d\n", faults);

	
}

void FIFO(int inputSet[], int setSize, int frames)
{
	int frameCounter[frames];
	int faults = 0;
	int s = 0;
	
	//set the frameCountee array to nothing value in paging.
    for(int m = 0; m < frames; m++)
		frameCounter[m] = -1;
      
    for(int m = 0; m < setSize; m++)
    {
		s = 0;
		
        for(int n = 0; n < frames; n++)
			if(inputSet[m] == frameCounter[n])
            {
				s++;
                faults--;
            }   
                  
        faults++;
            
        if((faults <= frames) && (s == 0))
			frameCounter[m] = inputSet[m];
        else if(s == 0)
			frameCounter[(faults - 1) % frames] = inputSet[m];
            
        printf("\n");
            
        for(int n = 0; n < frames; n++)
        {     
			if(frameCounter[n] != -1)
			{
				printf("\t");
				putchar(frameCounter[n]);
				
			}
			else
				printf("\t-");
		}
	} 
      printf("\nPage Faults for FIFO algorithm:\t%d\n", faults);
	
}

void Optimal(int inputSet[], int setSize, int frames)
{
	int frameCounter[frames], temp[frames], pos, max, faults = 0;
	int a, b, c;	//flags
	
    for(int i = 0; i < frames; ++i)
        frameCounter[i] = -1;
    
    
    for(int i = 0; i < setSize; ++i)
    {
        a = 0;
        b = 0;
        
        for(int j = 0; j < frames; ++j)
            if(frameCounter[j] == inputSet[i])
            {
                   a = 1;
                   b = 1;
                   break;
            }
        
        if(a == 0)
            for(int j = 0; j < frames; ++j)
                if(frameCounter[j] == -1)
                {
                    faults++;
                    frameCounter[j] = inputSet[i];
                    b = 1;
                    break;
                }
        
        if(b == 0)
        {
            c =0;
            
            for(int j = 0; j < frames; ++j){
                temp[j] = -1;
                
                for(int k = i + 1; k < setSize; ++k)
                    if(frameCounter[j] == inputSet[k]){
                        temp[j] = k;
                        break;
                    }
            }
            
            for(int j = 0; j < frames; ++j){
                if(temp[j] == -1){
                    pos = j;
                    c = 1;
                    break;
                }
            }
            
            if(c ==0){
                max = temp[0];
                pos = 0;
                
                for(int j = 1; j < frames; ++j)
                    if(temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }            
            }
            
            frameCounter[pos] = inputSet[i];
            faults++;
        }
        
        printf("\n");
        
        for(int m = 0; m < frames; m++)
            {
				  if(frameCounter[m] == -1)
					    printf("\t-");
				  else
				  {
					  printf("\t");
					  putchar(frameCounter[m]);
				  }
            }
        
    }
    
    printf("\n\nOptimal Algorithm page faults: %d", faults);
	
	
	
	
}



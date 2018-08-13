//Patrick Beach
//Operating Systems - Assignment 3
//multiple thread test
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int startingShirts = 1000;
int givenShirts = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


//Structure that saves data from the individual threads
struct threadResources
{
	int threadNum;
	int threadShirtsTaken;
};


// Thread function to generate sum of 0 to N
void* shirtInventory(void* arg);

int main()
{
	//number of threads
	int threadCount = 3;
	char ch = 'A';

	//declare structure for managing thread resources
	struct threadResources tr[threadCount];

	// Thread ID:
	pthread_t tids[threadCount];

	// Create attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	
	//for loop that creates the threads
	for(int i = 0; i < threadCount; i++)
	{
		tr[i].threadNum = i;			//thread number
		tr[i].threadShirtsTaken = 0;	//thread starts off with 0 shirts taken
		pthread_attr_t attr;			//thread attributes managed by pthread library
		pthread_attr_init(&attr);		
		pthread_create(&tids[i], &attr, shirtInventory, &tr[i]); //create thread
	}
	// Do other stuff here...

	//this waits for all the threads to finish
	for(int i = 0; i < threadCount; i++)
	{
		pthread_join(tids[i], NULL);	//once all threads are finished, end them 
		putchar(ch + i);
	}
	
	printf("The total number of T-shirts given out is: %d\n", givenShirts);
	
}

void* shirtInventory(void* arg)
{
	struct threadResources *tr = (struct threadResources*) arg;
	int shirtsJustTaken;	//temporary variable for printing shirts taken

	//loop that continues thread as long as there are still shirts in the inventory
	while(startingShirts > 0)
	{
//		pthread_mutex_lock(&mutex);	//lock shirt count
		
		if(startingShirts % (tr->threadNum + 3) != 0)
			shirtsJustTaken = (startingShirts / (tr->threadNum + 3) + 1);
		else
			shirtsJustTaken = (startingShirts / (tr->threadNum + 3));
			
		tr->threadShirtsTaken += shirtsJustTaken;
		int ch = 'A' + tr->threadNum;
		printf("Thread ");
		putchar(ch);
		printf(" has taken %d\n", shirtsJustTaken);
		startingShirts -= shirtsJustTaken;
			
		givenShirts += shirtsJustTaken;
		
//		pthread_mutex_unlock(&mutex);	//unlock shirt count
		
		//I'm calling wait so the other processes get to go a few times
		//Instead of A going multiple times in a row
		//usleep(10);	
				
	}

	pthread_exit(0);
}

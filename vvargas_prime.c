// UT El Paso EE 4374 Assignment 3
// Multi-threaded Prime Number Search
// Author: ???
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include "vvargas_prime.h"
#include <math.h> //for square root function

/* Global variables that are shared */
sPRIME_THREAD primeThreadData[MAX_THREADS];
int	numThreads;

/*Declare file names variable*/
FILE *primesFile; //file to write the primes to
char *fileName[2];

void *prime_search(void *param)
{
	
	/*We will receive an sPRIME_THREAD structure as argument, from there we will get our values*/
	sprintf(fileName[(((sPRIME_THREAD *)param)->num)-1], "primes%d", ((sPRIME_THREAD *)param)->num);	
	#if 0
	/* Create primes output file */
  	primesFile = fopen(fileName[(((sPRIME_THREAD *)param)->num)-1],"w");
	for(int i=((sPRIME_THREAD *)param)->low;i<=((sPRIME_THREAD *)param)->high;i++){
		((sPRIME_THREAD *)param)->current = i; //we set current number being checked
		//for each iteration we check if value is prime
		if(test_prime(i)){
			fprintf(primesFile,"%d\n",i); //write to file
		}
	}
	fclose(primesFile);//close the file
	#endif
}

void *mini_shell(void *param)
{
	int inputSize, i;
	int threadNum;
	char buff[128];		// Character buffer
	while(1)
	{
		// Request a line of input
		write(1, " -> ", 4);
		// Read the line
		inputSize = read(0, buff, 128);
		// Strip off carriage return
		buff[inputSize-1] = '\0';
		if((buff[0] >= '1') && (buff[0] <= '9'))
		{
			// An integer was entered
			threadNum = buff[0] - '0';
			if(threadNum <= numThreads)
			{
				printf("Thread %d progress: %d\n", threadNum, primeThreadData[threadNum-1].current);
			}
			else
			{
				printf("Thread %d does not exist\n", threadNum);
			}
			
		}
		else
		{		
			if(buff[0] == 'a')
			{
				// Print status for all threads
				for(i = 0; i < numThreads; i++)
				{
					printf("Thread %d progress: %d\n", i+1, primeThreadData[i].current);
				}
			}
			else
			{
				printf("Unrecognized input\n");
			}
		}

		printf("\n");
		fflush(NULL);

	}

	pthread_exit(0);

}
/*For this we will do a simple primality test, divide by all numbers from 2 to Sqrt of the given number
if any give an integer result, we declare it as non prime.*/
int test_prime(int n)
{
	//first get squared root
	double rootDoub = sqrt((double) n);
	int rootInt = rootDoub;
	//now perform check
	for(int i = 2; i<= rootInt ; i++){
		if(n%rootInt == 0)
			return 0;
	}
    return 1;
}

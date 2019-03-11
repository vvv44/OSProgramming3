// UT El Paso EE 4374 Assignment 3
// Multi-threaded Prime Number Search
// Author: ???
//
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include "vvargas_prime.h"

#define BUFFER_SIZE	1000000
//s
unsigned char buffer[BUFFER_SIZE+1];
unsigned char fileName[100];
FILE *primeFile;
FILE *primeThreadFile;


int main(int argc, char *argv[])
{
  int i, bytesRead, bytesWritten;
  pthread_t tid[MAX_THREADS];
  pthread_t tidshell;
  pthread_attr_t attr;
  time_t before, after;

  /* Record time at start */
  before = time(NULL);

  /* Setup threads to find prime numbers */
  pthread_attr_init(&attr);
  numThreads = 2;

  /*We need to fill the info for the array of structs*/
  /*First we will get it from the two arguments, argv[1] is the low and argv[2] is the high*/
  /*Right away we can set the low of first thread and high of second and their thread numbers*/
  primeThreadData[0].low = atoi(argv[1]);
  primeThreadData[1].high = atoi(argv[2]);
  primeThreadData[0].num = 1;
  primeThreadData[1].num = 2;

  /*Now we need to compute the missing high and low, to achieve a good balance*/
  //FIXME: We will leave it at 50/50 for now
  int range = primeThreadData[1].high-primeThreadData[0].low;
  primeThreadData[0].high = range/2;
  primeThreadData[1].low = range/2+1;

  /*Create threads that will do the prime search*/
  pthread_create(&tid[0],&attr,prime_search,&primeThreadData[0]);//thread 1
  pthread_create(&tid[1],&attr,prime_search,&primeThreadData[1]);//thread 2

  /* Setup a mini shell thread to provide interactivity with the user */
  pthread_create(&tidshell,&attr,mini_shell,NULL);

  /* Create primes output file */
  primeFile = fopen("primest","w");
  fclose(primeFile);
  int res = 0;//respnse from  pthread join
  /* Wait for the prime search threads to complete and combine their data */
  for(i = 0; i < numThreads; i++)
  {
    printf("before join");
  	/* Wait for the next thread to complete */
  	res = pthread_join(tid[i],NULL);
    if (res!=0){//error
      printf("Errorsillo");
      break;
    }
  	/* On thread completion, write its data to "primest" */
    printf("join succesful");
    fileName[0] = '\0';
    sprintf(fileName, "primes%d", i+1);					// Open the thread's data file
    if((primeThreadFile = fopen(fileName,"r")) == NULL)
    {
    	printf("Failed to open file: %s\n", fileName);
    }
    else
    {
    	if((primeFile = fopen("primest","a")) == NULL)	// Open "primest"
    	{
    		printf("Failed to open file: primest\n");
    	}
    	else
    	{
    		while(feof(primeThreadFile) == 0)
			  {
				/* Read from the thread's data file */
				bytesRead = fread(buffer,1,BUFFER_SIZE,primeThreadFile);
				/* Write to the combined file */
				bytesWritten = fwrite(buffer,1,bytesRead,primeFile);
    		}
			fclose(primeFile);
    	}
		fclose(primeThreadFile);
	  }
  }
  
  /* Record execution time */
  after = time(NULL);
  printf("\nPrime search done after %ld seconds\n", after-before);

  sleep(10);
  
  /* Lastly, kill the interaction thread */
  pthread_kill(tidshell, SIGKILL);

  return 0;

}


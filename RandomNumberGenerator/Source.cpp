#ifndef _RANDOM_NUMBER_EXAMPLE
#define _RANDOM_NUMBER_EXAMPLE

/*
This is an example of how to make random numbers correctly

Since a processor has very specific ids for threads and processes
on multi-cored hyperthreaded processors don't generate random numbers
with using the processor clock as the seed very well. So instead
a word address is a much better option the following example shows
how to do this
*/
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/*
This example uses the processor clock time as the seed

THIS IS THE WRONG WAY TO DO IT MOST OF THE TIME

since most architectures are designed to be very effiecient often
processes are finished as long streams and only switch threads when
absolutely necessary

This is very fast but the numbers generated are very uniform
*/
int randomNumberExampleSystem(void)
{
	//time(NULL) returns the value of the current
	//process id
	srand(time(NULL));
	return rand()%100;
}

/*
This function generates a random number using
only a memory address. This is a very useful
technique because memory allocation is 
system state dependant.

This is still very fast, however only half as 
fast as processor seeding. However the numbers
generated are much more satisfying
*/
int randomNumberExampleMemory(void)
{
	int *seed = new int[1];
	srand((int)&seed[0]);
	return rand()%100;
}

/*
This combines both techniques so if one method
doesn't work the other one will save the system
*/
int randomNumberExampleCombination(void)
{
	int *seed = new int[1];
	srand(time(NULL)*(int)&seed[0]);
	return rand()%100;
}

void main(void)
{
	FILE * log;
	time_t current_time = time(0);
	log = fopen("log.txt", "w");
	int count = 0;
	while(time(0) < current_time + 2)
		fprintf(log, "Current loop iteration: %d \nSystem timing: %d \nMemory: %d\nCombination: %d \n\n", count++, randomNumberExampleSystem(),
		randomNumberExampleMemory(), randomNumberExampleCombination());
	fclose(log);
}
#endif
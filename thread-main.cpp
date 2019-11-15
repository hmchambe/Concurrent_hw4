// ----------------------------------------------------------- 
// NAME : Hunter Chambers                    User ID: 81276171 
// DUE DATE : 11/15/2019                                       
// PROGRAM ASSIGNMENT 4                                        
// FILE NAME : thread-main.cpp            
// PROGRAM PURPOSE :                                           
//    This program has a Santa, many elves, and many reindeer
//	Santa is sleeping and can only be woken up by three elves
//	if they have questions, or if all of the reindeer are back
//	from the bahamas        
// ----------------------------------------------------------- 
#include "ThreadClass.h"
#include "thread.h"
int queueLength = 0;
int line[3];
int ind;
int globalReindeer;
int numberOfReindeer;
int killAll = 0;
int deerWakeSanta = 0;

// ----------------------------------------------------------- 
// FUNCTION  main         
//     start the threads for Santa, elves, and reindeer                            
// PARAMETER USAGE :                                           
//    argv[1]: number of elves
//    argv[2]: number of reindeer
//    argv[3]: number of toys               
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
int main(int argc, char *argv[])
{
	int numberOfElves = atoi(argv[1]), numberOfToys = atoi(argv[3]), i;
	numberOfReindeer = atoi(argv[2]);
	// Default values
	if(numberOfElves == 0)
	{
		numberOfElves = 7;
	}
	if(numberOfReindeer == 0)
	{
		numberOfReindeer = 9;
	}
	if(numberOfToys == 0)
	{
		numberOfToys = 5;
	}
	globalReindeer = numberOfReindeer;
	char buf[500];

	// Instantiate threads
	ElfThread *elfthread[numberOfElves];
	SantaThread *santathread = new SantaThread(numberOfElves, numberOfReindeer, numberOfToys);
	ReindeerThread *reindeerthread[numberOfReindeer];

	// Starts Santa thread
	santathread->Begin();
	for(i=0; i<numberOfReindeer; i++)
	{
		reindeerthread[i] = new ReindeerThread(i, numberOfReindeer);
		reindeerthread[i]->Begin();
	}

	for(i=0; i<numberOfElves; i++)
	{
		elfthread[i] = new ElfThread(i);
		elfthread[i]->Begin();
	}	

	// wait for santa to exit
	santathread->Join();
	Exit();
}

// ----------------------------------------------------------- 
// NAME : Hunter Chambers                    User ID: 81276171 
// DUE DATE : 11/15/2019                                       
// PROGRAM ASSIGNMENT 4                                        
// FILE NAME : thread.cpp            
// PROGRAM PURPOSE :                                           
//    This program has a Santa, many elves, and many reindeer
//	Santa is sleeping and can only be woken up by three elves
//	if they have questions, or if all of the reindeer are back
//	from the bahamas        
// ----------------------------------------------------------- 
#include "ThreadClass.h" 
#include "thread.h"

// ----------------------------------------------------------- 
// FUNCTION  SantaThread         
//     Constructor                            
// PARAMETER USAGE :                                           
//    elves: number of elves
//    reindeer: number of reindeer
//    toys: number of toys
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
SantaThread::SantaThread(int elves, int reindeer, int toys)
		: numberOfElves(elves), numberOfReindeer(reindeer), numberOfToys(toys)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Santa" << '\0';
}


// ----------------------------------------------------------- 
// FUNCTION  ElfThread         
//     Constructor                            
// PARAMETER USAGE :                                           
//    id: elf id
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
ElfThread::ElfThread(int id)
		: id(id)
{
	char buf[200];
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Elf" <<  id << '\0';
	sprintf(buf, "         Elf %d starts.\n", id);
	write(1, buf, strlen(buf));	
}

// ----------------------------------------------------------- 
// FUNCTION  ReindeerThread         
//     Constructor                            
// PARAMETER USAGE :                                           
//    id: reindeer id
//    numberOfReindeer: number of reindeer
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
ReindeerThread::ReindeerThread(int id, int numberOfReindeer)
		: id(id), numberOfReindeer(numberOfReindeer)
{
	char buf[200];
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Deer" << id << '\0';
	sprintf(buf, "    Reindeer %d starts\n", id);
	write(1, buf, strlen(buf));



}

// ----------------------------------------------------------- 
// FUNCTION  ThreadFunc        
//     Elfs main function                            
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    AskQuestion: elf asks a question
//    Delay: waits for a random amount of time       
// ----------------------------------------------------------- 
void ElfThread::ThreadFunc()
{
	while(1)
	{
		Delay();
		AskQuestion(id);
		Delay();
		// If santa is done, get laid off
		if(killAll)
		{
			Exit();
		}
	}
}

// ----------------------------------------------------------- 
// FUNCTION  ThreadFunc       
//     Santas main function                            
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    GatherReindeer: get reindeer from waiting
//    PutSleigh: hook up reindeer
//    ReleaseElves: let elves go after answering questions
//    Delay: waits for a random amount of time   
// ----------------------------------------------------------- 
void SantaThread::ThreadFunc()
{
	int i, j, tripsTaken = 0;
	char buf[200];
	sprintf(buf, "Santa thread starts\n");
	write(1, buf, strlen(buf));

	// Loops until time to retire
	while(numberOfToys)
	{
		Sleep();
		reindeerMutex.Lock();
		elfMutex.Lock();
		// If the reindeer are all back
		if(!globalReindeer)
		{
			// Reset reindeer count b/c it is no longer needed for this trip
			globalReindeer = numberOfReindeer;
			reindeerMutex.Unlock();
			// Last trip
			if(numberOfToys == 1)
			{
				killAll = 1;
			}
			elfMutex.Unlock();
			// gather all reindeer
			GatherReindeer();
			// put on sleigh
			PutSleigh();
			// fly off
			sprintf(buf, "The team flies off (%d)!\n", tripsTaken+1);
			write(1, buf, strlen(buf));
			Delay();
			//release all reindeer for vacation	
			for(i=0; i<numberOfReindeer; i++)
			{
				ReleaseReindeer.Signal();
			}
			// Account for trip taken
			numberOfToys--;
			tripsTaken++;
		}else if(queueLength == 3 && !killAll)
		{
			reindeerMutex.Unlock();
			elfMutex.Unlock();
			AnswerQuestions();
			sprintf(buf, "Santa answers the question posted by elves %d, %d, %d\n", line[0], line[1], line[2]);
			write(1, buf, strlen(buf));
			Delay();
			ReleaseElves();
		}
	}
	sprintf(buf, "After (%d) deliveries, Santa retires and is on vacation!\n", tripsTaken);
	write(1, buf, strlen(buf));
	Exit();

}

// ----------------------------------------------------------- 
// FUNCTION  ThreadFunc         
//     Reindeers main function                        
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    Delay: wait for some random amount of time
//    ReindeerBack: get back from Bahamas
//    WaitOthers: wait for other reindeer to be ready
//    WaitSleigh: get sleighed up
//    FlyOff: fly off with santa
// ----------------------------------------------------------- 
void ReindeerThread::ThreadFunc()
{
	while(1)
	{
		// If Santa is done, get laid off
		if(killAll)
		{
			Exit();
		}
		Delay();	// tan on the beaches
		ReindeerBack(id);	// report back to Santa
		WaitOthers();	// wait for others
				// Don't forget: the last wakes up Santa 
		WaitSleigh();	// wait for attaching sleigh
		FlyOff();	// fly off to deliver toys
				// Santa will let go all reindeer
		Delay();	// prepare for vacation
	}
}

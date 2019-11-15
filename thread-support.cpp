// ----------------------------------------------------------- 
// NAME : Hunter Chambers                    User ID: 81276171 
// DUE DATE : 11/15/2019                                       
// PROGRAM ASSIGNMENT 4                                        
// FILE NAME : thread-support.cpp            
// PROGRAM PURPOSE :                                           
//    This program has a Santa, many elves, and many reindeer
//	Santa is sleeping and can only be woken up by three elves
//	if they have questions, or if all of the reindeer are back
//	from the bahamas        
// ----------------------------------------------------------- 
#include "thread-support.h"

Semaphore SantaSleeping("SantaSleeping", 0);
Semaphore Queue("WaitingQueue", 3);
Semaphore AnsweringQuestion("AnsweringQuestion", 0);
Semaphore Release("Release", 0);
Semaphore SleighWaiting("WaitingOnSleigh", 0);
Semaphore ReleaseReindeer("ReleaseReindeer", 0);
Semaphore WaitForOthers("WaitOthers", 0);
Semaphore QueueLengthBlock("BlockQueueLength", 0);
Mutex elfMutex("elfMutex");
Mutex reindeerMutex("reindeerMutex");
	

// ----------------------------------------------------------- 
// FUNCTION  AskQuestion         
//     Elves ask santa a question and if there are 3 of them
// 	they can wake him up                      
// PARAMETER USAGE :                                           
//    id: elf id
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void AskQuestion(int id)
{
	char buf[200];
	int placeInLine;
	elfMutex.Lock();
	if(!killAll)
	{
		sprintf(buf, "         Elf %d has a problem\n", id);
		write(1, buf, strlen(buf));
	}
	elfMutex.Unlock();
	Queue.Wait();	
	line[ind] = id;
	ind++;
	elfMutex.Lock();
	queueLength++;
	if(queueLength == 3 && !killAll)
	{
		sprintf(buf, "         Elves %d, %d, %d wake up the Santa\n",line[0], line[1], line[2]);
	        write(1, buf, strlen(buf));	
		SantaSleeping.Signal();
	}
	elfMutex.Unlock();
	AnsweringQuestion.Wait();
	Release.Wait();
	elfMutex.Lock();
	// Only one elf prnits this and then resets queuelength
	if(line[2] == id && !killAll)
	{
		sprintf(buf, "         Elves %d, %d, %d return to work\n", line[0], line[1], line[2]);
		write(1, buf, strlen(buf));
		queueLength = 0;
		ind = 0;
		QueueLengthBlock.Signal();
		QueueLengthBlock.Signal();
		QueueLengthBlock.Signal();
	}	
	elfMutex.Unlock();
	// Make all elves wait until queueLength is reset and then signal 3 more to enter
	QueueLengthBlock.Wait();
	Queue.Signal();
}

// ----------------------------------------------------------- 
// FUNCTION  Sleep        
//     Santa sleeps                            
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void Sleep()
{
	SantaSleeping.Wait();
}

// ----------------------------------------------------------- 
// FUNCTION  AnswerQuestions        
//     Answer elves questions                   
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void AnswerQuestions()
{
	AnsweringQuestion.Signal();
	AnsweringQuestion.Signal();
	AnsweringQuestion.Signal();
}

// ----------------------------------------------------------- 
// FUNCTION  Release Elves        
//     Let elves go after answering their questions                     
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void ReleaseElves()
{
	Release.Signal();
	Release.Signal();
	Release.Signal();
}

// ----------------------------------------------------------- 
// FUNCTION  Gather Reindeer        
//     Prepare the sleighs                   
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void GatherReindeer()
{
	int i;
	char buf[200];
	sprintf(buf, "Santa is preparing sleighs\n");
	write(1, buf, strlen(buf));
	for(i=0; i<numberOfReindeer; i++)
	{
		WaitForOthers.Signal();
	}
}

// ----------------------------------------------------------- 
// FUNCTION  PutSleigh        
//     Allow reindeer through                         
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void PutSleigh()
{
	int i;
	for(i=0; i<numberOfReindeer; i++)
	{
		SleighWaiting.Signal();
	}
}

// ----------------------------------------------------------- 
// FUNCTION  ReindeerBack        
//     Reindeer back from Bahamas and wakes Santa if 
//	it's the last one                         
// PARAMETER USAGE :                                           
//    id: reindeer id
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void ReindeerBack(int id)
{
	char buf[200];
	reindeerMutex.Lock();
	globalReindeer--;
	sprintf(buf, "    Reindeer %d returns\n", id);
	write(1, buf, strlen(buf));
	if(globalReindeer == 0)
	{
		SantaSleeping.Signal();
		sprintf(buf, "    The last reindeer %d wakes up Santa\n", id);
		write(1, buf, strlen(buf));
	}
	reindeerMutex.Unlock();	
}

// ----------------------------------------------------------- 
// FUNCTION  WaitOthers        
//     Wait for other reindeer                         
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void WaitOthers()
{
	WaitForOthers.Wait();
}

// ----------------------------------------------------------- 
// FUNCTION  WaitSleigh        
//     Wait for sleigh                         
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void WaitSleigh()
{
	SleighWaiting.Wait();
}

// ----------------------------------------------------------- 
// FUNCTION  FlyOff        
//     Reindeer flyOff                        
// PARAMETER USAGE :                                           
//    [NONE]
// FUNCTION CALLED :                                           
//    [NONE]        
// ----------------------------------------------------------- 
void FlyOff()
{
	// The reindeer fly off
	ReleaseReindeer.Wait();
}

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


void Sleep()
{
	SantaSleeping.Wait();
}

void AnswerQuestions()
{
	AnsweringQuestion.Signal();
	AnsweringQuestion.Signal();
	AnsweringQuestion.Signal();
}

void ReleaseElves()
{
	Release.Signal();
	Release.Signal();
	Release.Signal();
}

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

void PutSleigh()
{
	int i;
	for(i=0; i<numberOfReindeer; i++)
	{
		SleighWaiting.Signal();
	}
}


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

void WaitOthers()
{
	WaitForOthers.Wait();
}

void WaitSleigh()
{
	SleighWaiting.Wait();
}

void FlyOff()
{
	// The reindeer fly off
	ReleaseReindeer.Wait();
}

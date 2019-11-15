#include "thread-support.h"

void AskQuestion(int id)
{
	char buf[200];
	int placeInLine;

	sprintf(buf, "         Elf %d has a problem\n", id);
	write(1, buf, strlen(buf));

	Queue.Wait();	
	line[ind] = id;
	ind++;
	elfMutex.Lock();
	queueLength++;
	if(queueLength == 3)
	{
		SantaSleeping.Signal();
	}
	elfMutex.Unlock();
	AnsweringQuestion.Wait();
	Release.Wait();
	elfMutex.Lock();
	// Only one elf prnits this and then resets queuelength
	if(line[2] == id)
	{
		sprintf(buf, "         Elves %d, %d, %d return to work\n", line[0], line[1], line[2]);
		write(1, buf, strlen(buf));
		queueLength = 0;
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
	sprintf(buf, "Santa is preparing sleighs\nGlobal Reindeer Reset\n");
	write(1, buf, strlen(buf));
	globalReindeer = numberOfReindeer;
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
	reindeerMutex.Unlock();
	sprintf(buf, "    Reindeer %d returns\n", id);
	write(1, buf, strlen(buf));
	if(globalReindeer == 0)
	{
		sprintf(buf, "    The last reindeer %d wakes up Santa\n", id);
		write(1, buf, strlen(buf));
		SantaSleeping.Signal();
	}
	
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
}

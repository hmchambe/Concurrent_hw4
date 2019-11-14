#include "thread-support.h"

void AskQuestion(int id)
{
	char buf[200];
	int placeInLine;

	sprintf(buf, "         Elf %d has a problem\n", id);
	write(1, buf, strlen(buf));
	
	elfMutex.Lock();
	queueLength++;
	if(queueLength == 3)
	{
		SantaSleeping.Signal();
		sprintf(buf, "         Elf %d wakes up the Santa\n", id);
		write(1, buf, strlen(buf));
	}
	elfMutex.Unlock();
	AnsweringQuestion.Wait();
	sprintf(buf, "         Elf %d question answered\n", id);
	write(1, buf, strlen(buf));
	Queue.Wait();

	elfMutex.Lock();
	queueLength--;
	elfMutex.Unlock();
}

void WaitOthers()
{

}

void WaitSleigh()
{

}

void FlyOff()
{



}

void Sleep()
{
	SantaSleeping.Wait();
}

// TODO add id
void ReindeerBack()
{



}

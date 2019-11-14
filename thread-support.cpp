#include "thread-support.h"

void AskQuestion(int id)
{
	char buf[200];
	int placeInLine;

	sprintf(buf, "         Elf %d has a problem\n", id);
	write(1, buf, strlen(buf));

	Queue.Wait();	
	//elfMutex.Lock();
	queueLength++;
	//queue[index] = id;
	//index++;
	if(queueLength == 3)
	{
		SantaSleeping.Signal();
		//sprintf(buf, "         Elf %d, %d, %d wake up the Santa\n", queue[0], queue[1], queue[2]);
		//write(1, buf, strlen(buf));
	}
	//elfMutex.Unlock();
	printf("BEFORE WAIT\n");
	Answering.Wait();
	printf("AFTER WAIT\n");
	sprintf(buf, "         Elf %d question answered\n", id);
	write(1, buf, strlen(buf));
	Release.Wait();
	elfMutex.Lock();
	queueLength--;
	elfMutex.Unlock();
	Queue.Signal();
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

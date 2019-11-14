#include "ThreadClass.h" 
#include "thread.h"
#include "thread-support.h" 

SantaThread::SantaThread(int elves, int reindeer, int toys)
		: numberOfElves(elves), numberOfReindeer(reindeer), numberOfToys(toys)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Santa" << '\0';
}



ElfThread::ElfThread(int id)
		: id(id)
{
	char buf[200];
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Elf" <<  id << '\0';
	sprintf(buf, "         Elf %d starts.\n", id);
	write(1, buf, strlen(buf));	
}

ReindeerThread::ReindeerThread(int id, int numberOfReindeer)
		: id(id), numberOfReindeer(numberOfReindeer)
{




}

void ElfThread::ThreadFunc()
{
	char buf[200];

	while(1)
	{
		Delay();
		AskQuestion(id);
		Delay();
	}
}


void SantaThread::ThreadFunc()
{
	int i, j;
	char buf[200];
	sprintf(buf, "Santa thread starts\n");
	write(1, buf, strlen(buf));

	while(1)
	{
		Sleep();
		if(queueLength >= 3)
		{
			printf("SANTA\n");
			Answering.Signal();
			Answering.Signal();
			Answering.Signal();
			Delay();
			Release.Signal();
			Release.Signal();
			Release.Signal();
			printf("SANTA END\n");
		}	
	}

}

void ReindeerThread::ThreadFunc()
{
	while(1)
	{
		Delay();	// tan on the beaches
		ReindeerBack();	// report back to Santa
		WaitOthers();	// wait for others
				// Don't forget: the last wakes up Santa 
		WaitSleigh();	// wait for attaching sleigh
		FlyOff();	// fly off to deliver toys
				// Santa will let go all reindeer
		Delay();	// prepare for vacation
	}



}

#include "ThreadClass.h" 
#include "thread.h"

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
	char buf[200];
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Deer" << id << '\0';
	sprintf(buf, "    Reindeer %d starts\n", id);
	write(1, buf, strlen(buf));



}

void ElfThread::ThreadFunc()
{
	char buf[200];

	while(1)
	{
		Delay();
		AskQuestion(id);
		Delay();
		if(killAll)
		{
			Exit();
		}
	}
}


void SantaThread::ThreadFunc()
{
	int i, j, tripsTaken = 0;
	char buf[200];
	sprintf(buf, "Santa thread starts\n");
	write(1, buf, strlen(buf));

	while(numberOfToys)
	{
		int i;
		Sleep();
		if(!globalReindeer)
		{
			// Last trip
			if(numberOfToys == 1)
			{
				killAll = 1;
			}
			// gather all reindeer
			GatherReindeer();
			// put on sleigh
			PutSleigh();
			// fly off
			sprintf(buf, "The team flies off (%d)!\n", tripsTaken+1);
			write(1, buf, strlen(buf));
			Delay();
			//release all reindeer for vacation	
			numberOfToys--;
			tripsTaken++;
		}else if(queueLength == 3)
		{
			sprintf(buf, "         Elf %d, %d, %d wake up Santa\n", line[0], line[1], line[2]);
			write(1, buf, strlen(buf));
			AnswerQuestions();
			Delay();
			ReleaseElves();
		}
	}
	sprintf(buf, "After (%d) deliveries, Santa retires and is on vacation!\n", tripsTaken);
	write(1, buf, strlen(buf));
	Exit();

}

void ReindeerThread::ThreadFunc()
{
	while(1)
	{
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

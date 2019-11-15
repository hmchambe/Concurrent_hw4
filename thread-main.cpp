#include "ThreadClass.h"
#include "thread.h"
int queueLength = 0;
int line[3];
int ind;
int globalReindeer;
int numberOfReindeer;
int killAll = 0;
int deerWakeSanta = 0;

int main(int argc, char *argv[])
{
	int numberOfElves = atoi(argv[1]), numberOfToys = atoi(argv[3]), i;
	numberOfReindeer = atoi(argv[2]);
	globalReindeer = numberOfReindeer;
	char buf[500];
	ElfThread *elfthread[numberOfElves];
	SantaThread *santathread = new SantaThread(numberOfElves, numberOfReindeer, numberOfToys);
	ReindeerThread *reindeerthread[numberOfReindeer];

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


	santathread->Begin();

	for(i=0; i<numberOfReindeer; i++)
	{
		//reindeerthread[i]->Join();
	}
	for(i=0; i<numberOfElves; i++)
	{
		//elfthread[i]->Join();
	}
	// wait for santa to exit
	santathread->Join();

	Exit();
}

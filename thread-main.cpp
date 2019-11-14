#include "ThreadClass.h"
#include "thread.h"

int main(int argc, char *argv[])
{
	int numberOfElves = atoi(argv[1]), numberOfReindeer = atoi(argv[2]), numberOfToys = atoi(argv[3]), i;

	ElfThread *elfthread[numberOfElves];
	SantaThread *santathread = new SantaThread(numberOfElves, numberOfReindeer, numberOfToys);

	for(i=0; i<numberOfElves; i++)
	{
		elfthread[i] = new ElfThread(i);
		elfthread[i]->Begin();
	}	


	santathread->Begin();

	// wait for santa to exit
	santathread->Join();

}

#include "thread-support.h"

void AskQuestion(int id)
{
	elfMutex->Lock();
//	elvesWaiting++;
	elfMutex->Unlock();
	
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

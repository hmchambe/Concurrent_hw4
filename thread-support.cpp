#include "thread-support.h"
#include "ThreadClass.h"

void AskQuestion()
{
	elfMutex.Lock;
	elvesWaiting++;
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
	santaSleeping.Wait();
}

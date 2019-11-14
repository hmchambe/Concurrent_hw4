#ifndef THREAD_SUPPORT
#define THREAD_SUPPORT
#include "ThreadClass.h"

//int elvesWaiting = 0;
//int reindeerCount;

static Semaphore SantaSleeping("SantaSleeping", 1);
static Semaphore Queue("WaitingQueue", 3);

static Mutex *elfMutex;
static Mutex *reindeerMutex;

void ReindeerBack();
void WaitOthers();
void WaitSleigh();
void FlyOff();
void Sleep();
void AskQuestion(int id);


#endif

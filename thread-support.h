#ifndef THREAD_SUPPORT
#define THREAD_SUPPORT
#include "ThreadClass.h"
#include <stdio.h>
#include <string.h>
extern int queueLength;
//int reindeerCount;

static Semaphore SantaSleeping("SantaSleeping", 0);
static Semaphore Queue("WaitingQueue", 0);
static Semaphore AnsweringQuestion("AnsweringQuestion", 0);
static Semaphore QueueID("StoreID", 3);
static Mutex elfMutex("reindeerMutex");
static Mutex reindeerMutex("reindeerMutex");

void ReindeerBack();
void WaitOthers();
void WaitSleigh();
void FlyOff();
void Sleep();
void AskQuestion(int id);


#endif

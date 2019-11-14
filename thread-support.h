#ifndef THREAD_SUPPORT
#define THREAD_SUPPORT
#include "ThreadClass.h"
#include <stdio.h>
#include <string.h>
extern int queueLength;
extern int queue[3];
//int reindeerCount;

static Semaphore SantaSleeping("SantaSleeping", 0);
static Semaphore Queue("WaitingQueue", 3);
static Semaphore Answering("AnsweringQuestion", 0);
static Semaphore Release("Release", 0);
static Mutex elfMutex("reindeerMutex");
static Mutex reindeerMutex("reindeerMutex");

void ReindeerBack();
void WaitOthers();
void WaitSleigh();
void FlyOff();
void Sleep();
void AskQuestion(int id);


#endif

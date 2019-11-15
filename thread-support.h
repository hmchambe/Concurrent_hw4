//#ifndef THREAD_SUPPORT
//#define THREAD_SUPPORT
#include "ThreadClass.h"
#include <stdio.h>
#include <string.h>
extern int queueLength;
extern int numberOfReindeer;
extern int line[3];
extern int ind;
extern int globalReindeer;
extern int killAll;

static Semaphore SantaSleeping("SantaSleeping", 0);
static Semaphore Queue("WaitingQueue", 3);
static Semaphore AnsweringQuestion("AnsweringQuestion", 0);
static Semaphore Release("Release", 0);
static Semaphore SleighWaiting("WaitingOnSleigh", 0);
static Semaphore WaitForOthers("WaitOthers", 0);
static Semaphore QueueLengthBlock("BlockQueueLength", 0);
static Mutex elfMutex("reindeerMutex");
static Mutex reindeerMutex("reindeerMutex");


void ReindeerBack(int id);
void WaitOthers();
void WaitSleigh();
void FlyOff();
void Sleep();
void AskQuestion(int id);
void ReleaseElves();
void AnswerQuestions();
void GatherReindeer();
void PutSleigh();
//#endif

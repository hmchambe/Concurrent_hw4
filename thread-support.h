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

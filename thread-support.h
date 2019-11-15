// ----------------------------------------------------------- 
// NAME : Hunter Chambers                    User ID: 81276171 
// DUE DATE : 11/15/2019                                       
// PROGRAM ASSIGNMENT 4                                        
// FILE NAME : thread-support.h            
// PROGRAM PURPOSE :                                           
//    This program has a Santa, many elves, and many reindeer
//	Santa is sleeping and can only be woken up by three elves
//	if they have questions, or if all of the reindeer are back
//	from the bahamas        
// ----------------------------------------------------------- 
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


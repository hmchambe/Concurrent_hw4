// ----------------------------------------------------------- 
// NAME : Hunter Chambers                    User ID: 81276171 
// DUE DATE : 11/15/2019                                       
// PROGRAM ASSIGNMENT 4                                        
// FILE NAME : thread.h            
// PROGRAM PURPOSE :                                           
//    This program has a Santa, many elves, and many reindeer
//	Santa is sleeping and can only be woken up by three elves
//	if they have questions, or if all of the reindeer are back
//	from the bahamas        
// ----------------------------------------------------------- 
#ifndef THREAD_STUFF
#define THREAD_STUFF
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "thread-support.h"

extern Semaphore SantaSleeping;
extern Semaphore Queue;
extern Semaphore AnsweringQuestion;
extern Semaphore Release;
extern Semaphore SleighWaiting;
extern Semaphore WaitForOthers;
extern Semaphore QueueLengthBlock;
extern Semaphore ReleaseReindeer;
extern Mutex elfMutex;
extern Mutex reindeerMutex;


class ElfThread : public Thread
{
	public:
	// constructor
	ElfThread(int id);
	private:
	void ThreadFunc();
	int id;
};

class ReindeerThread : public Thread
{
	public:
	//constructor
	ReindeerThread(int id, int numberOfReindeer);
	private:
	void ThreadFunc();
	int id;
	int numberOfReindeer;
};

class SantaThread : public Thread
{
	public:
	//constructor
	SantaThread(int numberOfElves, int numberOfReindeer, int numberOfToys);
	private: 
	void ThreadFunc();
	int numberOfElves;
	int numberOfReindeer;
	int numberOfToys;
};
#endif

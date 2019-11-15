#ifndef THREAD_STUFF
#define THREAD_STUFF
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "thread-support.h"
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

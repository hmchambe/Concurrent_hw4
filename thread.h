#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

extern elfCount, reindeerCount

class ElfThread : public Thread
{
	public:
	// constructor
	ElfThread(int id);
	private:
	void ThreadFunc();
	int id;
}

class ReindeerThread : public Thread
{
	public:
	//constructor
	ReindeerThread(int id);
	private:
	void ThreadFunc();
	int id;
}

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
}


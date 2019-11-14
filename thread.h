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

}

class ReindeerThread : public Thread
{
	public:
	//constructor
	ReindeerThread();
	private:
	void ThreadFunc();

}

class SantaThread : public Thread
{
	public:
	//constructor
	SantaThread();
	private: 
	void ThreadFunc();
}


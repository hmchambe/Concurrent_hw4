#include "ThreadClass.h"

int main(int argc, char *argv[])
{
	SantaThread santathread = new SantaThread();
	santathread->Begin();







	// wait for santa to exit
	santathread->Join();



}

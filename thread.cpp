SantaThread::SantaThread(int elves, int reindeer, int toys)
		: numberOfElves(elves), numberOfReindeer(reindeer), numberOfToys(toys)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Santa" << '\0';
}



ElfThread::ElfThread(int id)// TODO add line below
		: id(id)
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Elf"
		<<  id << '\0';
	
}

ReindeerThread::ReindeerThread(int id, int numberOfReindeer)
		: id(id), numberOfReindeer(numberOfReindeer)
{




}

void ElfThread::ThreadFunc(int id)
{
	char buf[200];
	sprintf(buf, "         Elf %d starts.\n", id);
	write(1, buf, strlen(buf));

	while(1)
	{
		Delay();
		AskQuestion(id);
		Delay();
	}
}

void SantaThread::ThreadFunc()
{

	while(1)
	{
		Sleep();	
	}



}

void ReindeerThread::ThreadFunc()
{
	while(1)
	{
		Delay();	// tan on the beaches
		ReindeerBack();	// report back to Santa
		WaitOthers();	// wait for others
				// Don't forget: the last wakes up Santa 
		WaitSleigh();	// wait for attaching sleigh
		FlyOff();	// fly off to deliver toys
				// Santa will let go all reindeer
		Delay();	// prepare for vacation
	}



}

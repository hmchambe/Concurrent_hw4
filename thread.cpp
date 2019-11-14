ElfThread::ElfThread()// TODO add line below
{
	ThreadName.seekp(0, ios::beg);
	ThreadName << "Elf"
		<< 



}

void ElfThread::ThreadFunc()
{
	while(1)
	{
		Delay();
		AskQuestion();
		Delay();
	}
}

void SantaThread::ThreadFunc()
{
	while(!retire)
	{
		if(



	}
	



}



extern elfCount;
extern reindeerCount;

extern Semaphore santaSleeping;

extern Mutex elfMutex;
extern Mutex reindeerMutex;

void Reindeerback();
void WaitOthers();
void WaitSleigh();
void FlyOff();
void Sleep();
void AskQuestion();

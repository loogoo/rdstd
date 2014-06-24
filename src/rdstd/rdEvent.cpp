/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdEvent.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#include "rdEvent.h"


BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32

rdEvent::rdEvent() 
{ 
	e = NULL;
}

rdEvent::~rdEvent()
{
	close();
}

bool rdEvent::wait(unsigned msec) 
{ 
	int rc = WaitForSingleObject(e, msec);
	assert(rc == WAIT_OBJECT_0 || rc == WAIT_TIMEOUT);
	return rc == WAIT_OBJECT_0;
}


void rdEvent::signal() 
{
	SetEvent(e);
}


void rdEvent::reset() 
{
	ResetEvent(e);
}


bool rdEvent::open(char_t const* name, bool signaled, bool manual) 
{
	e = CreateEvent(NULL, manual, signaled, name);
	return e != NULL; 
}


void rdEvent::close() 
{
	CloseHandle(e);
	e = NULL;
}


void rdEvent::erase() 
{ 
	close();
}

#else

rdEvent::rdEvent(const char *name, unsigned initValue)
	:rdSemaphore(name, initValue)
{

}
rdEvent::~rdEvent()
{

}


bool rdEvent::wait(unsigned msec) 
{ 
	if (dbSemaphore::wait(msec)) { 
		sem_post(sem);
		return true;
	}
	return false;
}


void rdEvent::signal() 
{
	while (sem_trywait(sem) == 0);
	sem_post(sem);
}


void rdEvent::reset() 
{
	while (sem_trywait(sem) == 0);
}


bool rdEvent::open(char const* name, bool signaled, bool /*manual*/) 
{
	return dbSemaphore::open(name, (int)signaled);
}

#endif


END_RDSTD_NAMESPACE
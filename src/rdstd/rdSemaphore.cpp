/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdSemaphore.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
***************************************************************************/
#include "rdSemaphore.h"


BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32

rdSemaphore::rdSemaphore(const char *name, unsigned initValue)
{
	open(name, initValue);
}

rdSemaphore::~rdSemaphore()
{
	close();
}


bool rdSemaphore::wait(unsigned msec) 
{ 
	int rc = WaitForSingleObject(_sem, msec);
	assert(rc == WAIT_OBJECT_0 || rc == WAIT_TIMEOUT);
	return rc == WAIT_OBJECT_0;
}


void rdSemaphore::signal(unsigned inc) 
{
	if (inc != 0) { 
		ReleaseSemaphore(_sem, inc, NULL);
	}
}
void rdSemaphore::reset() 
{ 
	while (WaitForSingleObject(_sem, 0) == WAIT_OBJECT_0);
}    


bool rdSemaphore::open(char_t const* name, unsigned initValue) 
{
	_sem = CreateSemaphore(NULL, initValue, LONG_MAX, name);
	return _sem != NULL; 
}

void rdSemaphore::close() 
{
	if (NULL != _sem) {
		BOOL ret = CloseHandle(_sem);
		if (0 != ret) {
			_sem = NULL;
		}
	}
}

void rdSemaphore::erase() 
{ 
	close();
}

#else

rdSemaphore::rdSemaphore(const char *name, unsigned initValue)
{
	open(name, initValue);
}

rdSemaphore::~rdSemaphore()
{
	close();
}


bool rdSemaphore::wait(unsigned msec) 
{ 
#ifdef POSIX_1003_1d
	struct timespec abs_ts;
	struct timeval  cur_tv;
	clock_gettime(CLOCK_REALTIME, &cur_tv);
	abs_ts.tv_sec = cur_tv.tv_sec + (msec + cur_tv.tv_usec / 1000) / 1000000; 
	abs_ts.tv_nsec = (msec + cur_tv.tv_usec / 1000) % 1000000 * 1000;
	int rc = sem_timedwait(_sem, &abs_ts);
	if (rc < 0) { 
		assert(errno == ETIMEDOUT);
		return false;
	}
	return true;
#else 
#ifdef NDEBUG
	sem_wait(_sem);
#else
	int rc = sem_wait(_sem);
	assert(rc == 0);
#endif
	return true;
#endif  
}

void rdSemaphore::signal(unsigned inc) 
{
	while (inc-- > 0) { 
		sem_post(_sem);
	}
}
void rdSemaphore::reset() 
{ 
	while (sem_trywait(_sem) == 0);
}    

bool rdSemaphore::open(char const* name, unsigned initValue) 
{
	this->name = new char[strlen(name)+2];
	if (*name != '/') { 
		strcpy(this->name+1, name);
		*this->name = '/';
	} else { 
		strcpy(this->name, name);
	}
	_sem = sem_open(this->name, O_CREAT, 0777, initValue);
	return _sem != NULL; 
}

void rdSemaphore::close() 
{
	if (_sem != NULL) { 
		sem_close(_sem);
		_sem = NULL;
	}
}
void rdSemaphore::erase() 
{ 
	close();
	sem_unlink(name);
	delete[] name;
}

#endif


END_RDSTD_NAMESPACE
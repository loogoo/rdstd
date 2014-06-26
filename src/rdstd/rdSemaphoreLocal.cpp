/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdSemaphoreLocal.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月14日
* 修改记录: 
***************************************************************************/
#include "rdSemaphoreLocal.h"

BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32

bool rdSemaphoreLocal::wait(rdMutex& mutex, time_t timeoutMsec) 
{ 
	mutex.unlock();
	int rc = WaitForSingleObject(_sem, (DWORD)timeoutMsec);
	assert(rc == WAIT_OBJECT_0 || rc == WAIT_TIMEOUT);
	mutex.lock();
	return rc == WAIT_OBJECT_0;
}


void rdSemaphoreLocal::wait(rdMutex& mutex) 
{ 
	mutex.unlock();
	int rc = WaitForSingleObject(_sem, INFINITE);
	assert(rc == WAIT_OBJECT_0);
	mutex.lock();
}

bool rdSemaphoreLocal::wait(rdMutexEx& mutex, time_t timeoutMsec) 
{ 
	mutex.unlock();
	int rc = WaitForSingleObject(_sem, (DWORD)timeoutMsec);
	assert(rc == WAIT_OBJECT_0 || rc == WAIT_TIMEOUT);
	mutex.lock();
	return rc == WAIT_OBJECT_0;
}


void rdSemaphoreLocal::wait(rdMutexEx& mutex) 
{ 
	mutex.unlock();
	int rc = WaitForSingleObject(_sem, INFINITE);
	assert(rc == WAIT_OBJECT_0);
	mutex.lock();
}

bool rdSemaphoreLocal::open(unsigned initValue) 
{
	return rdSemaphore::open(NULL, initValue);
}

#else

void rdLocalSemaphore::wait(rdMutex& mutex)
{ 
	while (count == 0) { 
		pthread_cond_wait(&cond, &mutex._mutex);
	}
	count -= 1;
}


bool rdLocalSemaphore::wait(rdMutex& mutex, time_t timeout) 
{
	if (count == 0) { 
		struct timespec abs_ts; 
#ifdef PTHREAD_GET_EXPIRATION_NP
		struct timespec rel_ts; 
		rel_ts.tv_sec = timeout/1000; 
		rel_ts.tv_nsec = timeout%1000*1000000;
		pthread_get_expiration_np(&rel_ts, &abs_ts);
#else
		struct timeval cur_tv;
		gettimeofday(&cur_tv, NULL);
		abs_ts.tv_sec = cur_tv.tv_sec + timeout/1000; 
		abs_ts.tv_nsec = cur_tv.tv_usec*1000 + timeout%1000*1000000;
		if (abs_ts.tv_nsec > 1000000000) { 
			abs_ts.tv_nsec -= 1000000000;
			abs_ts.tv_sec += 1;
		}
#endif
		do { 
			int rc = pthread_cond_timedwait(&cond, &mutex._mutex, &abs_ts);
			if (rc != 0) { 
				return false;
			}
		} while (count == 0);
	}
	count -= 1;
	return true;
}

void rdLocalSemaphore::wait(rdMutexEx& mutex)
{ 
	while (count == 0) { 
		pthread_cond_wait(&cond, &mutex._mutex);
	}
	count -= 1;
}


bool rdLocalSemaphore::wait(rdMutexEx& mutex, time_t timeout) 
{
	if (count == 0) { 
		struct timespec abs_ts; 
#ifdef PTHREAD_GET_EXPIRATION_NP
		struct timespec rel_ts; 
		rel_ts.tv_sec = timeout/1000; 
		rel_ts.tv_nsec = timeout%1000*1000000;
		pthread_get_expiration_np(&rel_ts, &abs_ts);
#else
		struct timeval cur_tv;
		gettimeofday(&cur_tv, NULL);
		abs_ts.tv_sec = cur_tv.tv_sec + timeout/1000; 
		abs_ts.tv_nsec = cur_tv.tv_usec*1000 + timeout%1000*1000000;
		if (abs_ts.tv_nsec > 1000000000) { 
			abs_ts.tv_nsec -= 1000000000;
			abs_ts.tv_sec += 1;
		}
#endif
		do { 
			int rc = pthread_cond_timedwait(&cond, &mutex._mutex, &abs_ts);
			if (rc != 0) { 
				return false;
			}
		} while (count == 0);
	}
	count -= 1;
	return true;
}


void rdLocalSemaphore::signal(unsigned inc = 1) 
{
	count += inc;
	if (inc > 1) { 
		pthread_cond_broadcast(&cond);
	} else if (inc == 1) { 
		pthread_cond_signal(&cond);
	}
}


void rdLocalSemaphore::open(unsigned initValue = 0) 
{ 
	pthread_cond_init(&cond, NULL);
	count = initValue;
}


void rdLocalSemaphore::close() 
{
	pthread_cond_destroy(&cond);
}

#endif
END_RDSTD_NAMESPACE
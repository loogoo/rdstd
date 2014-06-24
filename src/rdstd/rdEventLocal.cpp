/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdEventLocal.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月14日
* 修改记录: 
***************************************************************************/
#include "rdEventLocal.h"


BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32

bool rdEventLocal::wait(rdMutex& mutex, time_t timeoutMsec) 
{ 
	mutex.unlock();
	int rc = WaitForSingleObject(e, (DWORD)timeoutMsec);
	assert(rc == WAIT_OBJECT_0 || rc == WAIT_TIMEOUT);
	mutex.lock();
	return rc == WAIT_OBJECT_0;
}


void rdEventLocal::wait(rdMutex& mutex) 
{ 
	mutex.unlock();
	int rc = WaitForSingleObject(e, INFINITE);
	assert(rc == WAIT_OBJECT_0);
	mutex.lock();
}


bool rdEventLocal::open(bool signaled) 
{
	return rdEvent::open(NULL, signaled);
}

#else

void rdEventLocal::wait(rdMutex& mutex) 
{ 
	while (!signaled) { 
		pthread_cond_wait(&cond, &mutex._mutex);
	}
}
bool rdEventLocal::wait(rdMutex& mutex, time_t timeout) {
	if (!signaled) { 
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
		} while (!signaled);

	}
	return true;
}


void rdEventLocal::signal() 
{
	signaled = true;
	pthread_cond_broadcast(&cond);
}


void rdEventLocal::reset() {
	signaled = false;
}


void rdEventLocal::open(bool initValue) 
{ 
	signaled = initValue;
	pthread_cond_init(&cond, NULL);
}


void rdEventLocal::close() 
{
	pthread_cond_destroy(&cond);
}

#endif


END_RDSTD_NAMESPACE
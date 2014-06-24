/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdrdMutex.cpp
* 当前版本: 1.0
* 摘  要:
*
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录:
***************************************************************************/
#include "rdMutex.h"
#include "rdError.h"

#ifndef _WIN32
#include "rdTime.h"
#include <pthread.h>
#endif // _WIN32

BEGIN_RDSTD_NAMESPACE


rdMutex::rdMutex() {
	#ifdef _WIN32
		_mutex = CreateMutex(NULL, FALSE, NULL);
	#else
		int32_t ret = 0;
		pthread_mutexattr_t attr;

		ret = pthread_mutexattr_init(&attr);
		if (0 != ret) {
			ret = pthread_mutex_init(&this->_mutex, NULL);
		} else {
			ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);
			ret = pthread_mutex_init(&_mutex, &attr);
			pthread_mutexattr_destroy(&attr);
		}
	#endif
}

rdMutex::~rdMutex() {
	#ifdef _WIN32
		BOOL ret = CloseHandle(_mutex);
		if (0 != ret) {
			_mutex = NULL;
		}
	#else
		pthread_mutex_destroy(&_mutex);
	#endif
}

int32_t rdMutex::lock(uint32_t millisecond) {
	#ifdef _WIN32
		if (NULL == _mutex) {
			return E_NULL_POINTER;
		}

		DWORD ret = WaitForSingleObject(_mutex, millisecond);
		if (WAIT_OBJECT_0 == ret) {
			return 0;
		}
		else if (WAIT_TIMEOUT == ret) {
			return E_TIMEOUT;
		}
		else {
			return E_SYSERROR;
		}
	#else
		int32_t ret = 0;

		if (WAIT_INFINITE == millisecond) {
			ret = pthread_mutex_lock(&_mutex);
		}
		else {
			struct timespec ts = {0, 0};
			rdTime::get_abs_timespec(&ts, millisecond);
			ret = pthread_mutex_timedlock(&_mutex, &ts);
		}

		if (0 != ret) {
			int32_t e = rdGetLastError();
			if (ETIMEDOUT == e) {
				return E_TIMEOUT;
			}
			else {
				return E_SYSERROR;
			}
		}
		return 0;
	#endif
}

int32_t rdMutex::try_lock() {
	#ifdef _WIN32
		return lock(1);
	#else
		int32_t ret = 0;
		ret = pthread_mutex_trylock(&_mutex);
		return (0 == ret ? 0 : E_SYSERROR);
	#endif
}

int32_t rdMutex::unlock() {
	#ifdef _WIN32
		BOOL ret = FALSE;

		if (NULL != _mutex) {
			ret = ReleaseMutex(_mutex);
		}
		return (0 != ret ? 0 : E_SYSERROR);
	#else
		int32_t ret = 0;
		ret = pthread_mutex_unlock(&_mutex);
		return (0 == ret ? 0 : E_SYSERROR);
	#endif
}

END_RDSTD_NAMESPACE

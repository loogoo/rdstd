/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdMutexEx.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:

* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#include "rdMutexEx.h"
#include "rdError.h"

BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32

rdMutexEx::rdMutexEx()
{
	InitializeCriticalSection(&_mutex);
	_initialized = true;
}

rdMutexEx::~rdMutexEx() 
{
	DeleteCriticalSection(&_mutex);
	_initialized = false;
}

bool rdMutexEx::isInitialized() 
{ 
	return _initialized;
}

int32_t rdMutexEx::lock() 
{
	if (_initialized) { 
		EnterCriticalSection(&_mutex);

		return 0;
	}

	return E_NULL_POINTER;
}

int32_t rdMutexEx::unlock() 
{
	if (_initialized) { 
		LeaveCriticalSection(&_mutex);

		return 0;
	}

	return E_NULL_POINTER;
}


#else

rdMutexEx::rdMutexEx() 
{
#ifdef VXWORKS
	memset(&_mutex, '\0', sizeof(_mutex));
#endif // VXWORKS
	int rc = pthread_mutex_init(&_mutex, NULL);
	assert(rc == 0);

	_initialized = true;
}

rdMutexEx::~rdMutexEx() 
{
	int rc = pthread_mutex_destroy(&_mutex);
	assert(rc == 0);

	_initialized = false;
}


bool rdMutexEx::isInitialized() 
{ 
	return _initialized;
}


int32_t rdMutexEx::lock() 
{
	if (_initialized) 
	{ 
		int rc = pthread_mutex_lock(&_mutex);
		assert(rc == 0);

		return 0;
	}

	return E_NULL_POINTER;
}

int32_t rdMutexEx::unlock() 
{
	if (_initialized) 
	{ 
		int rc = pthread_mutex_unlock(&_mutex);
		assert(rc == 0);

		return 0;
	}

	return E_NULL_POINTER;
}

#endif


END_RDSTD_NAMESPACE
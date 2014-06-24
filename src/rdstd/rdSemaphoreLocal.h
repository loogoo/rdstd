/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdSemaphoreLocal.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��6��14��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_SEMAPHORE_LOCAL_H_
#define _RD_SEMAPHORE_LOCAL_H_

#include "rdSemaphore.h"
#include "rdMutex.h"

BEGIN_RDSTD_NAMESPACE
 
#ifdef _WIN32

class RD_STD_DLL_ENTRY rdSemaphoreLocal : public rdSemaphore { 
public:
	bool wait(rdMutex& mutex, time_t timeoutMsec) ;
	void wait(rdMutex& mutex);
	bool open(unsigned initValue = 0);
};

#else

class dbLocalSemaphore { 
	pthread_cond_t   cond;
	int              count;
public:
	void wait(rdMutex& mutex);
	bool wait(rdMutex& mutex, time_t timeout);
	void signal(unsigned inc = 1);
	void open(unsigned initValue = 0);
	void close();
};

#endif


END_RDSTD_NAMESPACE

#endif

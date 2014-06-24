/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdEventLocal.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��6��14��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_EVENT_LOCAL_H_
#define _RD_EVENT_LOCAL_H_

#include "rdMutex.h"
#include "rdEvent.h"

BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32
class RD_STD_DLL_ENTRY rdEventLocal : public rdEvent
{
public:
	bool wait(rdMutex& mutex, time_t timeoutMsec);
	void wait(rdMutex& mutex);
	bool open(bool signaled = false);
};
#else

class RD_STD_DLL_ENTRY rdEventLocal { 
protected:
	pthread_cond_t   cond;
	int              signaled;
public:
	void wait(rdMutex& mutex);
	bool wait(rdMutex& mutex, time_t timeout);
	void signal();
	void reset();
	void open(bool initValue = false);
	void close();
};

#endif

END_RDSTD_NAMESPACE

#endif
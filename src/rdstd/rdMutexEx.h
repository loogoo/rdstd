/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdMutexEx.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_MUTEXEX_H_
#define _RD_MUTEXEX_H_

#include "rdstdtp.h"
#include "rdGuard.h"

BEGIN_RDSTD_NAMESPACE


class RD_STD_DLL_ENTRY rdMutexEx
{
#ifndef _WIN32
	friend class dbLocalEvent;
	friend class dbLocalSemaphore;
#endif

public:
	rdMutexEx();
	~rdMutexEx();


	/**
	 * @brief isInitialized �ж��Ƿ��ʼ��
	 *
	 *
	 * @return bool
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 16ʱ27��46��
	 */
	bool isInitialized();



	/** 
	 * @brief lock  ��������
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 16ʱ28��01��
	 */
	int32_t lock() ;


	/**
	 * @brief unlock ��������
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 16ʱ28��23��
	 */
	int32_t unlock();

protected:
	mutex_cs _mutex;
	bool	 _initialized;
};

typedef rdGuard<rdMutexEx> rdScopedMutex_cs;

END_RDSTD_NAMESPACE

#endif
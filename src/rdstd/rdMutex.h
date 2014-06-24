/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdrdMutex.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_MUTEX_H_
#define _RD_MUTEX_H_

#include "rdstdtp.h"
#include "rdGuard.h"

BEGIN_RDSTD_NAMESPACE

/**
 * @brief ʵ���̼߳�Ļ������
 * @see
 * @note
 * @author  liy
 * @date    2014��5��23�� 15ʱ42��34��
 */
class RD_STD_DLL_ENTRY rdMutex {

#ifndef _WIN32
	friend class dbLocalEvent;
	friend class dbLocalSemaphore;
#endif

public:

    rdMutex();
    ~rdMutex();

    /**
     * @brief lock ��������
     *
     * @param uint32_t millisecond
     *
     * @return int32_t
     *
     * @see
     * @note
     *
     * @author liy
     * @date   2014��5��23�� 15ʱ43��19��
     */
    int32_t lock(uint32_t millisecond = WAIT_INFINITE);

    /**
     * @brief try_lock ���Լ�������
     *
     *
     * @return int32_t
     *
     * @see
     * @note
     *
     * @author liy
     * @date 2014��5��23�� 15ʱ42��26��
     */
    int32_t try_lock();


    /**
     * @brief unlock ��������
     *
     *
     * @return int32_t
     *
     * @see
     * @note
     *
     * @author liy
     * @date 2014��5��23�� 15ʱ42��17��
     */
    int32_t unlock();

protected:
    /**
     * @brief rdMutex ���ÿ������캯��
     *
     * @param const rdMutex &
     *
     * @return 
     *
     * @see
     * @note
     *
     * @author liy
     * @date 2014��5��23�� 15ʱ42��00��
     */
    rdMutex(const rdMutex&);


    /**
     * @brief operator= ���ø�ֵ�����
     *
     * @param const rdMutex &
     *
     * @return rdMutex&
     *
     * @author liy
     * @date 2014��5��23�� 15ʱ40��56��
     */
    rdMutex& operator=(const rdMutex&);

private:
    mutex_t _mutex;

}; // end of class rdMutex

typedef rdGuard<rdMutex> rdScopedMutex;

END_RDSTD_NAMESPACE

#endif
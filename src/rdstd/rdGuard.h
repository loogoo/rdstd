/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdGuard.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			��rdMutex����
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_GUARD_H_
#define _RD_GUARD_H_

#include <stdlib.h>
#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE

template <typename LockType>
class RD_STD_DLL_ENTRY rdGuard {
public:
    /**
     * @brief Guard ���캯������rdMutex����
     *
     * @param lock ������ָ��
     */
    rdGuard(LockType* lock) : _locked(false), _lock(lock) {
        if (NULL != _lock) {
            if (0 == _lock->lock()) {
                _locked = true;
            }
        }
    }

	 /**
     * @brief ~Guard ������������rdMutex����
     */
    ~rdGuard() {
        if (NULL != _lock) {
            if (0 == _lock->unlock()) {
                _locked = false;
            }
        }
    }

    /**
     * @brief is_locked �������Ƿ�ɹ�
     *
     * @return �����ɹ�����true�����򷵻�false
     */
    bool is_locked() const {
        return _locked;
    }

   
private:
    mutable bool _locked;
    LockType* _lock;
};

END_RDSTD_NAMESPACE


#endif
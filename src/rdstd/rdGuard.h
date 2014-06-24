/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdGuard.h 
* 当前版本: 1.0
* 摘  要:
*			对rdMutex加锁
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
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
     * @brief Guard 构造函数，对rdMutex加锁
     *
     * @param lock 待加锁指针
     */
    rdGuard(LockType* lock) : _locked(false), _lock(lock) {
        if (NULL != _lock) {
            if (0 == _lock->lock()) {
                _locked = true;
            }
        }
    }

	 /**
     * @brief ~Guard 析构函数，对rdMutex解锁
     */
    ~rdGuard() {
        if (NULL != _lock) {
            if (0 == _lock->unlock()) {
                _locked = false;
            }
        }
    }

    /**
     * @brief is_locked 检测加锁是否成功
     *
     * @return 加锁成功返回true；否则返回false
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
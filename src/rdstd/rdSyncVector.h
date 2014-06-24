/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdSyncVector.h 
* 当前版本: 1.0
* 摘  要:
*
*			线程安全vector
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#ifndef _RD_SYNCVECTOR_H_
#define _RD_SYNCVECTOR_H_

#include <vector>
#include "rdMutex.h"
#include "rdSemaphore.h"

#include "rdError.h"
#include "rdShared.h"


BEGIN_RDSTD_NAMESPACE

template <typename ElemType>
class RD_STD_DLL_ENTRY rdSyncVector : public rdShared {
public:
    rdSyncVector() { }
    typedef rdGuard<rdMutex> ScopedGuard;

    /**
     * @brief put 向同步vector中添加元素（允许重复）。同时触发信号量
     *
     * @param elem 新元素
     *
     * @return 添加成功返回0；否则返回错误码
     */
    int32_t put(ElemType elem) {
        {
            ScopedGuard guard(&_mutex);
            if (guard.is_locked()) {
                try {
                    _vector.push_back(elem);
                }
                catch(std::bad_alloc &) {
                    return E_NOMEM;
                }
            }
            else {
                return E_SYSERROR;
            }
        }
        _sem.signal();
        return 0;
    }

    /**
     * @brief get 从同步vector中取元素。如果同步vector为空，将阻塞指定时长WAIT_INFINITE表示无限阻塞。
     *
     * @param elem 取得的元素
     * @param millisecond 超时时长（毫秒）
     *
     * @return 成功返回0；否则返回错误码: E_TIMEOUT表示超时.
     */
    int32_t get(ElemType& elem, int millisecond) {
        int32_t ret = _sem.wait(millisecond);

        if (0 == ret) {
            {
                ScopedGuard guard(&_mutex);
                if (guard.is_locked()) {
                    elem = _vector.back();
                    _vector.pop_back();
                }
                else {
                    return E_SYSERROR;
                }
            }
            return 0;
        }
        else {
            return ret;
        }
    }

    int32_t size() {
        ScopedGuard guard(&_mutex);
        return (int32_t)_vector.size();
    }

protected:
    rdSyncVector(const rdSyncVector&);
    rdSyncVector& operator=(const rdSyncVector&);

private:
    std::vector<ElemType> _vector;
    rdMutex _mutex;
    rdSemaphore _sem;

}; // end of class rdSyncVector


END_RDSTD_NAMESPACE

#endif

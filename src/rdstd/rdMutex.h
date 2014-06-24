/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdrdMutex.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
***************************************************************************/
#ifndef _RD_MUTEX_H_
#define _RD_MUTEX_H_

#include "rdstdtp.h"
#include "rdGuard.h"

BEGIN_RDSTD_NAMESPACE

/**
 * @brief 实现线程间的互斥访问
 * @see
 * @note
 * @author  liy
 * @date    2014年5月23日 15时42分34秒
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
     * @brief lock 加锁操作
     *
     * @param uint32_t millisecond
     *
     * @return int32_t
     *
     * @see
     * @note
     *
     * @author liy
     * @date   2014年5月23日 15时43分19秒
     */
    int32_t lock(uint32_t millisecond = WAIT_INFINITE);

    /**
     * @brief try_lock 尝试加锁操作
     *
     *
     * @return int32_t
     *
     * @see
     * @note
     *
     * @author liy
     * @date 2014年5月23日 15时42分26秒
     */
    int32_t try_lock();


    /**
     * @brief unlock 解锁操作
     *
     *
     * @return int32_t
     *
     * @see
     * @note
     *
     * @author liy
     * @date 2014年5月23日 15时42分17秒
     */
    int32_t unlock();

protected:
    /**
     * @brief rdMutex 禁用拷贝构造函数
     *
     * @param const rdMutex &
     *
     * @return 
     *
     * @see
     * @note
     *
     * @author liy
     * @date 2014年5月23日 15时42分00秒
     */
    rdMutex(const rdMutex&);


    /**
     * @brief operator= 禁用赋值运算符
     *
     * @param const rdMutex &
     *
     * @return rdMutex&
     *
     * @author liy
     * @date 2014年5月23日 15时40分56秒
     */
    rdMutex& operator=(const rdMutex&);

private:
    mutex_t _mutex;

}; // end of class rdMutex

typedef rdGuard<rdMutex> rdScopedMutex;

END_RDSTD_NAMESPACE

#endif
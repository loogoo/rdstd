/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadpool.h 
* 当前版本: 1.0
* 摘  要:
*
*		线程池维护一组预先创建好的线程及一个任务队列。线程依次执行任务队列中的任务。
*
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#ifndef _RD_THREADPOOL_H_
#define _RD_THREADPOOL_H_

#include "rdRunable.h"
#include "rdSyncVector.h"
#include "rdThreadgroup.h"
#include "rdShared.h"

BEGIN_RDSTD_NAMESPACE

class RD_STD_DLL_ENTRY rdThreadPool : public rdShared 
{
public:
    /**
     * @class state_t
     * @brief 线程池状态
     */
    enum state_t {
        UNINITIALIZED, INITIALIZED
    };

    /**
     * @brief   构造函数
     * @param   
     * @return  
     */
    rdThreadPool();

    /**
     * @brief   析构函数
     * @param   
     * @return  
     */
    ~rdThreadPool();

    /** 线程池中默认线程个数 */
    static const int DEFAULT_THREADS_NUM = 10;

    /**
     * @brief   初始化线程池，创建规定个数的线程
     * @param   nThreads 创建线程的个数
     * @return  成功返回0
     */
    int init(int nThreads = DEFAULT_THREADS_NUM);

    /**
     * @brief   向任务队列中添加任务
     * @param   pr 待添加的任务
     * @return  成功返回true
     */
    bool addTask(rdRunablePtr pr);

    /**
     * @brief  等待所有线程执行完毕。请不要调用此方法，线程池中的线程永远不会自动执行结束
     * @param   
     * @return  
     */
    bool join();

    /**
     * @brief   获取线程个数
     * @param   
     * @return  当前线程池中线程个数
     */
    size_t size();

    /**
     * @brief   终止所有线程的执行
     * @param   
     * @return  
     */
    bool terminate();


private:
    /*
    * addWorker: 向线程池中添加nWorker个线程
    */
    int addWorker(int nWorker);

    friend class rdThreadPoolRunner;

    /* 添加到线程池中的任务 */
    rdSyncVector<rdRunablePtr> _tasks;

    /* 线程组 */
    rdThreadGroup _threadGroup;
    state_t _state;

private:
	class rdThreadPoolRunner;
};

END_RDSTD_NAMESPACE

#endif


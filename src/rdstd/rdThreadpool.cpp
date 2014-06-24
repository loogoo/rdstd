/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadpool.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#include <iostream>
#include "rdThreadpool.h"
#include "rdThreadManager.h"

BEGIN_RDSTD_NAMESPACE

/**
 * @class ThreadPoolRunner
 * @brief 线程池任务类型
 */
class rdThreadPool::rdThreadPoolRunner : public rdRunable 
{
public:
    /**
     * @brief   线程池构造函数
     * @param   tp 线程池
     * @return  
     */
    rdThreadPoolRunner(rdThreadPool* tp);

    /**
     * @brief   执行体
     * @param   
     * @return  
     */
    virtual int32_t operator()(void* param);
private:
    rdThreadPool* _tp;
};


rdThreadPool::rdThreadPoolRunner::rdThreadPoolRunner(rdThreadPool* tp) : _tp(tp) 
{
}

int32_t rdThreadPool::rdThreadPoolRunner::operator()(void* param) 
{
    while (true) {
        rdRunablePtr pr;
        _tp->_tasks.get(pr, WAIT_INFINITE);
        if (pr.is_valid()) {
            (*pr)();
        }
    }
    return 1;
}


//////////////////////////////////////////////////////////////////////////


rdThreadPool::rdThreadPool() : _state(UNINITIALIZED) 
{
}

rdThreadPool::~rdThreadPool() 
{
    terminate();
}

int rdThreadPool::init(int nThreads) 
{
    int ret = 0;
    if (UNINITIALIZED == _state) {
        _state = INITIALIZED;

        addWorker(nThreads);
    }

    return ret;
}

bool rdThreadPool::addTask(rdRunablePtr pr) 
{
    return 0 == _tasks.put(pr);
}

bool rdThreadPool::join() 
{
    return _threadGroup.join();
}

size_t rdThreadPool::size() 
{
    return _threadGroup.size();
}

bool rdThreadPool::terminate() 
{
    return _threadGroup.terminateAll();
}

int rdThreadPool::addWorker(int nWorker) 
{
    int ret = 0;
    for (int i = 0; i < nWorker; ++i) {
		// 创建并开始线程
        rdSharedPtr<rdThread> workerThread = rdThreadManager::createThread(
                rdRunablePtr(new rdThreadPoolRunner(this)));
        if (workerThread.is_valid()) {
            _threadGroup.addThread(workerThread);
            ++ret;
        }
    }
    return ret;
}


END_RDSTD_NAMESPACE
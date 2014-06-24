/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThreadpool.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
***************************************************************************/
#include <iostream>
#include "rdThreadpool.h"
#include "rdThreadManager.h"

BEGIN_RDSTD_NAMESPACE

/**
 * @class ThreadPoolRunner
 * @brief �̳߳���������
 */
class rdThreadPool::rdThreadPoolRunner : public rdRunable 
{
public:
    /**
     * @brief   �̳߳ع��캯��
     * @param   tp �̳߳�
     * @return  
     */
    rdThreadPoolRunner(rdThreadPool* tp);

    /**
     * @brief   ִ����
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
		// ��������ʼ�߳�
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
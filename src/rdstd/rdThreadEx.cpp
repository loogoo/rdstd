/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadEx.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月24日
* 修改记录: 
***************************************************************************/
#include "rdThreadEx.h"

BEGIN_RDSTD_NAMESPACE


//////////////////////////////////////////////////////////////////////////
void thread_proc dbPooledThread::pooledThreadFunc(void* arg)
{
	((dbPooledThread*)arg)->run();
}

dbPooledThread::dbPooledThread(dbThreadPool* threadPool)
{
	pool = threadPool;
	startSem.open();
	readySem.open();
	next = NULL;
	running = true;
	thread.create(&pooledThreadFunc, this);
}

dbPooledThread::~dbPooledThread()
{
	startSem.close();
	readySem.close();
}

void dbPooledThread::stop() 
{
	running = false;
	startSem.signal(); 
	readySem.wait(pool->mutex);
}

void dbPooledThread::run() 
{
	rdScopedMutex_cs localMutex(&pool->mutex);

	while (true) { 
		startSem.wait(pool->mutex);
		if (!running) { 
			break;
		}
		(*f)(arg);
		readySem.signal();
	}
	readySem.signal();
}


//////////////////////////////////////////////////////////////////////////
void dbThreadPool::join(dbPooledThread* thr) 
{ 
	rdScopedMutex_cs localMutex(&mutex);

	thr->readySem.wait(mutex);
	thr->next = freeThreads;
	freeThreads = thr;
}


dbPooledThread* dbThreadPool::create(dbThread::thread_proc_t f, void* arg)
{
	rdScopedMutex_cs localMutex(&mutex);

	dbPooledThread* t = freeThreads;
	if (t == NULL) { 
		t = freeThreads = new dbPooledThread(this);
	}
	freeThreads = t->next;
	t->f = f;
	t->arg = arg;
	t->startSem.signal();
	return t;
}


dbThreadPool::dbThreadPool()
{
	freeThreads = NULL;
}

dbThreadPool::~dbThreadPool()
{
	rdScopedMutex_cs localMutex(&mutex);

	dbPooledThread *t, *next;
	for (t = freeThreads; t != NULL; t = next) { 
		next = t->next;
		t->stop();
		delete t;
	}        
}


END_RDSTD_NAMESPACE
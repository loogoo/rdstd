/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadEx.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月24日
* 修改记录: 
***************************************************************************/
#ifndef _RD_THREAD_EX_H_
#define _RD_THREAD_EX_H_

#include "rdMutexEx.h"
#include "rdSemaphoreLocal.h"


BEGIN_RDSTD_NAMESPACE


//////////////////////////////////////////////////////////////////////////
//                           dbThread								    //
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32

#define thread_proc WINAPI

class RD_STD_DLL_ENTRY dbThread 
{ 
	HANDLE h;

public:
	typedef void (thread_proc* thread_proc_t)(void*);


	dbThread() { 
		h = NULL; 
	}
	virtual ~dbThread() { 
		if (h != NULL) { 
			CloseHandle(h);
		}
	}

	void create(thread_proc_t f, void* arg) { 
		DWORD threadid;
		h = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(f), arg,
			0, &threadid);
	}
	enum ThreadPriority { 
		THR_PRI_LOW, 
		THR_PRI_HIGH
	};

	void setPriority(ThreadPriority pri) { 
		SetThreadPriority(h, pri == THR_PRI_LOW ? THREAD_PRIORITY_IDLE : THREAD_PRIORITY_HIGHEST);
	}

	static void sleep(time_t sec) { 
		Sleep((DWORD)(sec*1000));
	}


	void join() { 
		WaitForSingleObject(h, INFINITE);
		CloseHandle(h);
		h = NULL;
	}

	void detach() { 
		if (h != NULL) { 
			CloseHandle(h);
			h = NULL;
		}
	}

	static long getCurrentThreadId() {
		return GetCurrentThreadId();
	}

	static int numberOfProcessors() { 
#ifdef PHAR_LAP
		return 1;
#else
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);
		return sysinfo.dwNumberOfProcessors;
#endif
	}
};

#else

class dbThread { 
public:
	virtual ~dbThread() {}
	typedef void (thread_proc* thread_proc_t)(void*);
	void create(thread_proc_t f, void* arg) { f(arg); }
	void join() {}
	void detach() {}
	enum ThreadPriority { 
		THR_PRI_LOW, 
		THR_PRI_HIGH
	};
	void setPriority(ThreadPriority pri) { }
	static int numberOfProcessors() { return 1; }
};

#endif



//////////////////////////////////////////////////////////////////////////
//                           dbPooledThread							    //
//////////////////////////////////////////////////////////////////////////

class dbThreadPool;

class RD_STD_DLL_ENTRY dbPooledThread { 
private:
	friend class dbThreadPool;

	dbThread                thread;
	dbThreadPool*           pool;
	dbPooledThread*         next;
	dbThread::thread_proc_t f;
	void*                   arg;
	bool                    running;
	rdSemaphoreLocal        startSem;
	rdSemaphoreLocal        readySem;

	static void thread_proc  pooledThreadFunc(void* arg);

	void run();
	void stop();

	dbPooledThread(dbThreadPool* threadPool); 
	~dbPooledThread(); 
};



//////////////////////////////////////////////////////////////////////////
//                           dbThreadPool							    //
//////////////////////////////////////////////////////////////////////////
class RD_STD_DLL_ENTRY dbThreadPool { 
	friend class dbPooledThread;
	dbPooledThread* freeThreads;
	rdMutexEx         mutex;

public:
	dbPooledThread* create(dbThread::thread_proc_t f, void* arg);
	void join(dbPooledThread* thr);
	dbThreadPool();
	~dbThreadPool();
};


END_RDSTD_NAMESPACE

#endif
/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThread.h 
* 当前版本: 1.0
* 摘  要:
*
*			操作系统线程模型的抽象，负责线程的创建、执行、等待、休眠以及销毁
*
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#ifndef _RD_THTREAD_H_
#define _RD_THTREAD_H_

#include "rdRunable.h"
#include "rdSharedPtr.h"
#include "rdSemaphore.h"

BEGIN_RDSTD_NAMESPACE

typedef void* (*run_func_t)(void*);
typedef rdSharedPtr<rdRunable> rdRunablePtr;


class RD_STD_DLL_ENTRY rdThread : public rdShared 
{
public:
    /**
     * @brief Thread 构造函数
     *
     * @param runner 线程执行的任务
     * @param detached 是否分离
     */
    rdThread(const rdRunablePtr& runner, bool detached = false);

    /**
     * @brief Thread 构造函数
     *
     * @param func 线程执行的任务
     * @param detached 是否分离
     */
    rdThread(run_func_t func, void* arg = NULL, bool detached = false);

    /**
     * @brief ~Thread 析构函数
     */
    ~rdThread();

    /**
     * @brief start 启动线程的执行
     *
     * @return 成功返回true
     */
    bool start();

    /**
     * @brief join 等待线程执行结束
     *
     * @return 成功返回true
     */
    bool join();

    /**
     * @brief stop 终止线程的执行
     *
     * @return 成功返回true
     */
    bool stop();

#ifdef _WIN32
    /**
     * @brief get_thread_id 返回线程ID，仅在Windows下使用
     *
     * @return 线程ID
     */
    DWORD get_thread_id() const;

    /**
     * @brief HANDLE 返回线程句柄，仅在Windows下使用
     *
     * @return 线程句柄
     */
    operator HANDLE();

#else
    /**
     * @brief get_thread_id 返回线程ID，仅在Linux下使用
     *
     * @return 线程ID
     */
    pthread_t get_thread_id() const;
#endif

private:
	enum state_t {
		INIT,
		START,
		JOINED,
		STOP
	};

private:
    bool setDetached();
#ifdef _WIN32
    static DWORD __stdcall thread_start_func(LPVOID lpParam);
#else
    static void* thread_start_func(void* arg);
#endif
private:
    bool			_use_functor;
    rdRunablePtr	_functor;
    run_func_t		_func_ptr;
    void*			_func_arg;
    rdSemaphore		_sema;
    mutable bool	_detached;
    state_t			_state;

#ifdef _WIN32
    HANDLE _handle;
    DWORD _thread_id;
#else
    pthread_t _thread;
#endif

};

END_RDSTD_NAMESPACE

#endif


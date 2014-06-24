/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThread.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#include <errno.h>

#ifdef _WIN32
#include <process.h>
#endif

#include "rdThread.h"
#include "rdTime.h"

BEGIN_RDSTD_NAMESPACE

rdThread::rdThread(const rdRunablePtr& runner, bool detached)
    : _use_functor(true),
    _functor(runner),
    _func_ptr(NULL),
    _func_arg(NULL),
    _detached(detached),
    _state(INIT)
#ifdef _WIN32
      ,_handle(NULL)
#endif
{ }

rdThread::rdThread(run_func_t func, void* arg, bool detached)
    : _use_functor(false),
    _func_ptr(func),
    _func_arg(arg),
    _detached(detached),
    _state(INIT)
#ifdef _WIN32
      ,_handle(NULL)
#endif
{ }

rdThread::~rdThread() {
    join();
    _state = STOP;
}

bool rdThread::start() {
    if (INIT != _state) {
        return false;
    }
#ifdef _WIN32
    _handle = ::CreateThread(NULL, 0, 
            (LPTHREAD_START_ROUTINE)thread_start_func, this, 0, &_thread_id);

    if (NULL != _handle) {
        rdTime::safe_sleep_s(0);
        _sema.wait();
    }
    _state = START;

    return (NULL != _handle);
#else
    int ret;
    pthread_attr_t attr;

    ret = pthread_attr_init(&attr);
    if (0 != ret) {
        return false;
    }

    ret = pthread_attr_setdetachstate(&attr,
            _detached ? PTHREAD_CREATE_DETACHED : PTHREAD_CREATE_JOINABLE);
    if (0 != ret) {
        pthread_attr_destroy(&attr);
        return false;
    }

    ret = pthread_create(&_thread, &attr, thread_start_func, (void*)this);

    if (0 == ret) {
        rdTime::safe_sleep_s(0);
        _sema.wait();
    }

    pthread_attr_destroy(&attr);

    if (0 != ret) {
        return false;
    }

    _state = START;
    return true;
#endif
}

bool rdThread::join() {
    if (START != _state) {
        return false;
    }
#ifdef _WIN32
    bool ret = false;
    if (!_detached) {
        if (NULL != _handle) {
            DWORD dw = ::WaitForSingleObject(_handle, INFINITE);
            if (WAIT_OBJECT_0 == dw || WAIT_ABANDONED == dw) {
                ret = true;
                _handle = NULL;
            }
        }
        _state = JOINED;
    }
    return ret;
#else
    bool ret = false;

    if (!pthread_equal(pthread_self(), _thread)) {
        if (!_detached) {
            int r = pthread_join(_thread, NULL);
            if (0 == r) {
                _state = JOINED;
            }
            ret = (0 == r);
        }
    } else {
        ret = false;
    }
    return ret;
#endif 
}

bool rdThread::stop() {
    bool ret = true;
    if (_state != STOP && _state >= START) {
#ifdef _WIN32
        _state = STOP;
        ret = ::TerminateThread(_handle, 0) != 0;
#else
        int r = pthread_cancel(_thread);
        if (0 != r) {
            ret = false;
        } else {
            _state = STOP;
            ret = true;
        }
#endif
    }
    return ret;
}

#ifdef _WIN32
DWORD rdThread::get_thread_id() const {
    return _thread_id;
}

rdThread::operator HANDLE() {
    return _handle;
}

DWORD __stdcall rdThread::thread_start_func(LPVOID lpParam) {
    rdThread *me = (rdThread*)lpParam;
    rdRunablePtr runner = me->_functor;
    bool use_functor = me->_use_functor;
    run_func_t func = me->_func_ptr;
    void* arg = me->_func_arg;
    me->_sema.signal();

    DWORD ret = 0;
    if (use_functor) {
        if (runner.is_valid()) {
            ret = (*runner)();
        }
    }
    else {
        if (func) {
            func(arg);
        }
    }

    return ret;
}
#else
pthread_t rdThread::get_thread_id() const {
    return _thread;
}

void* rdThread::thread_start_func(void *arg) {
    rdThread* me = (rdThread*)arg;
    rdRunablePtr runner = me->_functor;
    bool use_functor = me->_use_functor;
    run_func_t func = me->_func_ptr;
    void* func_arg = me->_func_arg;
    me->_sema.signal();

    if (use_functor) {
        if (runner.is_valid()) {
            (*runner)();
        }
    }
    else {
        if (func) {
            func(func_arg);
        }
    }
    return NULL;
} 
#endif


END_RDSTD_NAMESPACE


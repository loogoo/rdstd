/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThread.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*
*			����ϵͳ�߳�ģ�͵ĳ��󣬸����̵߳Ĵ�����ִ�С��ȴ��������Լ�����
*
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
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
     * @brief Thread ���캯��
     *
     * @param runner �߳�ִ�е�����
     * @param detached �Ƿ����
     */
    rdThread(const rdRunablePtr& runner, bool detached = false);

    /**
     * @brief Thread ���캯��
     *
     * @param func �߳�ִ�е�����
     * @param detached �Ƿ����
     */
    rdThread(run_func_t func, void* arg = NULL, bool detached = false);

    /**
     * @brief ~Thread ��������
     */
    ~rdThread();

    /**
     * @brief start �����̵߳�ִ��
     *
     * @return �ɹ�����true
     */
    bool start();

    /**
     * @brief join �ȴ��߳�ִ�н���
     *
     * @return �ɹ�����true
     */
    bool join();

    /**
     * @brief stop ��ֹ�̵߳�ִ��
     *
     * @return �ɹ�����true
     */
    bool stop();

#ifdef _WIN32
    /**
     * @brief get_thread_id �����߳�ID������Windows��ʹ��
     *
     * @return �߳�ID
     */
    DWORD get_thread_id() const;

    /**
     * @brief HANDLE �����߳̾��������Windows��ʹ��
     *
     * @return �߳̾��
     */
    operator HANDLE();

#else
    /**
     * @brief get_thread_id �����߳�ID������Linux��ʹ��
     *
     * @return �߳�ID
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


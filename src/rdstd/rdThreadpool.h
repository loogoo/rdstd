/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThreadpool.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*
*		�̳߳�ά��һ��Ԥ�ȴ����õ��̼߳�һ��������С��߳�����ִ����������е�����
*
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
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
     * @brief �̳߳�״̬
     */
    enum state_t {
        UNINITIALIZED, INITIALIZED
    };

    /**
     * @brief   ���캯��
     * @param   
     * @return  
     */
    rdThreadPool();

    /**
     * @brief   ��������
     * @param   
     * @return  
     */
    ~rdThreadPool();

    /** �̳߳���Ĭ���̸߳��� */
    static const int DEFAULT_THREADS_NUM = 10;

    /**
     * @brief   ��ʼ���̳߳أ������涨�������߳�
     * @param   nThreads �����̵߳ĸ���
     * @return  �ɹ�����0
     */
    int init(int nThreads = DEFAULT_THREADS_NUM);

    /**
     * @brief   ������������������
     * @param   pr ����ӵ�����
     * @return  �ɹ�����true
     */
    bool addTask(rdRunablePtr pr);

    /**
     * @brief  �ȴ������߳�ִ����ϡ��벻Ҫ���ô˷������̳߳��е��߳���Զ�����Զ�ִ�н���
     * @param   
     * @return  
     */
    bool join();

    /**
     * @brief   ��ȡ�̸߳���
     * @param   
     * @return  ��ǰ�̳߳����̸߳���
     */
    size_t size();

    /**
     * @brief   ��ֹ�����̵߳�ִ��
     * @param   
     * @return  
     */
    bool terminate();


private:
    /*
    * addWorker: ���̳߳������nWorker���߳�
    */
    int addWorker(int nWorker);

    friend class rdThreadPoolRunner;

    /* ��ӵ��̳߳��е����� */
    rdSyncVector<rdRunablePtr> _tasks;

    /* �߳��� */
    rdThreadGroup _threadGroup;
    state_t _state;

private:
	class rdThreadPoolRunner;
};

END_RDSTD_NAMESPACE

#endif


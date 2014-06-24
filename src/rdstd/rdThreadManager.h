/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThreadManager.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _BGCC_THREADMANAGER_H_
#define _BGCC_THREADMANAGER_H_

#include "rdThread.h"
#include "rdSharedPtr.h"


BEGIN_RDSTD_NAMESPACE

/**
 * @class ThreadManger
 * @brief ���ڴ����µ��߳�
 */
class RD_STD_DLL_ENTRY rdThreadManager 
{
public:
    /**
     * @brief   �����µ��߳�
     * @param   pr �߳�ִ�е�����
     * @return  
     */
    static rdSharedPtr<rdThread> createThread(rdSharedPtr<rdRunable> pr);

private:
    rdThreadManager(const rdThreadManager&);
    rdThreadManager& operator=(const rdThreadManager&);
};

END_RDSTD_NAMESPACE

#endif


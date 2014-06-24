/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThreadgroup.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_THREADGROUP_H_
#define _RD_THREADGROUP_H_

#include <vector>
#include "rdThread.h"
#include "rdSharedPtr.h"

BEGIN_RDSTD_NAMESPACE

/**
 * @class ThreadGroup
 * @brief ThreadGroup��Thread�ļ��ϣ��������һ������߳�
 */
class RD_STD_DLL_ENTRY rdThreadGroup {
public:
    rdThreadGroup();
    ~rdThreadGroup();

    /**
     * @brief   ������߳�
     * @param   thread ����ӵ����߳�
     * @return  �ɹ�����true
     */
	bool addThread(rdSharedPtr<rdThread> thread);

    /**
     * @brief   �ȴ��߳����е������߳�ִ�н���
     * @param   
     * @return  �ɹ�����true
     */
	bool join();

    /**
     * @brief   ��ȡ�߳����е��̸߳���
     * @param   
     * @return  �߳����е��̸߳���
     */
	size_t size();

    /**
     * @brief   ��ֹ�߳����е������̵߳�ִ��
     * @param   
     * @return  �ɹ�����true
     */
	bool terminateAll();
private:
    rdThreadGroup(const rdThreadGroup&);
    rdThreadGroup& operator=(const rdThreadGroup&);

	std::vector< rdSharedPtr<rdThread> > _threads;
    typedef std::vector< rdSharedPtr<rdThread> >::const_iterator citr_type;
};

END_RDSTD_NAMESPACE

#endif


/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThreadManager.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
***************************************************************************/
#include "rdThreadManager.h"

BEGIN_RDSTD_NAMESPACE

rdSharedPtr<rdThread> rdThreadManager::createThread(rdSharedPtr<rdRunable> pr) 
{
    rdSharedPtr<rdThread> t(new rdThread(pr));
    bool bOk = t->start();
    return bOk ? t : rdSharedPtr<rdThread>(NULL);
}

END_RDSTD_NAMESPACE


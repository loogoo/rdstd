/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThreadutil.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��26��
* �޸ļ�¼: 
***************************************************************************/
#include "rdThreadutil.h"

BEGIN_RDSTD_NAMESPACE

int64_t rdThreadUtil::self_id() {
#ifdef _WIN32
	return (int64_t)GetCurrentThreadId();
#else
	return (int64_t)pthread_self();
#endif
}

END_RDSTD_NAMESPACE


/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThreadutil.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��26��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_THREADUTIL_H_
#define _RD_THREADUTIL_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif
#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE

class rdThreadUtil {
public:
	static int64_t self_id();
};

END_RDSTD_NAMESPACE

#endif


/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdRunable.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_RUNABLE_H_
#define _RD_RUNABLE_H_

#include <stdlib.h>
#include "rdShared.h"

BEGIN_RDSTD_NAMESPACE

class RD_STD_DLL_ENTRY rdRunable : public rdShared {
public:
	virtual int32_t operator()(void* param = NULL) = 0;
	virtual ~rdRunable() { }
};

END_RDSTD_NAMESPACE

#endif


/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdMemops.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��6��3��
* �޸ļ�¼: 
***************************************************************************/
#include "rdMemops.h"

BEGIN_RDSTD_NAMESPACE

void zero_mem(void* ptr, size_t n)
{
	volatile uint8_t* p = reinterpret_cast<volatile uint8_t*>(ptr);

	for(size_t i = 0; i != n; ++i)
		p[i] = 0;
}


END_RDSTD_NAMESPACE

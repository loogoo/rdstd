/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdstdint.h
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼:
***************************************************************************/
#ifndef _RD_STDINT_H_
#define _RD_STDINT_H_

#if defined _WIN32 && _MSC_VER < 1600

	#include <rdstdintPri.h>

	#pragma warning( disable : 4065 4267 )

#else
	#include <stdint.h>
#endif

#endif

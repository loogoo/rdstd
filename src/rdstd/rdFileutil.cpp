/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdFileutil.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��26��
* �޸ļ�¼: 
***************************************************************************/
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#define close _close
#endif

#include <errno.h>
#include "rdFileutil.h"

BEGIN_RDSTD_NAMESPACE

int32_t rdFileUtil::close_r(int32_t fd) 
{
    int32_t ret;

    do {
        ret = close(fd);
    } while(-1 == ret && EINTR == errno);
    return ret;
}


END_RDSTD_NAMESPACE
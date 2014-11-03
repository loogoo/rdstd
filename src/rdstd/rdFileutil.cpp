/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdFileutil.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
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
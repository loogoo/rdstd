/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadutil.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
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


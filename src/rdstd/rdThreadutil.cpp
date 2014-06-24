/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadutil.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
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


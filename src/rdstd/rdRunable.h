/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdRunable.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
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


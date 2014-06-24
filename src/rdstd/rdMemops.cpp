/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdMemops.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月3日
* 修改记录: 
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

/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdstdint.h
* 当前版本: 1.0
* 摘  要:
*
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录:
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

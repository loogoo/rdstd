/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdstdError.h
* 当前版本: 1.0
* 摘  要:
*
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录:
***************************************************************************/
#ifndef _RD_STD_ERROR_H_
#define _RD_STD_ERROR_H_

#include "rdstdtp.h"

#ifdef _WIN32
#include <Windows.h>
#define rdGetLastError() GetLastError()
#else
#include <errno.h>
#include <stdlib.h>
#define rdGetLastError() errno
#endif

BEGIN_RDSTD_NAMESPACE

enum {
	S_SUCCESS,
	E_NULL_POINTER = -10000,
	E_CONF_ERROR,
	E_NOMEM,
	E_INVALID_PARAM,
	E_SYSERROR,
	E_TIMEOUT,
	E_SERVER_ALREADY_INIT,
	E_SERVER_INIT_FAILED,
	E_SERVER_NEED_INIT,
	E_SERVER_CREATE_LISTENFD_FAILED,
	E_SERVICE_NOT_FOUND,
	E_OUT_MAX_TRY_COUNT
};

inline char*  rdstd_strerror_r(int32_t errcode, char* buffer = NULL, int32_t buflen = -1)
{
#ifdef _WIN32
	(void)buffer;
	(void)buflen;
	return strerror(errcode);
#else
	if (NULL == buffer || -1 == buflen) {
		return NULL;
	}
	return strerror_r(errcode, buffer, buflen);
#endif
}

END_RDSTD_NAMESPACE

#endif

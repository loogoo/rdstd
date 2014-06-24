/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdstdtp.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
***************************************************************************/
#include "rdstdtp.h"
#include <stdio.h>

BEGIN_RDSTD_NAMESPACE

static void CLI_CALLBACK_CC stderrTrace(char* msg)
{
    fputs(msg, stderr);
    fflush(stderr);
}

rdTraceFunctionPtr rdTraceFunction = stderrTrace;
bool rdTraceEnable = true;

void rdTrace(char* message, ...) 
{
    if (rdTraceEnable) { 
        va_list args;
        va_start (args, message);
        char buffer[1024];
        vsprintf(buffer, message, args);
        (*rdTraceFunction)(buffer);
        va_end(args);
    }
}

#ifdef USE_DLMALLOC
extern "C" {
	void* dlmalloc(size_t);
	void  dlfree(void*);
}
#endif

uint8_t* rdMalloc(size_t size)
{
#ifdef USE_DLMALLOC
    return (uint8_t*)dlmalloc(size);
#else
    return (uint8_t*)malloc(size);
#endif
}

void  rdFree(void* p)
{
#ifdef USE_DLMALLOC
    dlfree(p);
#else
    free(p);
#endif
}

END_RDSTD_NAMESPACE

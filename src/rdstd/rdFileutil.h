/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdFileutil.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
***************************************************************************/
#ifndef _RD_FILEUTIL_H_
#define _RD_FILEUTIL_H_

#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE

class RD_STD_DLL_ENTRY rdFileUtil 
{
public:
    /**
     * @brief close_r 确保close在遇到中断信号后继续被调用
     *
     * @param fd 文件描述符
     */
    static int32_t close_r(int32_t fd);

};

END_RDSTD_NAMESPACE

#endif


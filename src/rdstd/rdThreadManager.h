/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadManager.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#ifndef _BGCC_THREADMANAGER_H_
#define _BGCC_THREADMANAGER_H_

#include "rdThread.h"
#include "rdSharedPtr.h"


BEGIN_RDSTD_NAMESPACE

/**
 * @class ThreadManger
 * @brief 用于创建新的线程
 */
class RD_STD_DLL_ENTRY rdThreadManager 
{
public:
    /**
     * @brief   创建新的线程
     * @param   pr 线程执行的任务
     * @return  
     */
    static rdSharedPtr<rdThread> createThread(rdSharedPtr<rdRunable> pr);

private:
    rdThreadManager(const rdThreadManager&);
    rdThreadManager& operator=(const rdThreadManager&);
};

END_RDSTD_NAMESPACE

#endif


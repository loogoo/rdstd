/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadManager.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#include "rdThreadManager.h"

BEGIN_RDSTD_NAMESPACE

rdSharedPtr<rdThread> rdThreadManager::createThread(rdSharedPtr<rdRunable> pr) 
{
    rdSharedPtr<rdThread> t(new rdThread(pr));
    bool bOk = t->start();
    return bOk ? t : rdSharedPtr<rdThread>(NULL);
}

END_RDSTD_NAMESPACE


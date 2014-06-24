/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadgroup.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#include "rdThreadgroup.h"

BEGIN_RDSTD_NAMESPACE

rdThreadGroup::rdThreadGroup() {
}

rdThreadGroup::~rdThreadGroup() {
}

bool rdThreadGroup::addThread(rdSharedPtr<rdThread> thread) 
{
    try {
        _threads.push_back(thread);
    } catch(std::bad_alloc& ) {
        return false;
    }
    return true;
}

bool rdThreadGroup::join() 
{
    citr_type citr;

    for (citr = _threads.begin(); citr != _threads.end(); ++citr) 
	{
        (*citr)->join();
    }

    _threads.clear();

    return true;
}

size_t rdThreadGroup::size() 
{
    return _threads.size();
}

bool rdThreadGroup::terminateAll() 
{
    citr_type citr;

    for (citr = _threads.begin(); citr != _threads.end(); ++citr) {
        (*citr)->stop();
    }

    return true;
}

END_RDSTD_NAMESPACE


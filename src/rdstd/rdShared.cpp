/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdShared.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
***************************************************************************/
#include "rdShared.h"

BEGIN_RDSTD_NAMESPACE

rdShared::rdShared() : _count(0) { }

void rdShared::inc() {
    rdScopedMutex guard(&_mutex);
    ++_count;
}

int32_t rdShared::dec() {
    rdScopedMutex guard(&_mutex);

    if (_count > 0) {
        --_count;
    }
    return _count;
}

int32_t rdShared::get_count() {
    rdScopedMutex guard(&_mutex);
    return _count;
}

END_RDSTD_NAMESPACE
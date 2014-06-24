/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdShared.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
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
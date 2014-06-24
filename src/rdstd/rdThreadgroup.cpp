/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdThreadgroup.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
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


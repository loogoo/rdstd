/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdFileutil.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��26��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_FILEUTIL_H_
#define _RD_FILEUTIL_H_

#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE

class RD_STD_DLL_ENTRY rdFileUtil 
{
public:
    /**
     * @brief close_r ȷ��close�������ж��źź����������
     *
     * @param fd �ļ�������
     */
    static int32_t close_r(int32_t fd);

};

END_RDSTD_NAMESPACE

#endif


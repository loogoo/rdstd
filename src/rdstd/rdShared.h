/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdShared.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_SHARED_H_
#define _RD_SHARED_H_

#include "rdMutex.h"
#include "rdMemsecC99.h"

BEGIN_RDSTD_NAMESPACE

/**
 * @brief �ṩ����ԭ��������ͨ�ü��������ܣ��ɱ��������ָ�������
 */
class RD_STD_DLL_ENTRY  rdShared {
public:
    /**
     * @brief ~rdShared ��������
     */
    virtual ~rdShared() { }

    /**
     * @brief inc �������ü���
     */
    void inc();

    /**
     * @brief dec �������ü���
     *
     * @return ���ü�����1���ֵ
     */
    int32_t dec();

    /**
     * @brief get_count ��ȡ��ǰ���ü���
     *
     * @return ��ǰ���ü���ֵ
     */
    int32_t get_count();

protected:
    /**
     * @brief Shareable ������ʽ���죬����ͨ�����๹��
     */
    rdShared();
private:
    int32_t _count;
    rdMutex _mutex;
private:
    /**
     * @brief Shareable ���ÿ������칦��
     */
    rdShared(const rdShared&);

    /**
     * @brief operator= ���ø�ֵ�����
     *
     * @param Shareable
     */
    rdShared& operator=(const rdShared&);
};

END_RDSTD_NAMESPACE

#endif


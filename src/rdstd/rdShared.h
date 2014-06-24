/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdShared.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
***************************************************************************/
#ifndef _RD_SHARED_H_
#define _RD_SHARED_H_

#include "rdMutex.h"
#include "rdMemsecC99.h"

BEGIN_RDSTD_NAMESPACE

/**
 * @brief 提供具有原子增减的通用计数器功能，可被多个智能指针对象共享
 */
class RD_STD_DLL_ENTRY  rdShared {
public:
    /**
     * @brief ~rdShared 析构函数
     */
    virtual ~rdShared() { }

    /**
     * @brief inc 增加引用计数
     */
    void inc();

    /**
     * @brief dec 减少引用计数
     *
     * @return 引用计数减1后的值
     */
    int32_t dec();

    /**
     * @brief get_count 获取当前引用计数
     *
     * @return 当前引用计数值
     */
    int32_t get_count();

protected:
    /**
     * @brief Shareable 禁用显式构造，仅可通过子类构造
     */
    rdShared();
private:
    int32_t _count;
    rdMutex _mutex;
private:
    /**
     * @brief Shareable 禁用拷贝构造功能
     */
    rdShared(const rdShared&);

    /**
     * @brief operator= 禁用赋值运算符
     *
     * @param Shareable
     */
    rdShared& operator=(const rdShared&);
};

END_RDSTD_NAMESPACE

#endif


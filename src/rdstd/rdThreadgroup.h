/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdThreadgroup.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#ifndef _RD_THREADGROUP_H_
#define _RD_THREADGROUP_H_

#include <vector>
#include "rdThread.h"
#include "rdSharedPtr.h"

BEGIN_RDSTD_NAMESPACE

/**
 * @class ThreadGroup
 * @brief ThreadGroup是Thread的集合，方便管理一组相关线程
 */
class RD_STD_DLL_ENTRY rdThreadGroup {
public:
    rdThreadGroup();
    ~rdThreadGroup();

    /**
     * @brief   添加新线程
     * @param   thread 待添加的新线程
     * @return  成功返回true
     */
	bool addThread(rdSharedPtr<rdThread> thread);

    /**
     * @brief   等待线程组中的所有线程执行结束
     * @param   
     * @return  成功返回true
     */
	bool join();

    /**
     * @brief   获取线程组中的线程个数
     * @param   
     * @return  线程组中的线程个数
     */
	size_t size();

    /**
     * @brief   终止线程组中的所有线程的执行
     * @param   
     * @return  成功返回true
     */
	bool terminateAll();
private:
    rdThreadGroup(const rdThreadGroup&);
    rdThreadGroup& operator=(const rdThreadGroup&);

	std::vector< rdSharedPtr<rdThread> > _threads;
    typedef std::vector< rdSharedPtr<rdThread> >::const_iterator citr_type;
};

END_RDSTD_NAMESPACE

#endif


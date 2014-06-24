/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdMutexEx.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
***************************************************************************/
#ifndef _RD_MUTEXEX_H_
#define _RD_MUTEXEX_H_

#include "rdstdtp.h"
#include "rdGuard.h"

BEGIN_RDSTD_NAMESPACE


class RD_STD_DLL_ENTRY rdMutexEx
{
#ifndef _WIN32
	friend class dbLocalEvent;
	friend class dbLocalSemaphore;
#endif

public:
	rdMutexEx();
	~rdMutexEx();


	/**
	 * @brief isInitialized 判定是否初始化
	 *
	 *
	 * @return bool
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时27分46秒
	 */
	bool isInitialized();



	/** 
	 * @brief lock  加锁操作
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时28分01秒
	 */
	int32_t lock() ;


	/**
	 * @brief unlock 解锁操作
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时28分23秒
	 */
	int32_t unlock();

protected:
	mutex_cs _mutex;
	bool	 _initialized;
};

typedef rdGuard<rdMutexEx> rdScopedMutex_cs;

END_RDSTD_NAMESPACE

#endif
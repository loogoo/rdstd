/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdMempool.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年7月8日
* 修改记录: 
***************************************************************************/
#ifndef _RD_MEMPOOL_H_
#define _RD_MEMPOOL_H_

#include <map>
#include <vector>
#include "rdMutex.h"

BEGIN_RDSTD_NAMESPACE

class rdMempool {
public:
	static rdMempool* get_instance();
	~rdMempool();

	void* get_mem_block(int32_t size);
	void put_mem_block(void* mem_block);

	int32_t get_size(int32_t size);
private:
	rdMempool();
	rdMempool& operator=(const rdMempool& );

private:
	int32_t adjust_size(int32_t size);
	void free_mem_block(int32_t size);
	std::map<int32_t, std::vector<void*> > _mem_blocks;

	mutable rdMutex _mutex;

}; // end of class rdMempool

END_RDSTD_NAMESPACE

#endif
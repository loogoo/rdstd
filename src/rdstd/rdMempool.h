/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdMempool.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��7��8��
* �޸ļ�¼: 
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
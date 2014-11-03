/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdrdMempool.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年7月8日
* 修改记录: 
***************************************************************************/
#include "rdMempool.h"

BEGIN_RDSTD_NAMESPACE

rdMempool* rdMempool::get_instance() {
	static rdMempool mp;
	return &mp;
}

rdMempool::rdMempool() {
	_mem_blocks.insert(std::make_pair(128, std::vector<void*>()));
	_mem_blocks.insert(std::make_pair(256, std::vector<void*>()));
	_mem_blocks.insert(std::make_pair(512, std::vector<void*>()));
	_mem_blocks.insert(std::make_pair(1024, std::vector<void*>()));
	_mem_blocks.insert(std::make_pair(2048, std::vector<void*>()));
	_mem_blocks.insert(std::make_pair(4096, std::vector<void*>()));
}

rdMempool::~rdMempool() {
	free_mem_block(128);
	free_mem_block(256);
	free_mem_block(512);
	free_mem_block(1024);
	free_mem_block(2048);
	free_mem_block(4096);
	_mem_blocks.clear();
}

void rdMempool::free_mem_block(int32_t size) {
	std::vector<void*>& v = _mem_blocks[size];
	std::vector<void*>::iterator itr;

	for (itr = v.begin(); itr != v.end(); ++itr) {
		void* buf = (char*)*itr - 4;
		free(buf);
	}
	v.clear();
}

void* rdMempool::get_mem_block(int32_t size) {
	void* ret = NULL;
	size = adjust_size(size);

	if (size <= 4096) {
		rdGuard<rdMutex> guard(&_mutex);
		std::vector<void*>& v = _mem_blocks[size];
		if (v.size() > 0) {
			ret = v.back();
			v.pop_back();
		}
	}

	if (NULL == ret) {
		ret = malloc(size + 4);
		if (NULL != ret) {
			int32_t* pi = (int32_t*)ret;
			*pi = size;
			ret = (char*)ret + 4;
		}
	}
	return ret;
}

void rdMempool::put_mem_block(void* mem_block) {
	if (NULL == mem_block) {
		return;
	}

	int32_t* pi = (int32_t*)((char*)mem_block - 4);
	if (*pi > 4096) {
		free(pi);
	}
	else {
		rdGuard<rdMutex> guard(&_mutex);
		_mem_blocks[*pi].push_back(mem_block);
	}
}

int32_t rdMempool::adjust_size(int32_t size) {
	if (size <= 128) {
		return 128;
	}
	else if (size <= 256) {
		return 256;
	}
	else if (size <= 512) {
		return 512;
	}
	else if (size <= 1024) {
		return 1024;
	}
	else if (size <= 2048){
		return 2048;
	}
	else if (size <= 4096){
		return 4096;
	}
	else {
		return size;
	}
}

int32_t rdMempool::get_size(int32_t size) {
	rdGuard<rdMutex> guard(&_mutex);
	return (int32_t)_mem_blocks[size].size();
}


END_RDSTD_NAMESPACE
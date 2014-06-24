/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdMemalloc.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月3日
* 修改记录: 
***************************************************************************/
#ifndef _RD_MEMALLOC_H_
#define _RD_MEMALLOC_H_

#include "rdstdtp.h"
#include "rdMemops.h"
#include <algorithm>
#include <vector>


BEGIN_RDSTD_NAMESPACE

template<typename T>
class rdMemsecAlloc
{
public:
	typedef T          value_type;

	typedef T*         pointer;
	typedef const T*   const_pointer;

	typedef T&         reference;
	typedef const T&   const_reference;

	typedef std::size_t     size_type;
	typedef std::ptrdiff_t  difference_type;

	rdMemsecAlloc() {}
	~rdMemsecAlloc() {}

	pointer address(reference x) const 
	{ return &x; }

	const_pointer address(const_reference x) const 
	{ return &x; }

	pointer allocate(size_type n, const void* = 0)
	{
		pointer p = new T[n];
		clear_mem(p, n);
		return p;
	}

	void deallocate(pointer p, size_type n)
	{
		clear_mem(p, n);

		delete [] p;
	}

	size_type max_size() const
	{
		return static_cast<size_type>(-1) / sizeof(T);
	}

	//template<typename U, typename... Args>
	//void construct(U* p, Args&&... args)
	//{
	//	::new(static_cast<void*>(p)) U(std::forward<Args>(args)...);
	//}

	template<typename U> void destroy(U* p) { p->~U(); }
};

template<typename T> inline bool
operator==(const rdMemsecAlloc<T>&, const rdMemsecAlloc<T>&) { return true; }

template<typename T> inline bool
operator!=(const rdMemsecAlloc<T>&, const rdMemsecAlloc<T>&) { return false; }

//template<typename T> using secure_vector = std::vector< T, secure_allocator<T> >;

//template<typename T>
//std::vector<T> unlock(const secure_vector<T>& in)
//{
//	std::vector<T> out(in.size());
//	copy_mem(&out[0], &in[0], in.size());
//	return out;
//}

END_RDSTD_NAMESPACE

#endif
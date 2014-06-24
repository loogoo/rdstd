/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdMemsecC99.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月3日
* 修改记录: 
***************************************************************************/
#ifndef _RD_MEMSECC99_H_
#define _RD_MEMSECC99_H_

#include "rdMemalloc.h"

BEGIN_RDSTD_NAMESPACE


/**
* This class represents variable length memory buffers.
*/
template<typename T>
class rdMemoryRegion
{
public:
	/**
	* Find out the size of the buffer, i.e. how many objects of type T it
	* contains.
	* @return the size of the buffer
	*/
	uint32_t size() const { return used; }

	/**
	* Find out whether this buffer is empty.
	* @return true if the buffer is empty, false otherwise
	*/
	bool is_empty() const { return (used == 0); }

	/**
	* Find out whether this buffer is non-empty
	* @return true if the buffer is non-empty, false otherwise
	*/
	bool has_items() const { return (used != 0); }

	/**
	* Get a pointer to the first element in the buffer.
	* @return a pointer to the first element in the buffer
	*/
	operator T* () { return buf; }

	/**
	* Get a constant pointer to the first element in the buffer.
	* @return a constant pointer to the first element in the buffer
	*/
	operator const T* () const { return buf; }

	/**
	* Get a pointer to the first element in the buffer.
	* @return a pointer to the first element in the buffer
	*/
	T* begin() { return buf; }

	/**
	* Get a constant pointer to the first element in the buffer.
	* @return a constant pointer to the first element in the buffer
	*/
	const T* begin() const { return buf; }

	/**
	* Get a pointer to the last element in the buffer.
	* @return a pointer to the last element in the buffer
	*/
	T* end() { return (buf + size()); }

	/**
	* Get a constant pointer to the last element in the buffer.
	* @return a constant pointer to the last element in the buffer
	*/
	const T* end() const { return (buf + size()); }

	/**
	* Check two buffers for equality.
	* @return true iff the content of both buffers is byte-wise equal
	*/
	bool operator==(const rdMemoryRegion<T>& other) const
	{
		return (size() == other.size() &&
			same_mem(buf, other.buf, size()));
	}

	/**
	* Compare two buffers lexicographically.
	* @return true if this buffer is lexicographically smaller than other.
	*/
	bool operator<(const rdMemoryRegion<T>& other) const;

	/**
	* Check two buffers for inequality.
	* @return false if the content of both buffers is byte-wise equal, true
	* otherwise.
	*/
	bool operator!=(const rdMemoryRegion<T>& in) const
	{ return (!(*this == in)); }

	/**
	* Copy the contents of another buffer into this buffer.
	* The former contents of *this are discarded.
	* @param in the buffer to copy the contents from.
	* @return a reference to *this
	*/
	rdMemoryRegion<T>& operator=(const rdMemoryRegion<T>& in)
	{ if(this != &in) set(in); return (*this); }

	/**
	* The use of this function is discouraged because of the risk of memory
	* errors. Use rdMemoryRegion<T>::set()
	* instead.
	* Copy the contents of an array of objects of type T into this buffer.
	* The former contents of *this are discarded.
	* The length of *this must be at least n, otherwise memory errors occur.
	* @param in the array to copy the contents from
	* @param n the length of in
	*/
	void copy(const T in[], uint32_t n)
	{ copy(0, in, n); }

	/**
	* The use of this function is discouraged because of the risk of memory
	* errors. Use rdMemoryRegion<T>::set()
	* instead.
	* Copy the contents of an array of objects of type T into this buffer.
	* The former contents of *this are discarded.
	* The length of *this must be at least n, otherwise memory errors occur.
	* @param off the offset position inside this buffer to start inserting
	* the copied bytes
	* @param in the array to copy the contents from
	* @param n the length of in
	*/
	void copy(uint32_t off, const T in[], uint32_t n)
	{ copy_mem(buf + off, in, (n > size() - off) ? (size() - off) : n); }

	/**
	* Set the contents of this according to the argument. The size of
	* *this is increased if necessary.
	* @param in the array of objects of type T to copy the contents from
	* @param n the size of array in
	*/
	void set(const T in[], uint32_t n)    { create(n); copy(in, n); }

	/**
	* Set the contents of this according to the argument. The size of
	* *this is increased if necessary.
	* @param in the buffer to copy the contents from
	*/
	void set(const rdMemoryRegion<T>& in) { set(in.begin(), in.size()); }

	/**
	* Append data to the end of this buffer.
	* @param data the array containing the data to append
	* @param n the size of the array data
	*/
	void append(const T data[], uint32_t n)
	{ grow_to(size()+n); copy(size() - n, data, n); }

	/**
	* Append a single element.
	* @param x the element to append
	*/
	void append(T x) { append(&x, 1); }

	/**
	* Append data to the end of this buffer.
	* @param data the buffer containing the data to append
	*/
	void append(const rdMemoryRegion<T>& x) { append(x.begin(), x.size()); }

	/**
	* Zeroise the bytes of this buffer. The length remains unchanged.
	*/
	void clear() { clear_mem(buf, allocated); }

	/**
	* Reset this buffer to an empty buffer with size zero.
	*/
	void destroy() { create(0); }

	/**
	* Reset this buffer to a buffer of specified length. The content will be
	* initialized to zero bytes.
	* @param n the new length of the buffer
	*/
	void create(uint32_t n);

	/**
	* Preallocate memory, so that this buffer can grow up to size n without
	* having to perform any actual memory allocations. (This is
	* the same principle as for std::vector::reserve().)
	*/
	void grow_to(uint32_t N);

	/**
	* Swap this buffer with another object.
	*/
	void swap(rdMemoryRegion<T>& other);

	~rdMemoryRegion() { deallocate(buf, allocated); }

protected:
	rdMemoryRegion() { buf = 0; alloc = 0; used = allocated = 0; }
	rdMemoryRegion(const rdMemoryRegion<T>& other)
	{
		buf = 0;
		used = allocated = 0;
		alloc = other.alloc;
		set(other.buf, other.used);
	}

	void init(bool locking, uint32_t length = 0)
	{ alloc = new rdMemsecAlloc<T>; create(length); }
private:
	T* allocate(uint32_t n)
	{
		return static_cast<T*>(alloc->allocate(sizeof(T)*n));
	}

	void deallocate(T* p, uint32_t n)
	{ alloc->deallocate(p, sizeof(T)*n); }

	T* buf;
	uint32_t used;
	uint32_t allocated;
	rdMemsecAlloc<T>* alloc;
};

/*
* Create a new buffer
*/
template<typename T>
void rdMemoryRegion<T>::create(uint32_t n)
{
	if(n <= allocated) { clear(); used = n; return; }
	deallocate(buf, allocated);
	buf = allocate(n);
	allocated = used = n;
}

/*
* Increase the size of the buffer
*/
template<typename T>
void rdMemoryRegion<T>::grow_to(uint32_t n)
{
	if(n > used && n <= allocated)
	{
		clear_mem(buf + used, n - used);
		used = n;
		return;
	}
	else if(n > allocated)
	{
		T* new_buf = allocate(n);
		copy_mem(new_buf, buf, used);
		deallocate(buf, allocated);
		buf = new_buf;
		allocated = used = n;
	}
}

/*
* Compare this buffer with another one
*/
template<typename T>
bool rdMemoryRegion<T>::operator<(const rdMemoryRegion<T>& in) const
{
	if(size() < in.size()) return true;
	if(size() > in.size()) return false;

	for(uint32_t j = 0; j != size(); j++)
	{
		if(buf[j] < in[j]) return true;
		if(buf[j] > in[j]) return false;
	}

	return false;
}

/*
* Swap this buffer with another one
*/
template<typename T>
void rdMemoryRegion<T>::swap(rdMemoryRegion<T>& x)
{
	std::swap(buf, x.buf);
	std::swap(used, x.used);
	std::swap(allocated, x.allocated);
	std::swap(alloc, x.alloc);
}




/**
* This class represents variable length buffers that do not
* make use of memory locking.
*/
template<typename T>
class rdMemoryVector : public rdMemoryRegion<T>
{
public:
	using rdMemoryRegion<T>::set;
	using rdMemoryRegion<T>::init;
	using rdMemoryRegion<T>::append;

	/**
	* Copy the contents of another buffer into this buffer.
	* @param in the buffer to copy the contents from
	* @return a reference to *this
	*/
	rdMemoryVector<T>& operator=(const rdMemoryRegion<T>& in)
	{ if(this != &in) set(in); return (*this); }

	/**
	* Create a buffer of the specified length.
	* @param n the length of the buffer to create.

	*/
	rdMemoryVector(uint32_t n = 0) { init(false, n); }

	/**
	* Create a buffer with the specified contents.
	* @param in the array containing the data to be initially copied
	* into the newly created buffer
	* @param n the size of the arry in
	*/
	rdMemoryVector(const T in[], uint32_t n)
	{ init(false); set(in, n); }

	/**
	* Copy constructor.
	*/
	rdMemoryVector(const rdMemoryRegion<T>& in)
	{ init(false); set(in); }

	/**
	* Create a buffer whose content is the concatenation of two other
	* buffers.
	* @param in1 the first part of the new contents
	* @param in2 the contents to be appended to in1
	*/
	rdMemoryVector(const rdMemoryRegion<T>& in1, const rdMemoryRegion<T>& in2)
	{ init(false); set(in1); append(in2); }
};




/**
* This class represents variable length buffers using the operating
* systems capability to lock memory, i.e. keeping it from being
* swapped out to disk. In this way, a security hole allowing attackers
* to find swapped out secret keys is closed. Please refer to
* Botan::InitializerOptions::secure_memory() for restrictions and
* further details.
*/
template<typename T>
class rdSecureVector : public rdMemoryRegion<T>
{
public:
	using rdMemoryRegion<T>::set;
	using rdMemoryRegion<T>::init;
	using rdMemoryRegion<T>::append;

	/**
	* Copy the contents of another buffer into this buffer.
	* @param in the buffer to copy the contents from
	* @return a reference to *this
	*/
	rdSecureVector<T>& operator=(const rdMemoryRegion<T>& in)
	{ if(this != &in) set(in); return (*this); }

	/**
	* Create a buffer of the specified length.
	* @param n the length of the buffer to create.

	*/
	rdSecureVector(uint32_t n = 0) { init(true, n); }

	/**
	* Create a buffer with the specified contents.
	* @param in the array containing the data to be initially copied
	* into the newly created buffer
	* @param n the size of the array in
	*/
	rdSecureVector(const T in[], uint32_t n)
	{ init(true); set(in, n); }

	/**
	* Create a buffer with contents specified contents.
	* @param in the buffer holding the contents that will be
	* copied into the newly created buffer.
	*/
	rdSecureVector(const rdMemoryRegion<T>& in)
	{ init(true); set(in); }

	/**
	* Create a buffer whose content is the concatenation of two other
	* buffers.
	* @param in1 the first part of the new contents
	* @param in2 the contents to be appended to in1
	*/
	rdSecureVector(const rdMemoryRegion<T>& in1, const rdMemoryRegion<T>& in2)
	{ init(true); set(in1); append(in2); }
};



/**
* This class represents fixed length buffers using the operating
* systems capability to lock memory, i.e. keeping it from being
* swapped out to disk. In this way, a security hole allowing attackers
* to find swapped out secret keys is closed. Please refer to
* Botan::InitializerOptions::secure_memory() for restrictions and
* further details.
*/
template<typename T, uint32_t L>
class rdSecureBuffer : public rdMemoryRegion<T>
{
public:
	using rdMemoryRegion<T>::set;
	using rdMemoryRegion<T>::init;

	/**
	* Copy the contents of another buffer into this buffer.
	* @param in the buffer to copy the contents from
	* @return a reference to *this
	*/
	rdSecureBuffer<T,L>& operator=(const rdSecureBuffer<T,L>& in)
	{ if(this != &in) set(in); return (*this); }

	/**
	* Create a buffer of the length L.
	*/
	rdSecureBuffer() { init(true, L); }

	/**
	* Create a buffer of size L with the specified contents.
	* @param in the array containing the data to be initially copied
	* into the newly created buffer
	* @param n the size of the array in
	*/
	rdSecureBuffer(const T in[], uint32_t n)
	{ init(true, L); this->copy(in, n); }
private:
	rdSecureBuffer<T, L>& operator=(const rdMemoryRegion<T>& in)
	{ if(this != &in) set(in); return (*this); }
};


END_RDSTD_NAMESPACE

#endif
/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdWebhdr.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月24日
* 修改记录: 
***************************************************************************/
#include "rdWebhdr.h"

ARR_WEB_DOI::ARR_WEB_DOI()
{
	__ptr = NULL;
	__size = 0;
	soap = NULL;
}

ARR_WEB_DOI::ARR_WEB_DOI(struct soap*, int n)
{
	__ptr = NULL;
	__size = 0;
	this->soap = soap;
	resize(n);
}

ARR_WEB_DOI::~ARR_WEB_DOI()
{
	resize(0);
}


int ARR_WEB_DOI::size()
{
	return __size;
}

void ARR_WEB_DOI::resize(int n)
{
	if (__ptr)
	{ 
		if (soap) // if created by soap environment
			soap_delete(soap, __ptr); // then delete
		else
			delete[] __ptr;
	}
	__size = n;
	if (n <= 0)
		__ptr = NULL;
	//else if (soap)
	//	__ptr = soap_new_ns__Data(soap, n);
	else
		__ptr = new WEB_DOI[n];
}

WEB_DOI& ARR_WEB_DOI::operator[](int i) const
{
	//assert(__ptr && i >= 0 && i < __size);
	return __ptr[i];
}

//////////////////////////////////////////////////////////////////////////
ARR_WEB_DOIVAL::ARR_WEB_DOIVAL()
{
	__ptr = NULL;
	__size = 0;
	soap = NULL;
}

ARR_WEB_DOIVAL::ARR_WEB_DOIVAL(struct soap*, int n)
{
	__ptr = NULL;
	__size = 0;
	this->soap = soap;
	resize(n);
}

ARR_WEB_DOIVAL::~ARR_WEB_DOIVAL()
{
	resize(0);
}


int ARR_WEB_DOIVAL::size()
{
	return __size;
}

void ARR_WEB_DOIVAL::resize(int n)
{
	if (__ptr)
	{ 
		if (soap) // if created by soap environment
			soap_delete(soap, __ptr); // then delete
		else
			delete[] __ptr;
	}
	__size = n;
	if (n <= 0)
		__ptr = NULL;
	//else if (soap)
	//	__ptr = soap_new_ns__Data(soap, n);
	else
		__ptr = new WEB_DOIVAL[n];
}

WEB_DOIVAL& ARR_WEB_DOIVAL::operator[](int i) const
{
	//assert(__ptr && i >= 0 && i < __size);
	return __ptr[i];
}

////////////////////////////////////////////////////////////////////////////////
//
//	Class vector Methods
//
////////////////////////////////////////////////////////////////////////////////

vector::vector()
{ __ptr = 0;
__size = 0;
}

vector::vector(int size)
{ __ptr = (int*)soap_malloc(soap, size*sizeof(int));
__size = size;
}

vector::~vector()
{ soap_unlink(soap, this); // not required, but just to make sure if someone calls delete on this
}

void vector::resize(int size)
{ int *p;
if (__size == size)
return;
p = (int*)soap_malloc(soap, size*sizeof(int));
if (__ptr)
{ for (int i = 0; i < (size <= __size ? size : __size); i++)
p[i] = __ptr[i];
soap_unlink(soap, __ptr);
free(__ptr);
}
__ptr = p;
__size = size;
}

int& vector::operator[](int idx) const
{ if (!__ptr || idx < 0 || idx >= __size)
fprintf(stderr, "Array index out of bounds\n");
return __ptr[idx];
}

////////////////////////////////////////////////////////////////////////////////
//
//	Class matrix Methods
//
////////////////////////////////////////////////////////////////////////////////

matrix::matrix()
{ __ptr = 0;
__size = 0;
}

matrix::~matrix()
{ soap_unlink(soap, this); // not required, but just to make sure if someone calls delete on this
}

matrix::matrix(int rows, int cols)
{ 
	__ptr = soap_new_vector(soap, rows);
	for (int i = 0; i < cols; i++)
		__ptr[i].resize(cols);
	__size = rows;
}

void matrix::resize(int rows, int cols)
{ int i;
vector *p;
if (__size != rows)
{ if (__ptr)
{ p = soap_new_vector(soap, rows);
for (i = 0; i < (rows <= __size ? rows : __size); i++)
{ if (this[i].__size != cols)
(*this)[i].resize(cols);
(p+i)->__ptr = __ptr[i].__ptr;
(p+i)->__size = cols;
}
for (; i < rows; i++)
__ptr[i].resize(cols);
}
else
{ 
	__ptr = soap_new_vector(soap, rows);
	for (i = 0; i < rows; i++)
		__ptr[i].resize(cols);
	__size = rows;
}
}
else
for (i = 0; i < __size; i++)
__ptr[i].resize(cols);
}

vector& matrix::operator[](int idx) const
{ if (!__ptr || idx < 0 || idx >= __size)
fprintf(stderr, "Array index out of bounds\n");
return __ptr[idx];
}

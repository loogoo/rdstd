/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdWebService.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月24日
* 修改记录: 
***************************************************************************/
#include "rdWebhdr.h"
#include "rdms.nsmap"
#include <stdio.h>

int ns__GetData(struct soap *soap, WEB_DOI doi, WEB_DOIVAL *pVal)
{
	return SOAP_OK;
}

int ns__GetDataN(struct soap *soap, ARR_WEB_DOI *doi, ARR_WEB_DOIVAL *pVal)
{
	int num = doi->size();
	pVal->resize(num);


	for (int i=0; i<num; i++)
	{

		pVal->__ptr[i].doi = doi->__ptr[i];
		pVal->__ptr[i].bValid = true;
		pVal->__ptr[i].dVal = 1.0*i;
		pVal->__ptr[i].val = i;
		pVal->__ptr[i].type = 1;
		pVal->__ptr[i].rvTime = time(NULL);

	}

	return SOAP_OK;
}

int ns__multi(struct soap *soap, int a, int b, int *c)
{
	*c = a * b;

	return SOAP_OK;
}


////////////////////////////////////////////////////////////////////////////////
//
//	Magic Square Algorithm
//
////////////////////////////////////////////////////////////////////////////////
int ns__magic(struct soap *soap, int n, matrix *square)
{ 
	int i, j, k, l, key = 2;
	if (n < 1)
		return soap_sender_fault(soap, "Negative or zero size", "<error xmlns=\"http://tempuri.org/\">The input parameter must be positive</error>");
	if (n > 100)
		return soap_sender_fault(soap, "size > 100", "<error xmlns=\"http://tempuri.org/\">The input parameter must not be too large</error>");
	square->resize(n, n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			(*square)[i][j] = 0;
	i = 0;
	j = (n-1)/2;
	(*square)[i][j] = 1;
	while (key <= n*n)
	{ 
		if (i-1 < 0)
			k = n-1;
		else
			k = i-1;
		if (j-1 < 0)
			l = n-1;
		else
			l = j-1;
		if ((*square)[k][l])
			i = (i+1) % n;
		else
		{ i = k;
		j = l;
		}
		(*square)[i][j] = key;
		key++;
	}
	Sleep(1);		// mimic work load latency
	return SOAP_OK;
}
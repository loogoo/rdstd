/* soapClient.cpp
   Generated by gSOAP 2.8.17r from rdms.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.17r 2014-11-29 07:08:30 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__GetData(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct WEB_DOI doi, struct WEB_DOIVAL *pVal)
{	struct ns__GetData soap_tmp_ns__GetData;
	struct ns__GetDataResponse *soap_tmp_ns__GetDataResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/rdms.cgi";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__GetData.doi = doi;
	soap_serializeheader(soap);
	soap_serialize_ns__GetData(soap, &soap_tmp_ns__GetData);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__GetData(soap, &soap_tmp_ns__GetData, "ns:GetData", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__GetData(soap, &soap_tmp_ns__GetData, "ns:GetData", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!pVal)
		return soap_closesock(soap);
	soap_default_WEB_DOIVAL(soap, pVal);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__GetDataResponse = soap_get_ns__GetDataResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__GetDataResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (pVal && soap_tmp_ns__GetDataResponse->pVal)
		*pVal = *soap_tmp_ns__GetDataResponse->pVal;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__GetDataN(struct soap *soap, const char *soap_endpoint, const char *soap_action, ARR_WEB_DOI *doi, ARR_WEB_DOIVAL *pVal)
{	struct ns__GetDataN soap_tmp_ns__GetDataN;
	struct ns__GetDataNResponse *soap_tmp_ns__GetDataNResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/rdms.cgi";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__GetDataN.doi = doi;
	soap_serializeheader(soap);
	soap_serialize_ns__GetDataN(soap, &soap_tmp_ns__GetDataN);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__GetDataN(soap, &soap_tmp_ns__GetDataN, "ns:GetDataN", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__GetDataN(soap, &soap_tmp_ns__GetDataN, "ns:GetDataN", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!pVal)
		return soap_closesock(soap);
	pVal->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__GetDataNResponse = soap_get_ns__GetDataNResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__GetDataNResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (pVal && soap_tmp_ns__GetDataNResponse->pVal)
		*pVal = *soap_tmp_ns__GetDataNResponse->pVal;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__multi(struct soap *soap, const char *soap_endpoint, const char *soap_action, int a, int b, int *c)
{	struct ns__multi soap_tmp_ns__multi;
	struct ns__multiResponse *soap_tmp_ns__multiResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/rdms.cgi";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__multi.a = a;
	soap_tmp_ns__multi.b = b;
	soap_serializeheader(soap);
	soap_serialize_ns__multi(soap, &soap_tmp_ns__multi);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__multi(soap, &soap_tmp_ns__multi, "ns:multi", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__multi(soap, &soap_tmp_ns__multi, "ns:multi", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!c)
		return soap_closesock(soap);
	soap_default_int(soap, c);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__multiResponse = soap_get_ns__multiResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__multiResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (c && soap_tmp_ns__multiResponse->c)
		*c = *soap_tmp_ns__multiResponse->c;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__magic(struct soap *soap, const char *soap_endpoint, const char *soap_action, int rank, matrix *result)
{	struct ns__magic soap_tmp_ns__magic;
	struct ns__magicResponse *soap_tmp_ns__magicResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/rdms.cgi";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__magic.rank = rank;
	soap_serializeheader(soap);
	soap_serialize_ns__magic(soap, &soap_tmp_ns__magic);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__magic(soap, &soap_tmp_ns__magic, "ns:magic", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__magic(soap, &soap_tmp_ns__magic, "ns:magic", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	result->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__magicResponse = soap_get_ns__magicResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__magicResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__magicResponse->result)
		*result = *soap_tmp_ns__magicResponse->result;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */

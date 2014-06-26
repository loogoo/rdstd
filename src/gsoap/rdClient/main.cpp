#include "rdwebhdr.h"
#include <iostream>


void callMagic(struct soap *soap, const char *server)
{
	matrix *A = soap_new_matrix(soap, -1);

	printf("Content-type: text/html\r\n\r\n<html><h1>Magic Square of Rank %d</h1><pre>\n", 5);
	if (soap_call_ns__magic(soap, server, NULL, 5, A))
	{ 
		soap_print_fault(soap, stderr);
		soap_print_fault_location(soap, stderr);
	}
	else
	{ 
		for (int i = 0; i < A->__size; i++)
		{ 
			for (int j = 0; j < (*A)[i].__size; j++)
				printf("%4d", (*A)[i][j]);
			printf("\n");
		}
	}
	printf("</pre></html>\n");

	soap_delete_matrix(soap, A);
}

int main()
{
	struct soap *soap = soap_new();
	soap_init(soap);
	//soap_init2(soap, SOAP_IO_KEEPALIVE, SOAP_IO_KEEPALIVE | SOAP_XML_TREE | SOAP_XML_INDENT); 

	const char *server = "http://localhost:8008";


	soap->encodingStyle = NULL;					// to remove SOAP 1.1/1.2 encodingStyle
	soap_mode(soap, SOAP_XML_TREE);				// XML without id-ref (no cycles!)
	//soap_mode(soap, SOAP_XML_GRAPH);			// XML with id-ref (including cycles)
	soap_set_namespaces(soap, namespaces);		//to set xmlns bindings 


	ARR_WEB_DOI arrdoi;
	arrdoi.resize(10);
	for (int j=0; j<10; j++)
	{
		arrdoi.__ptr[j].nStatID = j;
		arrdoi.__ptr[j].nDevID = j;
		arrdoi.__ptr[j].dCode = 201+j;
	}
	
	soap_write_ARR_WEB_DOI(soap, &arrdoi);


	//soap->sendfd = open("c:/a.txt", O_RDWR | O_CREAT | O_APPEND);
	//soap_write_ARR_WEB_DOI(soap, &arrdoi); 


	ARR_WEB_DOIVAL arrDVal;
	soap_call_ns__GetDataN(soap, server, NULL, &arrdoi, &arrDVal);
	//////////////////////////////////////////////////////////////////////////
	int m = 0;
	int t = soap_call_ns__multi(soap, server, "", 1, 2, &m);

	t = soap_call_ns__multi(soap, server, "", 1, 2, &m);
	t = soap_call_ns__multi(soap, server, "", 1, 2, &m);
	t = soap_call_ns__multi(soap, server, "", 1, 2, &m);


	callMagic(soap, server);

	
	soap_destroy(soap);
	soap_end(soap);
	soap_done(soap);
	soap_del(soap);

	return 0;
}


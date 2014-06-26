/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 ��������ʵ�����¼����ɷ����޹�˾ ��Ȩ����
* �ļ�����: rdWebApp.cpp 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��6��14��
* �޸ļ�¼: 
***************************************************************************/
#include "rdWebApp.h"

static int http_get(struct soap *soap)
{
	FILE *fd = NULL;
	char *s = strchr(soap->path, '?'); 
	if (s != NULL && strcmp(s, "?5") == 0){
		matrix *square = soap_new_matrix(soap, 1);

		if (ns__magic(soap, 5, square) == SOAP_OK){
			soap_write_matrix(soap, square);

			soap->http_content = "text/xml";
			soap_response(soap, SOAP_FILE);
			soap_send(soap, soap->tmpbuf);
			soap_end_send(soap); 
		}
		soap_delete_matrix(soap, square);
	}
	else if (s != NULL && strcmp(s, "?10") == 0){
		matrix *square = soap_new_matrix(soap, 1);

		if (ns__magic(soap, 10, square) == SOAP_OK){
			soap_write_matrix(soap, square);

			soap->http_content = "text/xml";
			soap_response(soap, SOAP_FILE);
			soap_send(soap, soap->tmpbuf);
			soap_end_send(soap); 
		}
		soap_delete_matrix(soap, square);
	}
	else if (s != NULL && strcmp(s, "?wsdl") == 0){
		fd = fopen("rdms.wsdl", "rb"); // open WSDL file to copy 
		if (!fd) 
			return 404; // return HTTP not found error 
		soap->http_content = "text/xml"; // HTTP header with text/xml content 
		soap_response(soap, SOAP_FILE); 
		for (;;) 
		{ 
			size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd); 
			if (!r) 
				break; 
			if (soap_send_raw(soap, soap->tmpbuf, r)) 
				break; // can't send, but little we can do about that 
		} 
		fclose(fd); 
		soap_end_send(soap); 
	}
	else
	{
		//soap_response(soap, SOAP_HTML);
		//soap_send(soap, " <HTML> My Web sevice is operational </HTML> ");
		//soap_end_send(soap);
		//return SOAP_OK;
		return SOAP_GET_METHOD; 
	}

	return SOAP_OK; 
} 



rdWebApp::rdWebApp()
{
	m_head = 0;
	m_tail = 0;

	m_event.open();
}


rdWebApp::~rdWebApp()
{
	Exit();
}


int rdWebApp::Enqueue(SOAP_SOCKET sock)
{
	int status = SOAP_OK;
	
	m_mutex.lock();

	int next = m_tail +1;
	if (next >= MAX_QUEUE)
		next = 0;
	if (next == m_head)
		status = SOAP_EOM;
	else
	{
		m_queue[m_tail] =sock;
		m_tail = next;
	}

	m_event.signal();

	m_mutex.unlock();
	return status;
}


SOAP_SOCKET rdWebApp::Dequeue()
{
	SOAP_SOCKET sock;
	m_mutex.lock();
	while (m_head == m_tail )
	{
		m_event.wait(m_mutex);
	}
	sock = m_queue[m_head++];
	if (m_head >= MAX_QUEUE)
	{
		m_head =0;
	}
	m_mutex.unlock();
	return sock;
}


/**************************************************************************
<PRE>
����     : Run ����Web service����
����     : 
����ֵ   : bool
����     : liy
---------------------------------------------------------------------------
�޸ļ�¼ :
�� ��            �汾     �޸���              �޸�����
2014/06/25  	 1.0      liy				  �½�
**************************************************************************/
bool rdWebApp::Run()
{
	m_run.create((rdstd::dbThread::thread_proc_t)Start, this);

	return true;
}


/**************************************************************************
<PRE>
����     : �˳� web service ����
����     : 
����ֵ   : bool
����     : liy
---------------------------------------------------------------------------
�޸ļ�¼ :
�� ��            �汾     �޸���              �޸�����
2014/06/25  	 1.0      liy				  �½�
**************************************************************************/
bool rdWebApp::Exit()
{
	int i = 0;
	for(i = 0; i < MAX_THR; i++)
	{
		while (Enqueue(SOAP_INVALID_SOCKET) == SOAP_EOM) 
		{
			Sleep(100);
		}
		Sleep(10);
	}
	
	m_run.join();

	//��������ʱ�Ļ���
	soap_done(&_ServerSoap);

	Sleep(1000);
	return true;
}


/**************************************************************************
<PRE>
����     : Start web servce start thread
����     : void* arg
����ֵ   : void
����     : liy
---------------------------------------------------------------------------
�޸ļ�¼ :
�� ��            �汾     �޸���              �޸�����
2014/06/25  	 1.0      liy				  �½�
**************************************************************************/
void thread_proc rdWebApp::Start(void* arg)
{
	rdWebApp *webSev = (rdWebApp *)arg;
	struct soap * tsoap = webSev->GetSoap();


	//soap_init(tsoap);
	soap_init2(tsoap, SOAP_IO_KEEPALIVE, SOAP_IO_KEEPALIVE | SOAP_XML_TREE | SOAP_XML_INDENT); 

	tsoap->encodingStyle = NULL;				// to remove SOAP 1.1/1.2 encodingStyle
	soap_mode(tsoap, SOAP_XML_TREE);			// XML without id-ref (no cycles!)
	//soap_mode(soap, SOAP_XML_GRAPH);			// XML with id-ref (including cycles)
	soap_set_namespaces(tsoap, namespaces);		//to set xmlns bindings 


	tsoap->fget = http_get; 

	int i = 0;

	// �󶨷���˿�
	SOAP_SOCKET m = soap_bind(tsoap, NULL, 8008,BACKLOG);
	// ѭ��ֱ�������׽��ֺϷ�
	while (!soap_valid_socket(m))
	{
		fprintf(stderr,"Bind port error! ");
		m = soap_bind(tsoap, NULL, 8008,BACKLOG);
		rdstd::dbThread::sleep(1);
	}
	fprintf(stderr,"socket connection successful %d .\n",m);

	// ���ɷ����߳�
	for(i = 0; i <MAX_THR; i++)
	{
		webSev->m_process[i].create((rdstd::dbThread::thread_proc_t)Process, webSev);
		//if (runThread == NULL)	{
		//	fprintf(stderr,"Starting web service process thread %02d error.\n", i);
		//}
		fprintf(stderr,"Starting web service process %d success.\n", i);
	}

	// �������շ����߳�
	if (1){
		webSev->m_accept.create((rdstd::dbThread::thread_proc_t)Accept, webSev);
		fprintf(stderr,"Starting accept thread success.\n");
	}


	for (i=0; i<MAX_THR; i++)
	{
		webSev->m_process[i].join();

		fprintf(stderr,"thread %d to terminated. \n",i);
	}
}


/**************************************************************************
<PRE>
����     : Process web�������߳�
����     : void* arg
����ֵ   : void
����     : liy
---------------------------------------------------------------------------
�޸ļ�¼ :
�� ��            �汾     �޸���              �޸�����
2014/06/25  	 1.0      liy				  �½�
**************************************************************************/
void thread_proc rdWebApp::Process(void* arg)
{
	rdWebApp *webSev = (rdWebApp *)arg;
	struct soap * tsoap = soap_copy(webSev->GetSoap());

	while(true)
	{
		tsoap->socket = webSev->Dequeue();
		if (!soap_valid_socket(tsoap->socket))
		{
			break;
		}

		soap_serve(tsoap);
		soap_destroy(tsoap);
		soap_end(tsoap);
	}

	soap_done(tsoap);
	free(tsoap);
	return;
}


/**************************************************************************
<PRE>
����     : Accept web service�����߳�
����     : void* arg
����ֵ   : void
����     : liy
---------------------------------------------------------------------------
�޸ļ�¼ :
�� ��            �汾     �޸���              �޸�����
2014/06/25  	 1.0      liy				  �½�
**************************************************************************/
void thread_proc rdWebApp::Accept(void* arg)
{
	
	rdWebApp *webSev = (rdWebApp *)arg;
	struct soap * serverSoap = webSev->GetSoap();

	while(true)
	{
		// ���ܿͻ��˵�����
		SOAP_SOCKET s = soap_accept(serverSoap);

		if (!soap_valid_socket(s))
		{
			if (serverSoap->errnum)
			{
				soap_print_fault(serverSoap,stderr);
				continue;
			}else
			{
				fprintf(stderr,"Server timed out ");
				break;
			}
		}
		// �ͻ��˵�IP��ַ
		fprintf(stderr,"Accepted connection from IP= %d.%d.%d.%d socket = %d \n",
			((serverSoap->ip)>>24)&&0xFF,
			((serverSoap->ip)>>16)&0xFF,
			((serverSoap->ip)>>8)&0xFF,
			(serverSoap->ip)&0xFF,
			(serverSoap->socket));

		// ������׽��ֽ�����У��������������ѭ���ȴ�
		while(webSev->Enqueue(s) == SOAP_EOM)
			Sleep(500);
	}
}
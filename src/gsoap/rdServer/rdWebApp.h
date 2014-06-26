/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdWebApp.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��6��24��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_WEBAPP_H_
#define _RD_WEBAPP_H_

#include "rdWebhdr.h"

#include <rdMutexEx.h>
#include <rdEvent.h>
#include <rdEventLocal.h>
#include <rdThreadEx.h>

///����ȫ�ֱ����Ķ���
#define  BACKLOG (100) 
#define  MAX_THR (10)  
#define  MAX_QUEUE (1000)



class rdWebApp
{
public:
	rdWebApp();
	~rdWebApp();

	struct soap* GetSoap() { return &_ServerSoap;}
	
	int Enqueue(SOAP_SOCKET sock);			// ��Ӳ���
	SOAP_SOCKET Dequeue();					// ���Ӳ���

	bool Run();


protected:
	bool Exit();

	/**
	 * @brief Start ���������߳�
	 *
	 * @param void * arg
	 *
	 * @return void thread_proc
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��6��25�� 11ʱ19��28��
	 */
	static void thread_proc Start(void* arg);


	/**
	 * @brief Process web service process function
	 *
	 * @param void * arg
	 *
	 * @return void thread_proc
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��6��24�� 22ʱ44��04��
	 */
	static void thread_proc Process(void* arg);


	/**
	 * @brief Accept web service accept client function
	 *
	 * @param void * arg
	 *
	 * @return void thread_proc
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��6��24�� 22ʱ44��37��
	 */
	static void thread_proc Accept(void* arg);


protected:
	struct soap _ServerSoap;

	rdstd::rdMutex		m_mutex;				// ������
	rdstd::rdEventLocal	m_event;				// �¼�
	SOAP_SOCKET			m_queue[MAX_QUEUE];		// �������
	int					m_head;					// ����ͷ
	int					m_tail;					// ����β


	rdstd::dbThread		m_run;					// web service start thread
	rdstd::dbThread		m_accept;				// web service accept thread
	rdstd::dbThread		m_process[MAX_THR];		// web service process thread
};

#endif
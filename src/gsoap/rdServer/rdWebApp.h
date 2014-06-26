/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdWebApp.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年6月24日
* 修改记录: 
***************************************************************************/
#ifndef _RD_WEBAPP_H_
#define _RD_WEBAPP_H_

#include "rdWebhdr.h"

#include <rdMutexEx.h>
#include <rdEvent.h>
#include <rdEventLocal.h>
#include <rdThreadEx.h>

///宏与全局变量的定义
#define  BACKLOG (100) 
#define  MAX_THR (10)  
#define  MAX_QUEUE (1000)



class rdWebApp
{
public:
	rdWebApp();
	~rdWebApp();

	struct soap* GetSoap() { return &_ServerSoap;}
	
	int Enqueue(SOAP_SOCKET sock);			// 入队操作
	SOAP_SOCKET Dequeue();					// 出队操作

	bool Run();


protected:
	bool Exit();

	/**
	 * @brief Start 启动服务线程
	 *
	 * @param void * arg
	 *
	 * @return void thread_proc
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年6月25日 11时19分28秒
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
	 * @date   2014年6月24日 22时44分04秒
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
	 * @date   2014年6月24日 22时44分37秒
	 */
	static void thread_proc Accept(void* arg);


protected:
	struct soap _ServerSoap;

	rdstd::rdMutex		m_mutex;				// 队列锁
	rdstd::rdEventLocal	m_event;				// 事件
	SOAP_SOCKET			m_queue[MAX_QUEUE];		// 数组队列
	int					m_head;					// 队列头
	int					m_tail;					// 队列尾


	rdstd::dbThread		m_run;					// web service start thread
	rdstd::dbThread		m_accept;				// web service accept thread
	rdstd::dbThread		m_process[MAX_THR];		// web service process thread
};

#endif
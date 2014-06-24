/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdEvent.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
		lpEventAttributes��
����		[����]һ��ָ��SECURITY_ATTRIBUTES�ṹ��ָ�룬ȷ�����صľ���Ƿ�ɱ��ӽ��̼̳С�
				���lpEventAttributes��NULL���˾�����ܱ��̳С�
  ����			Windows NT/2000��lpEventAttributes�Ľṹ�еĳ�ԱΪ�µ��¼�ָ����һ����ȫ����
				���lpEventAttributes��NULL���¼������һ��Ĭ�ϵİ�ȫ����
		bManualReset��
			[����]ָ�����¼����󴴽����ֶ���ԭ�����Զ���ԭ�������TRUE����ô������ResetEvent
				�������ֹ����¼���״̬��ԭ�����ź�״̬���������ΪFALSE�����¼���һ���ȴ���
				���ͷ��Ժ�ϵͳ�����Զ����¼�״̬��ԭΪ���ź�״̬��
		bInitialState��
			[����]ָ���¼�����ĳ�ʼ״̬�����ΪTRUE����ʼ״̬Ϊ���ź�״̬������Ϊ���ź�״̬��
		lpName��
			[����]ָ���¼��Ķ�������ƣ���һ����0�������ַ���ָ�롣���Ƶ��ַ���ʽ�޶���
				MAX_PATH֮�ڡ������ǶԴ�Сд���еġ����lpNameָ�������֣���һ�����ڵ�������
				�¼������������ͬ������������EVENT_ALL_ACCESS�����ʴ��ڵĶ�����ʱ������
				bManualReset��bInitialState�����Ѿ��ڴ����¼��Ľ��������ã�����������������
				�ԡ�
					���lpEventAttributes�ǲ�������NULL������ȷ���˾���Ƿ���Ա��̳У�����
				�䰲ȫ��������Ա�������ԡ����lpNameΪNULL��������һ���������¼�����
					���lpName�ĺ�һ�����ڵ��źš����⡢�ȴ���ʱ������ҵ�������ļ�ӳ�����������ͬ
				����������ʧ�ܣ���GetLastError�����н�����ERROR_INVALID_HANDLE�����������
				���ԭ������Щ������ͬһ�������ռ䡣
					�ն˷���(Terminal Services)�������п��Լ���"Global\"����"Local\"��ǰ׺����
				��������ȷ�Ľ����󴴽���ȫ�ֵĻ�����������ռ䡣���Ƶ��������ֳ��˷�б��(\)
				������ʹ�������ַ�����ϸ���ݿɲο�Kernel Object Name Spaces��
					Windows 2000����Windows 2000ϵͳ�У�û���ն˷������У�"Global\"��"Local\"ǰ
				׺�������ԡ����Ƶ��������ֳ��˷�б��(\)������ʹ�������ַ���

			����������óɹ������������¼�����ľ����������������Ķ����ں�������ǰ�Ѿ�������
		�����������ش��ڵ��¼�����ľ����������GetLastError�����з���ERROR_ALREADY_EXISTS�����
		����ʧ�ܣ���������ֵΪNULL�������Ҫ�����ϸ�Ĵ�����Ϣ����Ҫ����GetLastError��

		��ע��
����		����CreateEvent�������صľ�����þ������EVENT_ALL_ACCESSȨ��ȥ�����µ��¼�����
		ͬʱ���������κ��д��¼��������ĺ�����ʹ�á�
����		�ڵ��õĹ����У������̶߳�������һ���ȴ�������ָ���¼�����������ָ���Ķ����
		״̬����Ϊ���ź�״̬ʱ��������ȴ����������ء�
����		���ڶ����ȴ�����������ָ��Ϊ���������ָ���Ķ�����Ϊ���ź�״̬�����ȴ�����
		����ʱ���ȴ��߳̽����ͷ�ȥ�������С�
����		��ʼ״̬��bInitialState�����н������á�ʹ��SetEvent�������¼������״̬��Ϊ����
		��״̬��ʹ��ResetEvent�������¼������״̬��Ϊ���ź�״̬��
����		��һ���ֶ���ԭ���¼������״̬����Ϊ���ź�״̬ʱ���ö���״̬��һֱ�������ź�״
		̬��ֱ����ȷ����ResetEvent����������Ϊ�޷���״̬��
����		���¼��Ķ�����Ϊ���ź�״̬ʱ�����������ĵȴ����̣߳��Լ����ʼ�ȴ����߳̾�
		�ᱻ�ͷš�
����		��һ���Զ���ԭ���¼������״̬����Ϊ���ź�״̬ʱ���ö���״̬��һֱ�������ź�״
		̬��ֱ��һ���ȴ��̱߳��ͷ�;ϵͳ���Զ����˺�����Ϊ�޷���״̬�����û�еȴ��߳�����
		�ȴ����¼������״̬���������ź�״̬��
����		������̿ɳ���ͬһ���¼�����Ķ�����������ͨ��ʹ�ô˶�����ʵ�ֽ��̼��ͬ����
		 ����Ķ���������ǿ��еģ�
����		����CreateEvent�����У�lpEventAttributes����ָ������ɱ��̳�ʱ��ͨ��CreateProcess
			  �����������ӽ��̼̳е��¼���������
����		��һ�����̿�����DuplicateHandle������ָ���¼����������Ӷ����һ�����Ƶľ����
			  �˾�����Ա���������ʹ�á�
����		��һ�����̿�����OpenEvent��CreateEvent������ָ��һ�����֣��Ӷ����һ����������
			  ����������
����		ʹ��CloseHandle�����رվ����������ֹͣʱ��ϵͳ���Զ��رվ���������һ�������
		�رպ��¼����󽫱����١�


		һ��Event�������Ժ�,������OpenEvent()API���������Handle,��CloseHandle()���ر���,
		��SetEvent()��PulseEvent()��������ʹ�����ź�,��ResetEvent()��ʹ�����ź�,��WaitForSingleObject()
		��WaitForMultipleObjects()���ȴ����Ϊ���ź�.
			 PulseEvent()��һ���Ƚ�����˼��ʹ�÷���,�������API������,��ʹһ��Event�����״̬
		����һ������仯,�����źű�����ź��ٱ�����ź�,������������ԭ�ӵ�.���Զ���λ��Event
		����,�����ͷŵ�һ���ȵ����¼���thread�������),�������˹���λ��Event����,���ͷ����е�
		����thread. 

		���� WaitForSingleObject�������غ��Ƿ��¼���������Ϊ���ź�״̬�����Ǳ���Ϊ���ź�״̬ 
		bManualReset 
		[in] Boolean that specifies whether a manual-reset or auto-reset event object is created. 
		If TRUE, then you must use the ResetEvent function to manually reset the state to nonsignaled. 
		If FALSE, the system automatically resets the state to nonsignaled after a single waiting 
		thread has been released. 

* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_EVENT_H
#define _RD_EVENT_H

#include "rdstdtp.h"


BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32
class RD_STD_DLL_ENTRY rdEvent
{
public:
	rdEvent();
	~rdEvent();

	/**
	 * @brief wait �ȴ��¼�����
	 *
	 * @param unsigned msec
	 *
	 * @return bool
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 21ʱ42��19��
	 */
	bool wait(unsigned msec = INFINITE);


	/**
	 * @brief signal �����¼���Ч
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 21ʱ42��35��
	 */
	void signal();

	/**
	 * @brief reset �����¼�
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 21ʱ42��50��
	 */
	void reset();


	/**
	 * @brief open ���¼�
	 *
	 * @param char_t const * name
	 * @param bool signaled
	 *
	 * @return bool
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 21ʱ43��00��
	 */
	bool open(char_t const* name, bool signaled = false, bool manual = false);


	/**
	 * @brief close �ر��¼�
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 21ʱ43��14��
	 */
	void close();


	void erase();
	
protected:
	HANDLE e;
};

#else

#include "rdSemaphore.h"

class RD_STD_DLL_ENTRY rdEvent : public rdSemaphore { 
public:
	rdEvent(const char *name=0, unsigned initValue = 0);
	~rdEvent()
	bool wait(unsigned msec);
	void signal();
	void reset();
	bool open(char const* name, bool signaled = false, bool manual = true);
};

#endif

END_RDSTD_NAMESPACE

#endif
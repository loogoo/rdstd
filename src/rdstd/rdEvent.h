/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdEvent.h 
* 当前版本: 1.0
* 摘  要:
		lpEventAttributes：
　　		[输入]一个指向SECURITY_ATTRIBUTES结构的指针，确定返回的句柄是否可被子进程继承。
				如果lpEventAttributes是NULL，此句柄不能被继承。
  　　			Windows NT/2000：lpEventAttributes的结构中的成员为新的事件指定了一个安全符。
				如果lpEventAttributes是NULL，事件将获得一个默认的安全符。
		bManualReset：
			[输入]指定将事件对象创建成手动复原还是自动复原。如果是TRUE，那么必须用ResetEvent
				函数来手工将事件的状态复原到无信号状态。如果设置为FALSE，当事件被一个等待线
				程释放以后，系统将会自动将事件状态复原为无信号状态。
		bInitialState：
			[输入]指定事件对象的初始状态。如果为TRUE，初始状态为有信号状态；否则为无信号状态。
		lpName：
			[输入]指定事件的对象的名称，是一个以0结束的字符串指针。名称的字符格式限定在
				MAX_PATH之内。名字是对大小写敏感的。如果lpName指定的名字，与一个存在的命名的
				事件对象的名称相同，函数将请求EVENT_ALL_ACCESS来访问存在的对象。这时候，由于
				bManualReset和bInitialState参数已经在创建事件的进程中设置，这两个参数将被忽
				略。
					如果lpEventAttributes是参数不是NULL，它将确定此句柄是否可以被继承，但是
				其安全描述符成员将被忽略。如果lpName为NULL，将创建一个无名的事件对象。
					如果lpName的和一个存在的信号、互斥、等待计时器、作业或者是文件映射对象名称相同
				，函数将会失败，在GetLastError函数中将返回ERROR_INVALID_HANDLE。造成这种现
				象的原因是这些对象共享同一个命名空间。
					终端服务(Terminal Services)：名称中可以加入"Global\"或是"Local\"的前缀，这
				样可以明确的将对象创建在全局的或事务的命名空间。名称的其它部分除了反斜杠(\)
				，可以使用任意字符。详细内容可参考Kernel Object Name Spaces。
					Windows 2000：在Windows 2000系统中，没有终端服务运行，"Global\"和"Local\"前
				缀将被忽略。名称的其它部分除了反斜杠(\)，可以使用任意字符。

			如果函数调用成功，函数返回事件对象的句柄。如果对于命名的对象，在函数调用前已经被创建
		，函数将返回存在的事件对象的句柄，而且在GetLastError函数中返回ERROR_ALREADY_EXISTS。如果
		函数失败，函数返回值为NULL，如果需要获得详细的错误信息，需要调用GetLastError。

		备注：
　　		调用CreateEvent函数返回的句柄，该句柄具有EVENT_ALL_ACCESS权限去访问新的事件对象，
		同时它可以在任何有此事件对象句柄的函数中使用。
　　		在调用的过程中，所有线程都可以在一个等待函数中指定事件对象句柄。当指定的对象的
		状态被置为有信号状态时，单对象等待函数将返回。
　　		对于多对象等待函数，可以指定为任意或所有指定的对象被置为有信号状态。当等待函数
		返回时，等待线程将被释放去继续运行。
　　		初始状态在bInitialState参数中进行设置。使用SetEvent函数将事件对象的状态置为有信
		号状态。使用ResetEvent函数将事件对象的状态置为无信号状态。
　　		当一个手动复原的事件对象的状态被置为有信号状态时，该对象状态将一直保持有信号状
		态，直至明确调用ResetEvent函数将其置为无符号状态。
　　		当事件的对象被置为有信号状态时，任意数量的等待中线程，以及随后开始等待的线程均
		会被释放。
　　		当一个自动复原的事件对象的状态被置为有信号状态时，该对象状态将一直保持有信号状
		态，直至一个等待线程被释放;系统将自动将此函数置为无符号状态。如果没有等待线程正在
		等待，事件对象的状态将保持有信号状态。
　　		多个进程可持有同一个事件对象的多个句柄，可以通过使用此对象来实现进程间的同步。
		 下面的对象共享机制是可行的：
　　		·在CreateEvent函数中，lpEventAttributes参数指定句柄可被继承时，通过CreateProcess
			  函数创建的子进程继承的事件对象句柄。
　　		·一个进程可以在DuplicateHandle函数中指定事件对象句柄，从而获得一个复制的句柄，
			  此句柄可以被其它进程使用。
　　		·一个进程可以在OpenEvent或CreateEvent函数中指定一个名字，从而获得一个有名的事
			  件对象句柄。
　　		使用CloseHandle函数关闭句柄。当进程停止时，系统将自动关闭句柄。当最后一个句柄被
		关闭后，事件对象将被销毁。


		一个Event被创建以后,可以用OpenEvent()API来获得它的Handle,用CloseHandle()来关闭它,
		用SetEvent()或PulseEvent()来设置它使其有信号,用ResetEvent()来使其无信号,用WaitForSingleObject()
		或WaitForMultipleObjects()来等待其变为有信号.
			 PulseEvent()是一个比较有意思的使用方法,正如这个API的名字,它使一个Event对象的状态
		发生一次脉冲变化,从无信号变成有信号再变成无信号,而整个操作是原子的.对自动复位的Event
		对象,它仅释放第一个等到该事件的thread（如果有),而对于人工复位的Event对象,它释放所有等
		待的thread. 

		请问 WaitForSingleObject函数返回后是否将事件对象重置为无信号状态，还是保持为有信号状态 
		bManualReset 
		[in] Boolean that specifies whether a manual-reset or auto-reset event object is created. 
		If TRUE, then you must use the ResetEvent function to manually reset the state to nonsignaled. 
		If FALSE, the system automatically resets the state to nonsignaled after a single waiting 
		thread has been released. 

* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
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
	 * @brief wait 等待事件发生
	 *
	 * @param unsigned msec
	 *
	 * @return bool
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 21时42分19秒
	 */
	bool wait(unsigned msec = INFINITE);


	/**
	 * @brief signal 触发事件有效
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 21时42分35秒
	 */
	void signal();

	/**
	 * @brief reset 重置事件
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 21时42分50秒
	 */
	void reset();


	/**
	 * @brief open 打开事件
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
	 * @date   2014年5月23日 21时43分00秒
	 */
	bool open(char_t const* name, bool signaled = false, bool manual = false);


	/**
	 * @brief close 关闭事件
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 21时43分14秒
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
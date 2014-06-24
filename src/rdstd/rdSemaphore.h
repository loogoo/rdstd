/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdSemaphore.h 
* 当前版本: 1.0
* 摘  要:
		一旦不再需要，一定记住用CloseHandle关闭信号机的句柄。它的所
		有句柄都关闭以后，对象自己也会删除。
		一旦值大于零，信号机就会触发（发出信号）。ReleaseSemaphore
		函数的作用是增加信号机的计数。如果成功，就调用信号机上的一
		个等待函数来减少它的计数。
		Semaphore是另一个同步问题机制，不论是Event或Mutex，其他Process
		在执WaitForSingleObject时，就看当时的物件是Signal或UnSignal而决定是
		否等待，而Semaphore也相同，但是它要变成Signal /UnSignal的状态。却有
		些不同，它是提供一个计数值，它允许在这个计数值之内，任何执行到
		WaitForSingleObject的Thread都不会停下来，而且每执行WaitForSingleObject
		一次，计数值就减一，当计数值变成0时，该Semaphore才会处於UnSignal的状
		态，而某个Thread ReleaseSemaphore时，便会将计数值增加，以便其他的Thread
		或本身可得Signal的讯号，而使WaitForSingleObject停止等待。
		例如说，该电脑只有两个 COM PORT，所以只允许两个计数值同时使用
		COM PORT，因此，hSema = CreateSemaphore(ByVal 0&, 2, 2, "MySema")，
		第2个叁数表示：刚开始的时候，有多少个COM PORT可使用第3个叁数表示：
		最多有多少个COM PORT可使用，第4个叁数:Semaphore的名称，只要名称相同，
		则传回的handle(hSema)会指向相同的Semaphore物件。因此，要使用相同的
		名称来Create Semaphore才能达共用一个Semaphore的效果。而使用WaitForSingleObject
		来Check看看是否还有剩下的COM Port可使用，如果还有剩(计数值 > 0)，
		则没有等待而可执行下一行指令，同时，计数值减1。若有第三个要求COM PORT
		的使用，那它就得等待，直到有Thread执行ReleaseSemaphore(hSema, 1, count)
		第2个叁数表示：Release多少个COM PORT出来，一般来说都是1，表示一个
		ReleaseSemaphore会将计数器的值加一，但是您也可以指定 > 1的值，代表一
		口气增加计数器的值( + n , n > 1)。例如，您的程式一口气使用了两个COM PORT
		，并假设您於程式中有使用WaitForSingleObject两次，程式最後，使用
		ReleaseSemaphore(hSema, 2, count)而不必ReleaseSemaphore(hSema, 1, count)
		执行两次。第3个叁数表示：ReleaseSemaphore执行之前计数器原来的值。
		Semaphore和Event有个地方相同，那就是没有Owner的观念，即Thread A 所
		Create出的Semaphore物件，於Thread B中执行ReleaseSemaphore时，依然会增加
		计数器的值。

　　		WaitForSingleObject函数用来检测hHandle事件的信号状态，在某一线程中调用
		  该函数时，线程暂时挂起，如果在挂起的dwMilliseconds毫秒内，线程所等待的对象
		  变为有信号状态，则该函数立即返回；如果超时时间已经到达dwMilliseconds毫秒，
		  但hHandle所指向的对象还没有变成有信号状态，函数照样返回。参数dwMilliseconds
		  有两个具有特殊意义的值：0和INFINITE。若为0，则该函数立即返回；若为INFINITE
		  ，则线程一直被挂起，直到hHandle所指向的对象变为有信号状态时为止。
		  UINT CFlushDlg::MyThreadProc( LPVOID pParam ) {
		  while(WaitForSingleObject(g_event,MT_INTERVAL)!=WAIT_OBJECT_0){
		  } 
		  }

		  在这个线程循环中可以通过设置MT_INTERVAL来控制这个线程的函数体多久执行一次，
		  当事件为无信号状态时函数体隔MT_INTERVAL执行一次，当设置事件为有信号状态时，
		  线程就执行完毕了。 
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
***************************************************************************/
#ifndef _RD_SEMAPHORE_H_
#define _RD_SEMAPHORE_H_

#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE

class RD_STD_DLL_ENTRY rdSemaphore
{
public:
	rdSemaphore(const char *name=0, unsigned initValue = 0);
	virtual ~rdSemaphore();


	/**
	 * @brief wait 等待信号量
	 *
	 * @param unsigned msec
	 *
	 * @return bool
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时51分29秒
	 */
	bool wait(unsigned msec = INFINITE);

	/**
	 * @brief signal 触发信号量
	 *
	 * @param unsigned inc
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时51分47秒
	 */
	void signal(unsigned inc = 1);

	/**
	 * @brief reset 重置信号量为0
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时52分06秒
	 */
	void reset();

	/**
	 * @brief open 打开信号量
	 *
	 * @param char_t const * name
	 * @param unsigned initValue
	 *
	 * @return bool
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时52分21秒
	 */
	bool open(char_t const* name, unsigned initValue = 0) ;

	/**
	 * @brief close 关闭信号量
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时52分35秒
	 */
	void close();

	/**
	 * @brief erase 关闭信号量
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 16时52分46秒
	 */
	void erase();

protected:
	sem_t _sem;
};

END_RDSTD_NAMESPACE

#endif
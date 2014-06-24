/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdSemaphore.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
		һ��������Ҫ��һ����ס��CloseHandle�ر��źŻ��ľ����������
		�о�����ر��Ժ󣬶����Լ�Ҳ��ɾ����
		һ��ֵ�����㣬�źŻ��ͻᴥ���������źţ���ReleaseSemaphore
		�����������������źŻ��ļ���������ɹ����͵����źŻ��ϵ�һ
		���ȴ��������������ļ�����
		Semaphore����һ��ͬ��������ƣ�������Event��Mutex������Process
		��ִWaitForSingleObjectʱ���Ϳ���ʱ�������Signal��UnSignal��������
		��ȴ�����SemaphoreҲ��ͬ��������Ҫ���Signal /UnSignal��״̬��ȴ��
		Щ��ͬ�������ṩһ������ֵ�����������������ֵ֮�ڣ��κ�ִ�е�
		WaitForSingleObject��Thread������ͣ����������ÿִ��WaitForSingleObject
		һ�Σ�����ֵ�ͼ�һ��������ֵ���0ʱ����Semaphore�Żᴦ�UnSignal��״
		̬����ĳ��Thread ReleaseSemaphoreʱ����Ὣ����ֵ���ӣ��Ա�������Thread
		����ɵ�Signal��Ѷ�ţ���ʹWaitForSingleObjectֹͣ�ȴ���
		����˵���õ���ֻ������ COM PORT������ֻ������������ֵͬʱʹ��
		COM PORT����ˣ�hSema = CreateSemaphore(ByVal 0&, 2, 2, "MySema")��
		��2��������ʾ���տ�ʼ��ʱ���ж��ٸ�COM PORT��ʹ�õ�3��������ʾ��
		����ж��ٸ�COM PORT��ʹ�ã���4������:Semaphore�����ƣ�ֻҪ������ͬ��
		�򴫻ص�handle(hSema)��ָ����ͬ��Semaphore�������ˣ�Ҫʹ����ͬ��
		������Create Semaphore���ܴﹲ��һ��Semaphore��Ч������ʹ��WaitForSingleObject
		��Check�����Ƿ���ʣ�µ�COM Port��ʹ�ã��������ʣ(����ֵ > 0)��
		��û�еȴ�����ִ����һ��ָ�ͬʱ������ֵ��1�����е�����Ҫ��COM PORT
		��ʹ�ã������͵õȴ���ֱ����Threadִ��ReleaseSemaphore(hSema, 1, count)
		��2��������ʾ��Release���ٸ�COM PORT������һ����˵����1����ʾһ��
		ReleaseSemaphore�Ὣ��������ֵ��һ��������Ҳ����ָ�� > 1��ֵ������һ
		�������Ӽ�������ֵ( + n , n > 1)�����磬���ĳ�ʽһ����ʹ��������COM PORT
		����������춳�ʽ����ʹ��WaitForSingleObject���Σ���ʽ���ᣬʹ��
		ReleaseSemaphore(hSema, 2, count)������ReleaseSemaphore(hSema, 1, count)
		ִ�����Ρ���3��������ʾ��ReleaseSemaphoreִ��֮ǰ������ԭ����ֵ��
		Semaphore��Event�и��ط���ͬ���Ǿ���û��Owner�Ĺ����Thread A ��
		Create����Semaphore������Thread B��ִ��ReleaseSemaphoreʱ����Ȼ������
		��������ֵ��

����		WaitForSingleObject�����������hHandle�¼����ź�״̬����ĳһ�߳��е���
		  �ú���ʱ���߳���ʱ��������ڹ����dwMilliseconds�����ڣ��߳����ȴ��Ķ���
		  ��Ϊ���ź�״̬����ú����������أ������ʱʱ���Ѿ�����dwMilliseconds���룬
		  ��hHandle��ָ��Ķ���û�б�����ź�״̬�������������ء�����dwMilliseconds
		  �������������������ֵ��0��INFINITE����Ϊ0����ú����������أ���ΪINFINITE
		  �����߳�һֱ������ֱ��hHandle��ָ��Ķ����Ϊ���ź�״̬ʱΪֹ��
		  UINT CFlushDlg::MyThreadProc( LPVOID pParam ) {
		  while(WaitForSingleObject(g_event,MT_INTERVAL)!=WAIT_OBJECT_0){
		  } 
		  }

		  ������߳�ѭ���п���ͨ������MT_INTERVAL����������̵߳ĺ�������ִ��һ�Σ�
		  ���¼�Ϊ���ź�״̬ʱ�������MT_INTERVALִ��һ�Σ��������¼�Ϊ���ź�״̬ʱ��
		  �߳̾�ִ������ˡ� 
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
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
	 * @brief wait �ȴ��ź���
	 *
	 * @param unsigned msec
	 *
	 * @return bool
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 16ʱ51��29��
	 */
	bool wait(unsigned msec = INFINITE);

	/**
	 * @brief signal �����ź���
	 *
	 * @param unsigned inc
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 16ʱ51��47��
	 */
	void signal(unsigned inc = 1);

	/**
	 * @brief reset �����ź���Ϊ0
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 16ʱ52��06��
	 */
	void reset();

	/**
	 * @brief open ���ź���
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
	 * @date   2014��5��23�� 16ʱ52��21��
	 */
	bool open(char_t const* name, unsigned initValue = 0) ;

	/**
	 * @brief close �ر��ź���
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 16ʱ52��35��
	 */
	void close();

	/**
	 * @brief erase �ر��ź���
	 *
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 16ʱ52��46��
	 */
	void erase();

protected:
	sem_t _sem;
};

END_RDSTD_NAMESPACE

#endif
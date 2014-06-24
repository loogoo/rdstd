/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdTime.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			ʱ��ʵ�ù�����
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_TIME_H_
#define _RD_TIME_H_

#include "rdstdtp.h"



#ifdef _WIN32
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

#else
	#include <sys/time.h>   // for struct timeval
#endif

#include <string>

BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32
struct timezone 
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct ::timeval *tv, struct timezone *tz);
#endif

class RD_STD_DLL_ENTRY rdTime 
{
public:

	/**
	 * @brief get_timestamp_s  ��ȡʱ������룩
	 *
	 *
	 * @return uint64_t ���ش�Epoch������������
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ10��53��
	 */
	static uint64_t get_timestamp_s();


	/**
	 * @brief get_timestamp_ms ��ȡʱ�����΢�룩
	 *
	 *
	 * @return uint64_t ���ش�Epoch��������΢����
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ11��13��
	 */
	static uint64_t get_timestamp_ms();


	/**
	 * @brief safe_sleep_s ֧���жϵ�sleep���룩
	 *
	 * @param uint32_t second ˯�ߵ�����
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ11��47��
	 */
	static void safe_sleep_s(uint32_t second);


	/**
	 * @brief safe_sleep_ms ֧���жϵ�sleep�����룩
	 *
	 * @param uint32_t millisecond ˯�ߵĺ�����
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ12��07��
	 */
	static void safe_sleep_ms(uint32_t millisecond);

	/**
	 * @brief format_datetime_str ��ʱ�����ʽ��
	 *
	 * @param uint64_t millisecond  ��Epoch�������ĺ�����
	 *
	 * @return std::string
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ12��20��
	 */
	static std::string format_datetime_str(uint64_t millisecond);

#ifndef _WIN32
	//        struct ::timespec;
	/**
	 * @brief get_abs_timespec ��ȡ�ӵ�ǰʱ��� milliSeconds �����ľ���ʱ��
	 *
	 * @param struct timespec * ts	��ž���ʱ��
	 * @param int32_t millisecond	��ǰ��ĺ�����
	 *
	 * @return int32_t
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ12��37��
	 */
	static int32_t get_abs_timespec(struct timespec* ts, int32_t millisecond);
#endif

	/**
	 * @brief strftimeval ��struct timevalת��Ϊ�ַ�����ʽ����ʽΪ"YYYY-MM-DD HH:mm::SS.xxx"
	 *
	 * @param char * buffer					[out] ���ջ��������Ƽ���������СΪ24���ֽڡ�
	 * @param int32_t buflen				��������С
	 * @param const struct timeval * tv		��ת����struct timevalָ��
	 *	
	 * @return int32_t						����д�뻺�������ַ�����������\0�������򷵻�-1
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ12��57��
	 */
	static int32_t strftimeval(char* buffer, int32_t buflen, const struct timeval* tv);

	/**
	 * @brief get_date ��ȡ���ڴ� "YYYYMMDD"
	 *
	 *
	 * @return std::string ���ڴ�
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ13��27��
	 */
	static std::string get_date();


	/**
	 * @brief get_time 
	 *
	 *
	 * @return std::string ��ȡʱ�䴮 "HHmmSS.xxx"
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014��5��23�� 17ʱ13��41��
	 */
	static std::string get_time();

}; // end of class rdTime

END_RDSTD_NAMESPACE

#endif


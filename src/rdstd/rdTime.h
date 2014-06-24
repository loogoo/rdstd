/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdTime.h 
* 当前版本: 1.0
* 摘  要:
*			时间实用工具类
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
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
	 * @brief get_timestamp_s  获取时间戳（秒）
	 *
	 *
	 * @return uint64_t 返回从Epoch所经过的秒数
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时10分53秒
	 */
	static uint64_t get_timestamp_s();


	/**
	 * @brief get_timestamp_ms 获取时间戳（微秒）
	 *
	 *
	 * @return uint64_t 返回从Epoch所经过的微秒数
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时11分13秒
	 */
	static uint64_t get_timestamp_ms();


	/**
	 * @brief safe_sleep_s 支持中断的sleep（秒）
	 *
	 * @param uint32_t second 睡眠的秒数
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时11分47秒
	 */
	static void safe_sleep_s(uint32_t second);


	/**
	 * @brief safe_sleep_ms 支持中断的sleep（毫秒）
	 *
	 * @param uint32_t millisecond 睡眠的毫秒数
	 *
	 * @return void
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时12分07秒
	 */
	static void safe_sleep_ms(uint32_t millisecond);

	/**
	 * @brief format_datetime_str 将时间戳格式化
	 *
	 * @param uint64_t millisecond  从Epoch所经过的毫秒数
	 *
	 * @return std::string
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时12分20秒
	 */
	static std::string format_datetime_str(uint64_t millisecond);

#ifndef _WIN32
	//        struct ::timespec;
	/**
	 * @brief get_abs_timespec 获取从当前时间后 milliSeconds 毫秒后的绝对时间
	 *
	 * @param struct timespec * ts	存放绝对时间
	 * @param int32_t millisecond	当前后的毫秒数
	 *
	 * @return int32_t
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时12分37秒
	 */
	static int32_t get_abs_timespec(struct timespec* ts, int32_t millisecond);
#endif

	/**
	 * @brief strftimeval 将struct timeval转换为字符串形式，格式为"YYYY-MM-DD HH:mm::SS.xxx"
	 *
	 * @param char * buffer					[out] 接收缓冲区。推荐缓冲区大小为24个字节。
	 * @param int32_t buflen				缓冲区大小
	 * @param const struct timeval * tv		待转换的struct timeval指针
	 *	
	 * @return int32_t						返回写入缓冲区的字符个数（不含\0）；否则返回-1
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时12分57秒
	 */
	static int32_t strftimeval(char* buffer, int32_t buflen, const struct timeval* tv);

	/**
	 * @brief get_date 获取日期串 "YYYYMMDD"
	 *
	 *
	 * @return std::string 日期串
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时13分27秒
	 */
	static std::string get_date();


	/**
	 * @brief get_time 
	 *
	 *
	 * @return std::string 获取时间串 "HHmmSS.xxx"
	 *
	 * @see
	 * @note
	 *
	 * @author liy
	 * @date   2014年5月23日 17时13分41秒
	 */
	static std::string get_time();

}; // end of class rdTime

END_RDSTD_NAMESPACE

#endif


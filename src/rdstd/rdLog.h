/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdLog.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
***************************************************************************/
#ifndef _RD_LOG_H_
#define _RD_LOG_H_

#include <sstream>
#ifndef _WIN32
#include <pthread.h>
#include <sys/time.h>
#endif

#include <rdLogDeviceManager.h>
#include <rdThreadUtil.h>
#include <rdTime.h>

#define STR(x) STR2(x)
#define STR2(x) #x
#ifdef _WIN32
#define GETTIMEOFDAY rdstd::gettimeofday
#else
#define GETTIMEOFDAY gettimeofday
#endif

#define RDSTD_RAW_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, CONTENT) \
    do { \
        int32_t ___device_log_level = rdstd::rdLogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
        if (___device_log_level <= LOGLEVEL) { \
            struct timeval ___tv; \
            GETTIMEOFDAY(&___tv, NULL); \
            struct rdstd::log_message_t log_message = { \
                LOGLEVEL, \
                CONTENT, \
                LOGLEVEL_NAME, \
                __FILE__, \
                STR(__LINE__), \
                ___tv, \
				rdstd::rdThreadUtil::self_id() \
            }; \
            rdstd::rdLogDeviceManager::get_instance()->write(DEVICE, log_message); \
        } \
    } while(0)

#define RDSTD_RAW_TRACE(DEVICE,  CONTENT)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_TRACE,  "trace",  CONTENT)
#define RDSTD_RAW_DEBUG(DEVICE,  CONTENT)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_DEBUG,  "debug",  CONTENT)
#define RDSTD_RAW_NOTICE(DEVICE, CONTENT)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_NOTICE, "notice", CONTENT)
#define RDSTD_RAW_WARN(DEVICE,   CONTENT)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_WARN,   "warn",   CONTENT)
#define RDSTD_RAW_FATAL(DEVICE,  CONTENT)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_FATAL,  "fatal",  CONTENT)

#define RDSTD_STREAM_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, CONTENT) \
	do { \
	int32_t ___device_log_level = rdstd::rdLogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
	if (___device_log_level <= LOGLEVEL) { \
	std::ostringstream ___ss; \
	___ss << CONTENT; \
	std::string ___str = ___ss.str(); \
struct timeval ___tv; \
	GETTIMEOFDAY(&___tv, NULL); \
struct rdstd::log_message_t log_message = { \
	LOGLEVEL, \
	___str.c_str(), \
	LOGLEVEL_NAME, \
	__FILE__, \
	STR(__LINE__), \
	___tv, \
	rdstd::rdThreadUtil::self_id() \
}; \
	rdstd::rdLogDeviceManager::get_instance()->write(DEVICE, log_message); \
	} \
	} while(0)

#define RDSTD_STREAM_TRACE(DEVICE,  MESSAGE)    RDSTD_STREAM_WRITE(DEVICE, RDSTD_LOGLEVEL_TRACE,  "trace",   MESSAGE)
#define RDSTD_STREAM_DEBUG(DEVICE,  MESSAGE)    RDSTD_STREAM_WRITE(DEVICE, RDSTD_LOGLEVEL_DEBUG,  "debug",   MESSAGE)
#define RDSTD_STREAM_NOTICE(DEVICE, MESSAGE)    RDSTD_STREAM_WRITE(DEVICE, RDSTD_LOGLEVEL_NOTICE, "notice",  MESSAGE)
#define RDSTD_STREAM_WARN(DEVICE,   MESSAGE)    RDSTD_STREAM_WRITE(DEVICE, RDSTD_LOGLEVEL_WARN,   "warn",    MESSAGE)
#define RDSTD_STREAM_FATAL(DEVICE,  MESSAGE)    RDSTD_STREAM_WRITE(DEVICE, RDSTD_LOGLEVEL_FATAL,  "fatal",   MESSAGE)

#ifndef _WIN32

#define RDSTD_WRITE(DEVICE, LOGLEVEL, LOGLEVEL_NAME, FORMAT_AND_CONTENT...) \
    do { \
        int32_t ___device_log_level = rdstd::rdLogDeviceManager::get_instance()->get_device_loglevel(DEVICE); \
        if (___device_log_level <= LOGLEVEL) { \
            char ___buffer[1024]; \
            snprintf(___buffer, 1024, FORMAT_AND_CONTENT); \
            struct timeval ___tv; \
            gettimeofday(&___tv, NULL); \
            struct rdstd::log_message_t log_message = { \
                LOGLEVEL, \
                ___buffer, \
                LOGLEVEL_NAME, \
                __FILE__, \
                STR(__LINE__), \
                ___tv, \
                rdstd::ThreadUtil::self_id() \
            }; \
            rdstd::rdLogDeviceManager::get_instance()->write(DEVICE, log_message); \
        } \
    } while(0)

#define RDSTD_TRACE(DEVICE,  FORMAT...)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_TRACE,  "trace",  ##FORMAT)
#define RDSTD_DEBUG(DEVICE,  FORMAT...)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_DEBUG,  "debug",  ##FORMAT)
#define RDSTD_NOTICE(DEVICE, FORMAT...)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_NOTICE, "notic", ##FORMAT)
#define RDSTD_WARN(DEVICE,   FORMAT...)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_WARN,   "warn ",   ##FORMAT)
#define RDSTD_FATAL(DEVICE,  FORMAT...)    RDSTD_WRITE(DEVICE, RDSTD_LOGLEVEL_FATAL,  "fatal",  ##FORMAT)

#else

class CTraceFileAndLineInfo
{
public:
	CTraceFileAndLineInfo(
		const char* file_name,
		int32_t line_no,
		int32_t log_level,
		const char* log_level_name)
		: _file_name(file_name), _line_no(line_no),
		_log_level(log_level), _log_level_name(log_level_name)
	{}

	
	void __cdecl operator()(const char* device_name, const char* fmt, ...) const
	{
		std::stringstream ss;
		ss << _line_no;
		std::string line_no;
		ss >> line_no;
		va_list ptr; va_start(ptr, fmt);
		int32_t ___device_log_level = rdstd::rdLogDeviceManager::get_instance()->get_device_loglevel(device_name);
		if (___device_log_level <= _log_level) {
			char ___buffer[1024];
			_vsnprintf(___buffer, 1024, fmt, ptr);
			struct ::timeval ___tv;
			rdstd::gettimeofday(&___tv, NULL);
			struct rdstd::log_message_t log_message = {
				_log_level,
				___buffer,
				_log_level_name,
				_file_name,
				line_no.c_str(),
				___tv, \
				rdstd::rdThreadUtil::self_id()
			};
			rdstd::rdLogDeviceManager::get_instance()->write(device_name, log_message);
		}
		va_end(ptr);
	}

private:
	const char* const _file_name;
	int32_t _line_no;
	int32_t _log_level;
	const char* const _log_level_name;
};

#define RDSTD_TRACE CTraceFileAndLineInfo(__FILE__, __LINE__, RDSTD_LOGLEVEL_TRACE, "trace")
#define RDSTD_DEBUG CTraceFileAndLineInfo(__FILE__, __LINE__, RDSTD_LOGLEVEL_DEBUG, "debug")
#define RDSTD_NOTICE CTraceFileAndLineInfo(__FILE__, __LINE__, RDSTD_LOGLEVEL_NOTICE, "notice")
#define RDSTD_WARN CTraceFileAndLineInfo(__FILE__, __LINE__, RDSTD_LOGLEVEL_WARN, "warn")
#define RDSTD_FATAL CTraceFileAndLineInfo(__FILE__, __LINE__, RDSTD_LOGLEVEL_FATAL, "fatal")


#endif
#endif // _BGCC2_LOG_H_


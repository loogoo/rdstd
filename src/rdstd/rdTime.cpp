/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdTime.cpp
* 当前版本: 1.0
* 摘  要:
*
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录:
***************************************************************************/
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "rdTime.h"

BEGIN_RDSTD_NAMESPACE

#ifdef _WIN32
#define snprintf _snprintf
#endif

static struct tm* rdLocaltime_r(const time_t* timep, struct tm* result = NULL) {
#ifdef _WIN32
    (void)result;
    return localtime(timep);
#else
    return ::localtime_r(timep, result);
#endif
}

#ifdef _WIN32
//gettimeofday 引用自http://suacommunity.com/dictionary/gettimeofday-entry.php
int gettimeofday(struct ::timeval *tv, struct timezone *tz)
{
    FILETIME ft;

    unsigned __int64 tmpres = 0;
    static int tzflag = 0;

    if (NULL != tv)
    {
        GetSystemTimeAsFileTime(&ft);

        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;

        tmpres /= 10;

        tmpres -= DELTA_EPOCH_IN_MICROSECS;

        tv->tv_sec = (long)(tmpres / 1000000UL);
        tv->tv_usec = (long)(tmpres % 1000000UL);
    }

    if (NULL != tz)
    {
        if (!tzflag)
        {
            _tzset();
            tzflag++;
        }

        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime = _daylight;
    }

    return 0;
}
#endif

uint64_t rdTime::get_timestamp_s()
{
    struct ::timeval tv = {0, 0};
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

uint64_t rdTime::get_timestamp_ms()
{
    struct ::timeval tv = {0, 0};
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000 + tv.tv_usec;
}

void rdTime::safe_sleep_s(uint32_t second)
{
#ifdef _WIN32
    return rdTime::safe_sleep_ms(second * 1000);
#else
    struct timespec interval, remainder;
    int32_t ret;

    interval.tv_sec = second;
    interval.tv_nsec = 0;

    ret = nanosleep(&interval, &remainder);
    if (-1 == ret) {
        while (EINTR == errno && -1 == ret) {
            ret = nanosleep(&remainder, &remainder);
        }
    }
#endif
}

void rdTime::safe_sleep_ms(uint32_t millisecond)
{
#ifdef _WIN32
    ::Sleep(millisecond);
#else
    struct timespec interval, remainder;
    int32_t ret;

    interval.tv_sec = millisecond / 1000U;
    interval.tv_nsec = (uint64_t)millisecond % 1000UL * 1000UL * 1000UL;

    ret = nanosleep(&interval, &remainder);
    if (-1 == ret) {
        while (EINTR == errno && -1 == ret) {
            ret = nanosleep(&remainder, &remainder);
        }
    }
#endif
}

std::string rdTime::format_datetime_str(uint64_t millisecond)
{
    time_t time = (time_t)(millisecond / 1000);
    struct tm t;
    char buffer[24] = {0};

    t = *rdLocaltime_r(&time, &t);
    snprintf(buffer, 24, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
            t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int32_t)(millisecond % 1000));
    return std::string(buffer);
}

#ifndef _WIN32
int32_t rdTime::get_abs_timespec(struct timespec* ts, int32_t millisecond)
{
    struct timeval tv;
    int32_t ret;

    if (NULL == ts) {
        return EINVAL;
    }

    ret = gettimeofday(&tv, NULL);
    if (0 != ret) {
        return ret;
    }

    ts->tv_sec = tv.tv_sec;
    ts->tv_nsec = tv.tv_usec * 1000UL;

    ts->tv_sec += millisecond / 1000UL;
    ts->tv_nsec += millisecond % 1000UL * 1000000UL;

    ts->tv_sec += ts->tv_nsec/(1000UL * 1000UL *1000UL);
    ts->tv_nsec %= (1000UL * 1000UL *1000UL);

    return 0;
}
#endif

int32_t rdTime::strftimeval(char* buffer, int32_t buflen, const struct timeval* tv)
{
    if (NULL == buffer || NULL == tv) {
        return -1;
    }

    time_t time = tv->tv_sec;
    struct tm t;

    t = *rdLocaltime_r(&time, &t);
    return snprintf(buffer, buflen, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
            t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int32_t)tv->tv_usec / 1000);
}

std::string rdTime::get_date()
{
    time_t t = time(NULL);
    struct tm result;
    result = *rdLocaltime_r(&t, &result);

    char buffer[20] = {0};
    strftime(buffer, 20, "%Y%m%d", &result);
    return std::string(buffer);
}

std::string rdTime::get_time()
{
    time_t t = time(NULL);
    struct tm result;
    result = *rdLocaltime_r(&t, &result);

    char buffer[20] = {0};
    strftime(buffer, 20, "%H%M%S", &result);
    return std::string(buffer);
}


END_RDSTD_NAMESPACE

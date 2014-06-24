/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdStringUtil.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月24日
* 修改记录: 
***************************************************************************/
#include <ctype.h>
#ifdef _WIN32
#define _CRT_RAND_S
#include <objbase.h>
#endif
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "rdTime.h"
#include "rdStringUtil.h"

BEGIN_RDSTD_NAMESPACE

void rdStringUtil::toupper_inplace(char* str) {
    if (NULL == str) {
        return;
    }

    while ('\0' != *str) {
        *str = ::toupper(*str);
        ++str;
    }
}

std::string rdStringUtil::toupper(const char* str) {
    if (NULL == str) {
        return "";
    }

    std::string tmp(str);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
    return tmp;
}

std::string rdStringUtil::toupper(const std::string& str) {
    return rdStringUtil::toupper(str.c_str());
}

void rdStringUtil::tolower_inplace(char* str) {
    if (NULL == str) {
        return;
    }

    while ('\0' != *str) {
        //note 下行tolower前的::不可省略
        *str = ::tolower(*str);
        ++str;
    }
}

std::string rdStringUtil::tolower(const char* str) {
    if (NULL == str) {
        return "";
    }

    std::string tmp(str);
    //note 下行tolower前的::不可省略
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    return tmp;
}

std::string rdStringUtil::tolower(const std::string& str) {
    return rdStringUtil::tolower(str.c_str());
}

void rdStringUtil::ltrim_inplace(char* str) {
    if (NULL == str) {
        return;
    }

    char *pc = str;
    while (::isspace(*pc)) {
        ++pc;
    }

    if (pc != str) {
        while ((*str++ = *pc++)) {
        }
    }
}

std::string rdStringUtil::ltrim(const char* str) {
    if (NULL == str) {
        return "";
    }

    const char *pc = str;
    while (::isspace(*pc)) {
        ++pc;
    }

    return std::string(pc);
}

std::string rdStringUtil::ltrim(const std::string& str) {
    return rdStringUtil::ltrim(str.c_str());
}

void rdStringUtil::rtrim_inplace(char* str) {
    if (NULL == str) {
        return;
    }

    char *tail = str + strlen(str) - 1;
    while (tail >= str && ::isspace(*tail)) {
        *tail-- = '\0';
    }
}

std::string rdStringUtil::rtrim(const char* str, int32_t len) {
    if (NULL == str || len <= 0) {
        return "";
    }

    const char* head = str;
    const char* tail = head + len - 1;

    while (tail >= head && ::isspace(*tail)) {
        --tail;
    }

    if (tail >= head) {
        return std::string(head, tail - head + 1); 
    }
    else {
        return "";
    }
}

std::string rdStringUtil::rtrim(const char* str) {
    if (NULL == str) {
        return "";
    }
    else {
        return rdStringUtil::rtrim(str, (int32_t)strlen(str));
    }
}

std::string rdStringUtil::rtrim(const std::string& str) {
    return rdStringUtil::rtrim(str.c_str(), (int32_t)str.size());
}

void rdStringUtil::trim_inplace(char* str) {
    rdStringUtil::ltrim_inplace(str);
    rdStringUtil::rtrim_inplace(str);
}

std::string rdStringUtil::trim(const char* str) {
    return rdStringUtil::rtrim(rdStringUtil::ltrim(str));
}

std::string rdStringUtil::trim(const std::string& str) {
    return rdStringUtil::rtrim(rdStringUtil::ltrim(str));
}

void rdStringUtil::split_string(const std::string& str, const std::string& separator,
        std::vector<std::string>& container, bool filter_empty) {
    std::string::size_type pos;
    std::string::size_type lastPos = 0;

    container.clear();

    while (true) {
        pos = str.find_first_of(separator, lastPos);
        if (pos == std::string::npos) {
            pos = str.length();

            if(pos != lastPos || false == filter_empty) {
                container.push_back(std::string(str.data() + lastPos, pos - lastPos));
            }

            break;
        }
        else {
            if(pos != lastPos || false == filter_empty) {
                container.push_back(std::string(str.data() + lastPos, pos - lastPos));
            }
        }

        lastPos = pos + 1;
    }
}

std::string rdStringUtil::replace_string(const std::string& str, const std::string& target,
        const std::string& replacement) {
    std::string ret;
    std::string::size_type target_len = target.length();

    if (0 == target_len) {
        return str;
    }

    std::string::size_type pos_begin = 0;
    std::string::size_type pos_target = str.find(target, pos_begin);
    const char *str_head = str.data();

    while (pos_target != std::string::npos) {
        ret.append(str_head + pos_begin, pos_target - pos_begin);
        ret += replacement;
        pos_begin = pos_target + target_len;
        pos_target = str.find(target, pos_begin);
    }

    if (pos_begin < str.length()) {
        ret.append(str.begin() + pos_begin, str.end());
    }
    return ret;
}
bool rdStringUtil::str2uint32(const char* str, uint32_t& number) {
#ifdef _WIN32

    std::string trimed = rdStringUtil::ltrim(str);
    if (0 < trimed.length() && trimed.at(0) == '-') {
        return false;
    }
#endif
    return rdStringUtil::str2integer(str, number);
}

bool rdStringUtil::str2int32(const char* str, int32_t& number) {
    return rdStringUtil::str2integer(str, number);
}

bool rdStringUtil::str2uint64(const char* str, uint64_t& number) {
#ifdef _WIN32
    std::string trimed = rdStringUtil::ltrim(str);
    if (0 < trimed.length() && trimed.at(0) == '-') {
        return false;
    }
#endif
    return rdStringUtil::str2integer(str, number);
}

bool rdStringUtil::str2int64(const char* str, int64_t& number) {
    return rdStringUtil::str2integer(str, number);
}

std::string rdStringUtil::generate_uuid() {
    char uuid[40] = {0};
#ifdef _WIN32
    GUID guid;
    CoCreateGuid(&guid);
    _snprintf( uuid,
            sizeof(uuid),
            "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            guid.Data1, guid.Data2, guid.Data3,
            guid.Data4[0], guid.Data4[1],
            guid.Data4[2], guid.Data4[3],
            guid.Data4[4], guid.Data4[5],
            guid.Data4[6], guid.Data4[7]);
#else
    FILE* f = fopen("/proc/sys/kernel/random/uuid", "r");
    if (f != NULL) {
        fread(uuid, 1, 36, f);
        fclose(f);
    }
    else {
        return rand_string() + rand_string() + rand_string();
    }
#endif
    return uuid;
}

bool rdStringUtil::ipv4_ntoa(uint32_t src, std::string& dest) {
    uint32_t a, b, c, d;
    char buffer[16] = {0};

    a = (src >> 24) & 0xff;
    b = (src >> 16) & 0xff;
    c = (src >> 8) & 0xff;
    d = src & 0xff;

#ifdef _WIN32
    _snprintf(buffer, 16, "%u.%u.%u.%u", a, b, c, d);
#else
    snprintf(buffer, 16, "%u.%u.%u.%u", a, b, c, d);
#endif

    dest = buffer;
    return true;
}

bool rdStringUtil::ipv4_aton(const char* src, uint32_t& dest) {
    if (NULL == src) {
        return false;
    }

    uint32_t a, b, c, d;

    if (4 != sscanf(src, "%u.%u.%u.%u", &a, &b, &c, &d)) {
        return false;
    }

    if (a > 255 || b > 255 || c > 255 || d > 255) {
        return false;
    }

    dest = 0;
    dest |= a << 24;
    dest |= b << 16;
    dest |= c << 8;
    dest |= d;
    return true;
}

int32_t rdStringUtil::xstrncpy(char* dest, const char* src, int32_t n) {
    if (NULL == dest || NULL == src) {
        return -1;
    }

    int32_t ncpy = 0;

    while (*src && ncpy < n) {
        *dest++ = *src++;
        ++ncpy;
    }
    return ncpy;
}

std::string rdStringUtil::rand_string() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint32_t seed = tv.tv_usec;

    std::stringstream ss;
#ifdef _WIN32
    srand( seed );
    ss << rand();
#else
    ss << rand_r(&seed);
#endif
    std::string str;
    ss >> str;
    return str;
}

END_RDSTD_NAMESPACE

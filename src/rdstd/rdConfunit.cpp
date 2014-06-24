/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdConfunit.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
***************************************************************************/
#include "rdConfunit.h"

BEGIN_RDSTD_NAMESPACE

rdConfUnit::rdConfUnit(unit_type_t type) : _type(type) 
{
    if (UT_BOOL == type) {
        _union.b = true;
    }
    else if (UT_INT32 == type) {
        _union.i = 0;
    }
    else if (UT_INT64 == type) {
        _union.l = 0;
    }
    else if (UT_DOUBLE == type) {
        _union.d = 0.0;
    }
}

rdConfUnit::rdConfUnit(bool b) : _type(UT_BOOL) 
{
    _union.b = b;
}

rdConfUnit::rdConfUnit(int32_t i) : _type(UT_INT32) 
{
    _union.i = i;
}

rdConfUnit::rdConfUnit(int64_t l) : _type(UT_INT64) 
{
    _union.l = l;
}

rdConfUnit::rdConfUnit(double d) : _type(UT_DOUBLE) 
{
    _union.d = d;
}

rdConfUnit::rdConfUnit(const char* str) : _type(UT_STRING), _string(str) 
{
}

rdConfUnit::rdConfUnit(const std::string& str) : _type(UT_STRING), _string(str) 
{
}

rdConfUnit::~rdConfUnit() 
{
    if (is_array()) {
        iterator itr;
        for (itr = _vector.begin(); itr != _vector.end(); ++itr) {
            if (*itr) {
                delete (*itr);
            }
        }
        _vector.clear();
    }
    else if (is_group()) {
        std::map<std::string, rdConfUnit*>::iterator itr;
        for (itr = _map.begin(); itr != _map.end(); ++itr) {
            if (itr->second) {
                delete itr->second;
            }
        }
        _map.clear();
    }
}

int32_t rdConfUnit::get_type() const 
{
    return (int32_t)_type;
}

bool rdConfUnit::is_bool() const 
{
    return UT_BOOL == _type;
}

bool rdConfUnit::is_int32() const 
{
    return UT_INT32 == _type;
}

bool rdConfUnit::is_int64() const 
{
    return UT_INT64 == _type;
}

bool rdConfUnit::is_double() const 
{
    return UT_DOUBLE == _type;
}

bool rdConfUnit::is_string() const 
{
    return UT_STRING == _type;
}

bool rdConfUnit::is_array() const 
{
    return UT_ARRAY == _type;
}

bool rdConfUnit::is_group() const 
{
    return UT_GROUP == _type;
}

bool rdConfUnit::to_bool() const 
{
    if (is_bool()) {
        return _union.b;
    }
    else {
        throw std::exception();
    }
}

int32_t rdConfUnit::to_int32() const 
{
    if (is_int32()) {
        return _union.i;
    }
    else {
        throw std::exception();
    }
}

int64_t rdConfUnit::to_int64() const 
{
    if (is_int32()) {
        return (int64_t)_union.i;
    }
    else if (is_int64()) {
        return _union.l;
    }
    else {
        throw std::exception();
    }
}

double rdConfUnit::to_double() const 
{
    if (is_int32()) {
        return (double)_union.i;
    }
    else if (is_int64()) {
        return (double)_union.l;
    }
    else if (is_double()) {
        return _union.d;
    }
    else {
        throw std::exception();
    }
}

std::string rdConfUnit::to_string() const 
{
    if (is_string()) {
        return _string;
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::set_bool(bool b) 
{
    if (is_bool()) {
        _union.b = b;
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::set_int32(int32_t i) 
{
    if (is_int32()) {
        _union.i = i;
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::set_int64(int64_t l) 
{
    if (is_int64()) {
        _union.l = l;
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::set_double(double d) 
{
    if (is_double()) {
        _union.d = d;
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::set_string(const std::string& str) 
{
    if (is_string()) {
        _string = str;
    }
    else {
        throw std::exception();
    }
}


rdConfUnit::const_iterator rdConfUnit::begin() const 
{
    if (is_array()) {
        return _vector.begin();
    }
    else {
        throw std::exception();
    }
}

rdConfUnit::const_iterator rdConfUnit::end() const 
{
    if (is_array()) {
        return _vector.end();
    }
    else {
        throw std::exception();
    }
}

rdConfUnit* rdConfUnit::operator[](const std::string& index) 
{
    if (is_group()) {
        std::map<std::string, rdConfUnit*>::iterator itr;
        itr = _map.find(index);
        if (itr != _map.end()) {
            return itr->second;
        }
        else {
            return NULL;
        }
    }
    else {
        throw std::exception();
    }
}

rdConfUnit* rdConfUnit::push_back(rdConfUnit* punit) 
{
    if (is_array()) {
        _vector.push_back(punit);
        return punit;
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::pop_back() 
{
    if (is_array()) {
        if (_vector.size() > 0) {
            rdConfUnit* pson = NULL;
            pson = _vector.back();
            _vector.pop_back();
            if (NULL != pson) {
                delete pson;
            }
        }
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::insert(const std::string& key, rdConfUnit* punit) 
{
    if (is_group()) {
        _map.insert(std::make_pair(key, punit));
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::erase(const std::string& key) 
{
    if (is_group()) {
        std::map<std::string, rdConfUnit*>::iterator itr;
        itr = _map.find(key);
        if (itr != _map.end()) {
            if (NULL != itr->second) {
                delete itr->second;
            }
            _map.erase(itr);
        }
    }
    else {
        throw std::exception();
    }
}

void rdConfUnit::clear() 
{
    if (is_array()) {
        std::vector<rdConfUnit*>::iterator itr;
        for (itr = _vector.begin(); itr != _vector.end(); ++itr) {
            if (NULL != *itr) {
                delete *itr;
            }
        }
        _vector.clear();
    }
    else if (is_group()) {
        std::map<std::string, rdConfUnit*>::iterator itr;
        for (itr = _map.begin(); itr != _map.end(); ++itr) {
            if (NULL != itr->second) {
                delete itr->second;
            }
        }
        _map.clear();
    }
    else {
        throw std::exception();
    }
}

int32_t rdConfUnit::size() const 
{
    if (is_array()) {
        return (int32_t)_vector.size();
    }
    else if (is_group()) {
        return (int32_t)_map.size();
    }
    else {
        return 0;
    }
}

END_RDSTD_NAMESPACE

/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdConfloader.cpp 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
***************************************************************************/
#include <fstream>
#include "rdConfloader.h"
#include "rdConfunit.h"
#include "rdError.h"
#include "rdStringUtil.h"

BEGIN_RDSTD_NAMESPACE

const int32_t rdConfLoader::MAX_LINE_LEN = 512;

rdConfUnit* rdConfLoader::load_conf(const char* conf_filename) 
{
    std::ifstream conf_file(conf_filename, std::ifstream::in);
    if (conf_file.fail()) {
        return NULL;
    }

    char line[MAX_LINE_LEN];
    rdConfUnit* root = new(std::nothrow) rdConfUnit(rdConfUnit::UT_GROUP);
    if (NULL != root) {
        rdConfUnit* current = root;
        while (conf_file.good()) {
            conf_file.getline(line, MAX_LINE_LEN);

            if (is_white_line(line) || is_comment_line(line)) {
                continue;
            }

            if (0 != handle_line(line, root, current)) {
                delete root;
                root = NULL;
                break;
            }
        }
    }

    conf_file.close();
    return root;
}

bool rdConfLoader::is_white_line(const char* line) 
{
    if (NULL == line) {
        return false;
    }
    else {
        return rdStringUtil::trim(line).empty();
    }
}

bool rdConfLoader::is_comment_line(const char* line) 
{
    if (NULL == line) {
        return false;
    }
    else {
        std::string line_trimed = rdStringUtil::ltrim(line);
        return !line_trimed.empty() && ('#' == line_trimed[0]);
    }
}

int32_t rdConfLoader::handle_line(const char* line, rdConfUnit* root, rdConfUnit*& current) 
{
    if (NULL == root || NULL == current) {
        return E_NULL_POINTER;
    }

    std::vector<std::string> paths;
    std::string key;
    std::string value;

    if (0 == handle_as_section(line, paths)) {
        if (0 == paths.size()) {
            return E_CONF_ERROR;
        }
        current = push_section(root, paths);
        if (NULL == current) {
            return E_CONF_ERROR;
        }
    }
    else if (0 == handle_as_item(line, key, value)) {
        if (0 != push_item(current, key, value)) {
            return E_CONF_ERROR;
        }
    }
    else {
        return E_CONF_ERROR;
    }

    return 0;
}

int32_t rdConfLoader::handle_as_section(const char* line, std::vector<std::string>& paths) 
{
    paths.clear();
    std::string line_trimed = rdStringUtil::trim(line);
    int32_t size = (int32_t)line_trimed.size();

    if (size < 2
            || '[' != line_trimed[0]
            || ']' != line_trimed[size - 1]) { 
        return E_CONF_ERROR;
    }

    line_trimed = line_trimed.substr(1, size - 2);
    size -= 2;

    std::vector<std::string> v;
    rdStringUtil::split_string(line_trimed, ".", v, /*filter_empty = */false);
    if (0 == v.size()) {
        return E_CONF_ERROR;
    }

    std::vector<std::string>::iterator itr;
    for (itr = v.begin(); itr != v.end(); ++itr) {
        std::string s = rdStringUtil::trim(*itr);

        if (s.empty()) {
            return E_CONF_ERROR;
        }
        else {
            paths.push_back(s);
        }
    }

    std::vector<std::string>::reverse_iterator ritr;
    ritr = paths.rbegin();
    if (ritr != paths.rend()) {
        ++ritr;
        while (ritr != paths.rend()) {
            if ('@' == (*ritr)[0]) {
                paths.clear();
                return E_CONF_ERROR;
            }
            ++ritr;
        }
    }
    return 0;
}

int32_t rdConfLoader::handle_as_item(const char* line, std::string& key, std::string& value) 
{
    std::string line_trimed = rdStringUtil::trim(line);
    std::string::size_type pos = line_trimed.find_first_of('=');
    if (std::string::npos == pos) {
        return E_CONF_ERROR;
    }
    else {
        key = rdStringUtil::trim(line_trimed.substr(0, pos));
        if (key.empty()) {
            return E_CONF_ERROR;
        }

        if (pos != line_trimed.size() - 1) {
            value = rdStringUtil::trim(line_trimed.substr(pos + 1));
        }
        else {
            value = "";
        }

        return 0;
    }
}

rdConfUnit* rdConfLoader::push_section(rdConfUnit* root, const std::vector<std::string>& paths) 
{
    int32_t size = (int32_t)paths.size();
    if (0 == size) {
        return NULL;
    }

    rdConfUnit* current = root;
    rdConfUnit* son = NULL;
    for (int32_t i = 0; i < size - 1; ++i) {
        if (!current->is_group() || '@' == paths[i][0]) {
            return NULL;
        }
        son = (*current)[paths[i]];

        if (NULL == son) { //不存在，则插入
            current->insert(paths[i], new(std::nothrow) rdConfUnit(rdConfUnit::UT_GROUP));
            son = (*current)[paths[i]];
            if (NULL == son) {
                return NULL;
            }
        }
        current = son;
    }

    if (!current->is_group()) {
        return NULL;
    }

    if ('@' == paths[size - 1][0]) { //array
        std::string p = paths[size - 1].substr(1);
        son = (*current)[p];
        if (NULL != son) { //array已存在
            if (!son->is_array()) { //array不是UT_ARRAY
                return NULL;
            }
            return son->push_back(new(std::nothrow) rdConfUnit(rdConfUnit::UT_GROUP));
        }

        current->insert(p, new(std::nothrow) rdConfUnit(rdConfUnit::UT_ARRAY));
        son = (*current)[p];
        if (NULL == son || !son->is_array()) {
            return NULL;
        }
        return son->push_back(new(std::nothrow) rdConfUnit(rdConfUnit::UT_GROUP));
    }
    else {
        son = (*current)[paths[size - 1]];
        if (NULL != son) { //居然存在?
            return NULL;
        }
        current->insert(paths[size - 1], new(std::nothrow) rdConfUnit(rdConfUnit::UT_GROUP));
        son = (*current)[paths[size - 1]];
        return son;
    }
}

int32_t rdConfLoader::push_item(rdConfUnit* current, const std::string& key, const std::string& value) 
{
    if (NULL == current) {
        return E_CONF_ERROR;
    }

    rdConfUnit* tmp = (*current)[rdStringUtil::trim(key)];
    if (NULL != tmp) {
        return E_CONF_ERROR;
    }

    current->insert(rdStringUtil::trim(key), new(std::nothrow) rdConfUnit(rdStringUtil::trim(value)));
    return 0;
}

END_RDSTD_NAMESPACE
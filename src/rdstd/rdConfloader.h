/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdConfloader.h 
* 当前版本: 1.0
* 摘  要:
*			配置文件加载器
*
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
***************************************************************************/
#ifndef _RD_CONFLOADER_H_
#define _RD_CONFLOADER_H_

#include <vector>
#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE

class rdConfUnit;


class RD_STD_DLL_ENTRY rdConfLoader {
public:
    /**
     * @brief 行最大长度
     */
    static const int32_t MAX_LINE_LEN;

    /**
     * @brief load_conf 加载配置文件
     *
     * @param conf_filename 配置文件名
     *
     * @return 配置内容的Root;当加载出错时返回NULL
     */
    static rdConfUnit* load_conf(const char* conf_filename);

private:
    /**
     * @brief is_white_line 判断line是否为空白行----以空白符组成的行
     *
     * @param line C风格字符串
     *
     * @return true表示line为空白行；否则返回false
     */
    static bool is_white_line(const char* line);

    /**
     * @brief is_comment_line 判断line是否为注释行----以'#'开关的行
     *
     * @param line C风格字符串
     *
     * @return true表示line为注释行；否则返回false
     */
    static bool is_comment_line(const char* line);

    static int32_t handle_line(const char* line, rdConfUnit* root, rdConfUnit*& current);

    static int32_t handle_as_section(const char* line, std::vector<std::string>& paths);

    static int32_t handle_as_item(const char* line, std::string& key, std::string& value);

    static rdConfUnit* push_section(rdConfUnit* root, const std::vector<std::string>& paths);

    static int32_t push_item(rdConfUnit* current, const std::string& key,
            const std::string& value);

};

END_RDSTD_NAMESPACE

#endif

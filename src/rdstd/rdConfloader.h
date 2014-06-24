/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdConfloader.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			�����ļ�������
*
* ��  ��: liy ��������: 2014��5��26��
* �޸ļ�¼: 
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
     * @brief ����󳤶�
     */
    static const int32_t MAX_LINE_LEN;

    /**
     * @brief load_conf ���������ļ�
     *
     * @param conf_filename �����ļ���
     *
     * @return �������ݵ�Root;�����س���ʱ����NULL
     */
    static rdConfUnit* load_conf(const char* conf_filename);

private:
    /**
     * @brief is_white_line �ж�line�Ƿ�Ϊ�հ���----�Կհ׷���ɵ���
     *
     * @param line C����ַ���
     *
     * @return true��ʾlineΪ�հ��У����򷵻�false
     */
    static bool is_white_line(const char* line);

    /**
     * @brief is_comment_line �ж�line�Ƿ�Ϊע����----��'#'���ص���
     *
     * @param line C����ַ���
     *
     * @return true��ʾlineΪע���У����򷵻�false
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

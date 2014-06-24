/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdConfunit.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			INI�ļ����õ�Ԫ
*
* ��  ��: liy ��������: 2014��5��26��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_CONFUNIT_H_
#define _RD_CONFUNIT_H_

#include <string>
#include <map>
#include <vector>
#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE


class RD_STD_DLL_ENTRY rdConfUnit 
{
public:
    typedef std::vector<rdConfUnit*>::const_iterator const_iterator;
    typedef std::vector<rdConfUnit*>::iterator iterator;

    /**
     * @brief ���õ�Ԫ�����ͱ�ʶ
     */
    enum unit_type_t {
        UT_BOOL,
        UT_INT32,
        UT_INT64,
        UT_DOUBLE,
        UT_STRING,
        UT_ARRAY,
        UT_GROUP
    };

    /**
     * @brief rdConfUnit ���캯����ͨ�����ͱ�ʶ����
     */
    explicit rdConfUnit(unit_type_t type);

    /**
     * @brief rdConfUnit ���캯��������bool�������õ�Ԫ
     *
     * @param b ��ʼֵ
     */
    explicit rdConfUnit(bool b);

    /**
     * @brief rdConfUnit ���캯��������int32_t�������õ�Ԫ
     *
     * @param i ��ʼֵ
     */
    explicit rdConfUnit(int32_t i);

    /**
     * @brief rdConfUnit ���캯��������int64_t�������õ�Ԫ
     *
     * @param l ��ʼֵ
     */
    explicit rdConfUnit(int64_t l);

    /**
     * @brief rdConfUnit ���캯��������double�������õ�Ԫ
     *
     * @param d ��ʼֵ
     */
    explicit rdConfUnit(double d);

    /**
     * @brief rdConfUnit ���캯��������string�������õ�Ԫ
     *
     * @param str C����ַ���
     */
    explicit rdConfUnit(const char* str);

    /**
     * @brief rdConfUnit ���캯��������string�������õ�Ԫ
     *
     * @param str ��ʼֵ
     */
    explicit rdConfUnit(const std::string& str);

    /**
     * @brief ~rdConfUnit ��������
     */
    ~rdConfUnit();

    /**
     * @brief get_type ��ȡ���õ�Ԫ����
     *
     * @return ���õ�Ԫ����
     */
    int32_t get_type() const;

    /**
     * @brief is_bool �ж����õ�Ԫ�Ƿ�Ϊbool����
     *
     * @return 
     */
    bool is_bool() const;

    /**
     * @brief is_int32 �ж����õ�Ԫ�Ƿ�Ϊint32����
     *
     * @return 
     */
    bool is_int32() const;

    /**
     * @brief is_int64 �ж����õ�Ԫ�Ƿ�Ϊint64����
     *
     * @return 
     */
    bool is_int64() const;

    /**
     * @brief is_double �ж����õ�Ԫ�Ƿ�Ϊdobule����
     *
     * @return 
     */
    bool is_double() const;

    /**
     * @brief is_string �ж����õ�Ԫ�Ƿ�Ϊstring����
     *
     * @return 
     */
    bool is_string() const;

    /**
     * @brief is_array �ж����õ�Ԫ�Ƿ�Ϊarray����
     *
     * @return 
     */
    bool is_array() const;

    /**
     * @brief is_group �ж����õ�Ԫ�Ƿ�Ϊgroup����
     *
     * @return 
     */
    bool is_group() const;

    /**
     * @brief to_bool ȡ�����õ�Ԫ�е�boolֵ
     *
     * @return boolֵ
     * @see
     * @note �����õ�Ԫ����bool���ͣ����׳�std::exception�쳣
     */
    bool to_bool() const;

    /**
     * @brief to_int32 ȡ�����õ�Ԫ�е�int32ֵ
     *
     * @return int32ֵ
     * @see
     * @note �����õ�Ԫ����int32���ͣ����׳�std::exception�쳣
     */
    int32_t to_int32() const;

    /**
     * @brief to_int64 ȡ�����õ�Ԫ�е�int64ֵ
     *
     * @return int64ֵ
     * @see
     * @note �����õ�Ԫ����int32����int64���ͣ����׳�std::exception�쳣
     */
    int64_t to_int64() const;

    /**
     * @brief to_double ȡ�����õ�Ԫ�е�doubleֵ
     *
     * @return doubleֵ
     * @see
     * @note �����õ�Ԫ����double��int32��int64���ͣ����׳�std::exception�쳣
     */
    double to_double() const;

    /**
     * @brief to_string ȡ�����õ�Ԫ�е�stringֵ
     *
     * @return stringֵ
     * @see
     * @note �����õ�Ԫ����string���ͣ����׳�std::exception�쳣
     */
    std::string to_string() const;

    /**
     * @brief set_bool ����bool�������õ�boolֵ
     *
     * @param b ֵ
     * @see
     * @note �����õ�Ԫ����bool���ͣ����׳�std::exception�쳣
     */
    void set_bool(bool b);

    /**
     * @brief set_int32 ����int32�������õ�int32ֵ
     *
     * @param i ֵ
     * @see
     * @note �����õ�Ԫ����int32���ͣ����׳�std::exception�쳣
     */
    void set_int32(int32_t i);

    /**
     * @brief set_int64 ����int64�������õ�int64ֵ
     *
     * @param l ֵ
     * @see
     * @note �����õ�Ԫ����int64���ͣ����׳�std::exception�쳣
     */
    void set_int64(int64_t l);

    /**
     * @brief set_double ����double�������õ�Ԫ��doubleֵ
     *
     * @param d ֵ
     * @see
     * @note �����õ�Ԫ����double���ͣ����׳�std::exception�쳣
     */
    void set_double(double d);

    /**
     * @brief set_string ����string�������õ�Ԫ��stringֵ
     *
     * @param str ֵ
     * @see
     * @note �����õ�Ԫ����string���ͣ����׳�std::exception�쳣
     */
    void set_string(const std::string& str);

    /**
     * @brief begin ȡ��array���͵��׵�����
     *
     * @return �׵�����
     * @see
     * @note �����õ�Ԫ����array���ͣ����׳�std::explicit�쳣
     */
    const_iterator begin() const;

    /**
     * @brief end ȡ��array���͵�β������
     *
     * @return β������
     * @see
     * @note �����õ�Ԫ����array���ͣ����׳�std::exception�쳣
     */
    const_iterator end() const;

    /**
     * @brief operator[] ȡ����Ӧ�±��ϵ����õ�Ԫָ��
     *
     * @param index �±�
     *
     * @return ���õ�Ԫָ�룬���Ҳ����򷵻�NULL
     * @see
     * @note �����õ�Ԫ����group���ͣ����׳�std::exception�쳣
     */
    rdConfUnit* operator[](const std::string& index);

    /**
     * @brief push_back ����Ԫ�ز���array��
     *
     * @param punit ��Ԫ��
     *
     * @return ��Ԫ��
     * @see
     * @note �����õ�Ԫ����array���ͣ����׳�std::exception�쳣
     */
    rdConfUnit* push_back(rdConfUnit* punit);

    /**
     * @brief pop_back ��array�е���Ԫ��
     * @see
     * @note �����õ�Ԫ����array���ͣ����׳�std::exception�쳣
     */
    void pop_back();

    /**
     * @brief insert ����Ԫ����Ϊ����key����group��
     *
     * @param key ������
     * @param punit ��Ԫ��
     * @see
     * @note �����õ�Ԫ����group���ͣ����׳�std::exception�쳣
     */
    void insert(const std::string& key, rdConfUnit* punit);

    /**
     * @brief erase ��group��ɾ��������key��Ӧ�����õ�Ԫ
     *
     * @param key ������
     * @see
     * @note �����õ�Ԫ����group���ͣ����׳�std::exception�쳣
     */
    void erase(const std::string& key);

    /**
     * @brief clear ���array��group
     * @see
     * @note �����õ�Ԫ����array��group���ͣ����׳�std::exception�쳣
     */
    void clear();

    /**
     * @brief size �������õ�ԪԪ�ظ���
     *
     * @return Ԫ�ظ���
     */
    int32_t size() const;

private:
    unit_type_t _type;
    union {
        bool b;
        int32_t i;
        int64_t l;
        double d;
    }_union;
    std::string _string;
    std::vector<rdConfUnit*> _vector;
    std::map<std::string, rdConfUnit*> _map;
}; // end of class rdConfUnit

END_RDSTD_NAMESPACE

#endif


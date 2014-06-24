/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdLogDevice.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			���ڱ�ʾ���䵽��־�豸����־��Ϣ
*
* ��  ��: liy ��������: 2014��5��26��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_LOGDEVICE_H_
#define _RD_LOGDEVICE_H_

#include <stdio.h>      // for FILE
#include <vector>

#ifndef _WIN32
#include <pthread.h>    // for pthread_mutex_t
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
#include "rdTime.h"
#include "rdMutex.h"

#define MAX_DEVICE_NAME_LEN  512
#define MAX_FILE_PATH_LEN    512
#define MAX_LOG_FORMAT_LEN   512

#define LOG_SPLIT_POLICY_BY_TIME   0x0
#define LOG_SPLIT_POLICY_BY_SIZE   0x1

BEGIN_RDSTD_NAMESPACE

struct log_message_t {
    int32_t loglevel;          /** ��־����*/
    const char* content;       /** ��־���ݣ��ڸ�ʽ������%C��ʾ*/
    const char* loglevel_name; /** ��־�������ƣ��ڸ�ʽ������%N��ʾ*/
    const char* filename;      /** ��־�����ļ����ļ������ڸ�ʽ������%F��ʾ*/
    const char* line;          /** ��־���ڵ��кţ��ڸ�ʽ������%L��ʾ*/
	struct ::timeval tv;       /** ��־����������ʱ�䣬�ڸ�ʽ������%D��ʾ*/
    long long tid;			   /** �߳�ID���ڸ�ʽ������%T��ʾ*/
};

/**
 * @brief ��־�豸�ӿڡ�����涨����־�豸�����еĹ�������
 */
class RD_STD_DLL_ENTRY ILogDevice {
public:
    /**
     * @brief ~ILogDevice ��־�豸�ӿ���������
     */
    virtual ~ILogDevice() {
    }

    /**
     * @brief is_opened �ж���־�豸�Ƿ��Ѵ�
     *
     * @return  ����־�豸�Ѵ��򷵻�true�����򷵻�false��
     */
    virtual bool is_opened() const = 0;

    /**
     * @brief open ����־�豸
     *
     * @param param ��������
     *
     * @return �ɹ�����0
     */
    virtual int32_t open(void* param = NULL) = 0;

    /**
     * @brief close �ر���־�豸
     *
     * @param param ��������
     *
     * @return �ɹ�����0
     */
    virtual int32_t close(void* param = NULL) = 0;

    /**
     * @brief write д��־
     *
     * @param log_message ��־��Ϣ
     *
     * @return �ɹ�����0
     */
    virtual int32_t write(const struct log_message_t& log_message) = 0;

    /**
     * @brief get_name ������־�豸����
     *
     * @return ��־�豸����
     */
    virtual const char* get_name() const = 0;

    /**
     * @brief get_loglevel ������־�豸����
     *
     * @return ��־�豸����
     */
    virtual int32_t get_loglevel() const = 0;

    /**
     * @brief get_split_policy ������־�豸�ָ����
     *
     * @return ��־�豸�ָ����
     */
    virtual int32_t get_split_policy() const = 0;

    /**
     * @brief get_max_size ������־�豸�ļ����ֵ����λΪ�ֽڣ�
     *
     * @return  ��־�ļ�����ֽ���
     */
    virtual off_t get_max_size() const = 0;

    /**
     * @brief get_max_record_interval ������־�豸�ļ���¼���ʱ������λΪ�룩
     *
     * @return  ��־�ļ���¼���ʱ��
     */
    virtual int32_t get_max_record_interval() const = 0;

    /**
     * @brief get_log_format ��ȡ��־�豸����־��ʽ���ƴ�
     *
     * @return  ��־�豸����־��ʽ���ƴ�
     */
    virtual const char* get_log_format() const = 0;
};

//////////////////////////////////////////////////////////////////////////

/**
 * @brief ��־�豸�ĳ����ࡣ���ඨ�����־�豸��ͨ�÷���
 */
class RD_STD_DLL_ENTRY rdAbstractLogDevice : public ILogDevice {
public:
    /**
     * @brief rdAbstractLogDevice ���캯��
     *
     * @param name ��־�豸��
     * @param loglevel �豸��־����
     * @param split_policy �豸�ָ����
     * @param max_size ��־�ļ�����ֽ���
     * @param max_record_interval ��־�ļ���¼���ʱ��
     * @param log_format ��־��ʽ���ƴ�
     */
    rdAbstractLogDevice(
            const char* name,
            int32_t loglevel,
            int32_t split_policy,
            off_t max_size,
            int32_t max_record_interval,
            const char* log_format);

    /**
     * @brief ~rdAbstractLogDevice ��������
     */
    virtual ~rdAbstractLogDevice();

    /**
     * @brief get_name ������־�豸����
     *
     * @return ��־�豸����
     */
    virtual const char* get_name() const;

    /**
     * @brief get_loglevel ������־�豸����
     *
     * @return ��־�豸����
     */
    virtual int32_t get_loglevel() const;

    /**
     * @brief get_split_policy ������־�豸�ָ����
     *
     * @return ��־�豸�ָ����
     */
    virtual int32_t get_split_policy() const;

    /**
     * @brief get_max_size ������־�豸�ļ����ֵ����λΪ�ֽڣ�
     *
     * @return  ��־�ļ�����ֽ���
     */
    virtual off_t get_max_size() const;

    /**
     * @brief get_max_record_interval ������־�豸�ļ���¼���ʱ������λΪ�룩
     *
     * @return  ��־�ļ���¼���ʱ��
     */
    virtual int32_t get_max_record_interval() const;

    /**
     * @brief get_log_format ��ȡ��־�豸����־��ʽ���ƴ�
     *
     * @return  ��־�豸����־��ʽ���ƴ�
     */
    virtual const char* get_log_format() const;

protected:
    char    _name[MAX_DEVICE_NAME_LEN]; /** �豸����*/
    int32_t _loglevel;                  /** �豸��־�ȼ�*/
    int32_t _split_policy;              /** �ָ����*/
    int32_t _max_size;                  /** �ļ���󳤶�(��λ�ֽ�)*/
    int32_t _max_record_interval;       /** �ļ�����¼����(��λ��)*/
    char    _log_format[MAX_LOG_FORMAT_LEN]; /** ��־�豸����־��ʽ���ƴ�*/
};

//////////////////////////////////////////////////////////////////////////

/**
 * @brief �ļ���־�豸��
 */
class RD_STD_DLL_ENTRY rdFileLogDevice : public rdAbstractLogDevice {
public:
    /**
     * @brief rdFileLogDevice ���캯��
     *
     * @param file_path �ļ���־�豸�ļ�·��
     * @param name ��־�豸��
     * @param loglevel �豸��־����
     * @param split_policy �豸�ָ����
     * @param max_size ��־�ļ�����ֽ���
     * @param max_record_interval ��־�ļ���¼���ʱ��
     * @param log_format ��־��ʽ���ƴ�
     */
    rdFileLogDevice(
            const char* file_path,
            const char* name,
            int32_t loglevel,
            int32_t split_policy,
            off_t max_size,
            int32_t max_record_interval,
            const char* log_format);

    /**
     * @brief ~rdFileLogDevice ��������
     */
    virtual ~rdFileLogDevice();

    /**
     * @brief is_opened �ж���־�豸�Ƿ��Ѵ�
     *
     * @return  ����־�豸�Ѵ��򷵻�true�����򷵻�false��
     */
    virtual bool is_opened() const;

    /**
     * @brief open ����־�豸
     *
     * @param param ��������
     *
     * @return �ɹ�����0
     */
    virtual int32_t open(void* param = NULL);

    /**
     * @brief close �ر���־�豸
     *
     * @param param ��������
     *
     * @return �ɹ�����0
     */
    virtual int32_t close(void* param = NULL);

    /**
     * @brief write д��־
     *
     * @param log_message ��־��Ϣ
     *
     * @return �ɹ�����0
     */
    virtual int32_t write(const struct log_message_t& log_message);

private:
    /**
     * @brief exec_time_split_policy ����time�ָ���ԣ���������ʱ�����µ���־�ļ�
     *
     * @return �ɹ�����0
     */
    int32_t exec_time_split_policy();

    /**
     * @brief exec_size_split_policy ����size�ָ���ԣ���������ʱ�����µ���־�ļ�
     *
     * @param len ��д�����־�����ַ����ַ���
     *
     * @return �ɹ�����0
     */
    int32_t exec_size_split_policy(size_t len);

    /**
     * @brief get_file_stat ��ȡ��־�ļ����ļ�״̬
     *
     * @param state �ļ�״̬
     *
     * @return  �ɹ�����0
     */
    int32_t get_file_stat(struct stat& state) const;

    /**
     * @brief format_log_message ��ʽ����־��Ϣ
     *
     * @param logbuf ��־��Ϣ���ջ�����
     * @param logbufsiz ��־��Ϣ��������С
     * @param log_message ��־��Ϣ�ṹ��
     *
     * @return ���ظ�ʽ������ֽ���
     */
    int32_t format_log_message(char* logbuf, int32_t logbufsiz,
            const struct log_message_t& log_message);

private:
    std::string create_filename_suffix();

    char _file_path[MAX_FILE_PATH_LEN]; /** �ļ�ȫ·����*/
    FILE* _fp;							/** �ļ�ָ��*/
    rdMutex _mutex;
	struct ::timeval _create_time;		/** �ļ��Ĵ���ʱ��, ���ڰ�time��־�ָ����, ���ô˳�Ա��ԭ����ͨ��fstat�õ���stat�����޷���ʾ�ļ�����ʱ�䣿*/
    off_t _file_size;					/** ��ŵ�ǰ��־�ļ���С*/

};

END_RDSTD_NAMESPACE

#endif


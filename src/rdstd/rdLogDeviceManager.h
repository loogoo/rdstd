/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdLogDeviceManager.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��26��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_LOG_DEVICE_MANAGER_H_
#define _RD_LOG_DEVICE_MANAGER_H_

#include <vector>
#include "rdLogDevice.h"

//BGCC log level definition
#define RDSTD_LOGLEVEL_TRACE  0x0
#define RDSTD_LOGLEVEL_DEBUG  0x1
#define RDSTD_LOGLEVEL_NOTICE 0x2
#define RDSTD_LOGLEVEL_WARN   0x3
#define RDSTD_LOGLEVEL_FATAL  0x4
#define RDSTD_LOGLEVEL_NOLOG  0x10

BEGIN_RDSTD_NAMESPACE

/**
* @brief log_open 1. ���������ļ�����rdstd��־���� 2. ����������־����"rdstd"
*
* @param conf_filepath rdstd��־�����ļ�·��
* @see
* @note �������ļ������ڻ��������ļ�����ʱ������������ʾ��ֱ���˳������ִ��
* ����main������ڴ����øú���
*/
void RD_STD_DLL_ENTRY rdlog_open(const char* conf_filepath = NULL);

/**
* @brief log_close �ر�BGCC��־����
*
* @return 
* 
* @note
* ����main��������ǰ���øú���
*/
int32_t RD_STD_DLL_ENTRY log_close();

/**
* @brief ��־������
*/
class RD_STD_DLL_ENTRY rdLogDeviceManager 
{
public:
	/**
	* @brief get_instance ��ȡ��־������
	*
	* @return  ��־������
	*/
	static rdLogDeviceManager* get_instance();

	/**
	* @brief ~rdLogDeviceManager ��������
	*/
	~rdLogDeviceManager();

	/**
	* @brief is_device_exist �ж�ָ���豸device_name�Ƿ����
	*
	* @param device_name �豸����
	*
	* @return ���豸����ʱ����true�����򷵻�false
	*/
	bool is_device_exist(const char* device_name);

	/**
	* @brief get_device_loglevel ��ȡָ���豸����־����
	*
	* @param device_name �豸����
	*
	* @return ��־���𡣵��豸����ָ�����豸������ʱ������RDSTD_LOGLEVEL_NOLOG
	*/
	int32_t get_device_loglevel(const char* device_name);

	/**
	* @brief write ����־д���豸device_name��
	*
	* @param device_name �豸����
	* @param log_message ��־��Ϣ
	*
	* @return �ɹ��򷵻�0
	*/
	int32_t write(const char* device_name, const struct log_message_t& log_message);

private:
	/**
	* @brief add_device �����豸��ӵ��豸�б���
	*
	* @param device ���豸
	*
	* @return �����ɹ�����0�������豸�����������豸������ͬʱ������Ϊ���ʧ�ܣ����ط�0ֵ
	*/
	int32_t add_device(ILogDevice* device);

	/**
	* @brief get_device �����豸���ƻ�ȡ�豸
	*
	* @param device_name �豸����
	*
	* @return �豸ָ�롣��ָ���豸������ʱ����NULL
	*/
	ILogDevice* get_device(const char* device_name);

	std::vector<ILogDevice*> _devices;

	/**
	* @brief rdLogDeviceManager ������ʾ����
	*/
	rdLogDeviceManager();

	/**
	* @brief operator= ���ÿ�������
	*
	* @param rdLogDeviceManager
	*/
	rdLogDeviceManager& operator=(const rdLogDeviceManager&);

private:
	friend void load_default_device();
	friend void load_conf_device(const char*);
};

END_RDSTD_NAMESPACE

#endif 


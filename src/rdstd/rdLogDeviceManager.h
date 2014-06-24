/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdLogDeviceManager.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月26日
* 修改记录: 
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
* @brief log_open 1. 加载配置文件，打开rdstd日志对象 2. 加载内置日志对象"rdstd"
*
* @param conf_filepath rdstd日志配置文件路径
* @see
* @note 当配置文件不存在或者配置文件有误时将给出错误提示并直接退出程序的执行
* 请在main函数入口处调用该函数
*/
void RD_STD_DLL_ENTRY rdlog_open(const char* conf_filepath = NULL);

/**
* @brief log_close 关闭BGCC日志对象
*
* @return 
* 
* @note
* 请在main函数结束前调用该函数
*/
int32_t RD_STD_DLL_ENTRY log_close();

/**
* @brief 日志对象类
*/
class RD_STD_DLL_ENTRY rdLogDeviceManager 
{
public:
	/**
	* @brief get_instance 获取日志对象单例
	*
	* @return  日志对象单例
	*/
	static rdLogDeviceManager* get_instance();

	/**
	* @brief ~rdLogDeviceManager 析构函数
	*/
	~rdLogDeviceManager();

	/**
	* @brief is_device_exist 判断指定设备device_name是否存在
	*
	* @param device_name 设备名称
	*
	* @return 当设备存在时返回true；否则返回false
	*/
	bool is_device_exist(const char* device_name);

	/**
	* @brief get_device_loglevel 获取指定设备的日志级别
	*
	* @param device_name 设备名称
	*
	* @return 日志级别。当设备名称指定的设备不存在时，返回RDSTD_LOGLEVEL_NOLOG
	*/
	int32_t get_device_loglevel(const char* device_name);

	/**
	* @brief write 将日志写入设备device_name中
	*
	* @param device_name 设备名称
	* @param log_message 日志信息
	*
	* @return 成功则返回0
	*/
	int32_t write(const char* device_name, const struct log_message_t& log_message);

private:
	/**
	* @brief add_device 将新设备添加到设备列表中
	*
	* @param device 新设备
	*
	* @return 操作成功返回0。当新设备名称与已有设备名称相同时，则认为添加失败，返回非0值
	*/
	int32_t add_device(ILogDevice* device);

	/**
	* @brief get_device 根据设备名称获取设备
	*
	* @param device_name 设备名称
	*
	* @return 设备指针。当指定设备不存在时返回NULL
	*/
	ILogDevice* get_device(const char* device_name);

	std::vector<ILogDevice*> _devices;

	/**
	* @brief rdLogDeviceManager 禁用显示构造
	*/
	rdLogDeviceManager();

	/**
	* @brief operator= 禁用拷贝构造
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


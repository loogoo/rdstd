// rdWebServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdio.h>

#include <rdLog.h>

using namespace rdstd;


int main(int argc, char* argv[])
{
	rdLogDeviceManager* manager = rdLogDeviceManager::get_instance(); 
	
	manager->add_device("testlog.txt", "testLog", RDSTD_LOGLEVEL_TRACE, LOG_SPLIT_POLICY_BY_TIME, 0, 60*60, "%D [%N] %T {%F(%L)} %C");

	RDSTD_STREAM_TRACE("testLog", "xdalskdjfasl");
	RDSTD_STREAM_TRACE("testLog", "��������浽");

	return 1;
}

# *********************************************************************
# * Project:  rdstd
# * Purpose:  cmake script
# * Author:   liy, code_ly@163.com
# *********************************************************************
cmake_minimum_required (VERSION 2.8)
set(PROJECT_NAME rdstd)


#设置编译类型debug 或者release。 debug 版会生成相关调试信息，可以使用GDB 进行
#SET(CMAKE_BUILE_TYPE DEBUG)


set(RDSTD_PRJ_PATH ${RDPRJ_CURRENT_SOURCE_DIR}/src/rdstd)

#ADD_DEFINITIONS(RD_STD_DLL)
#ADD_DEFINITIONS(RD_STD_DLL_EXPORT)

#相关头文件的目录
INCLUDE_DIRECTORIES()


#相关库文件的目录
LINK_DIRECTORIES()



#设置变量，表示所有的源文件
SET(RDSTD_PRJ_HEADERS ${RDSTD_PRJ_HEADERS}
    ${RDSTD_PRJ_PATH}/config.h
	${RDSTD_PRJ_PATH}/rdstdtp.h
	${RDSTD_PRJ_PATH}/rdError.h
	${RDSTD_PRJ_PATH}/rdTime.h
	${RDSTD_PRJ_PATH}/rdThreadutil.h
	${RDSTD_PRJ_PATH}/rdStringUtil.h
	${RDSTD_PRJ_PATH}/rdFileutil.h
	${RDSTD_PRJ_PATH}/rdGuard.h
	${RDSTD_PRJ_PATH}/rdMutex.h
	${RDSTD_PRJ_PATH}/rdMutexEx.h
	${RDSTD_PRJ_PATH}/rdEvent.h
	${RDSTD_PRJ_PATH}/rdSemaphore.h
	${RDSTD_PRJ_PATH}/rdSyncVector.h
	${RDSTD_PRJ_PATH}/rdSharedPtr.h
	${RDSTD_PRJ_PATH}/rdShared.h
	${RDSTD_PRJ_PATH}/rdRunable.h
	${RDSTD_PRJ_PATH}/rdThread.h
	${RDSTD_PRJ_PATH}/rdThreadgroup.h
	${RDSTD_PRJ_PATH}/rdThreadpool.h
	${RDSTD_PRJ_PATH}/rdThreadManager.h
	${RDSTD_PRJ_PATH}/rdLogDevice.h
	${RDSTD_PRJ_PATH}/rdLogDeviceManager.h
	${RDSTD_PRJ_PATH}/rdConfunit.h
	${RDSTD_PRJ_PATH}/rdConfloader.h
	${RDSTD_PRJ_PATH}/rdLog.h
)

SET(RDSTD_PRJ_SOURCE ${RDSTD_PRJ_SOURCE}
	${RDSTD_PRJ_PATH}/rdstdtp.cpp
	${RDSTD_PRJ_PATH}/rdTime.cpp
	${RDSTD_PRJ_PATH}/rdThreadutil.cpp
	${RDSTD_PRJ_PATH}/rdStringUtil.cpp
	${RDSTD_PRJ_PATH}/rdFileutil.cpp
	${RDSTD_PRJ_PATH}/rdMutex.cpp
	${RDSTD_PRJ_PATH}/rdMutexEx.cpp
	${RDSTD_PRJ_PATH}/rdEvent.cpp
	${RDSTD_PRJ_PATH}/rdSemaphore.cpp
	${RDSTD_PRJ_PATH}/rdShared.cpp
	${RDSTD_PRJ_PATH}/rdThread.cpp
	${RDSTD_PRJ_PATH}/rdThreadgroup.cpp
	${RDSTD_PRJ_PATH}/rdThreadpool.cpp
	${RDSTD_PRJ_PATH}/rdThreadManager.cpp
	${RDSTD_PRJ_PATH}/rdLogDevice.cpp
	${RDSTD_PRJ_PATH}/rdLogDeviceManager.cpp
	${RDSTD_PRJ_PATH}/rdConfunit.cpp
	${RDSTD_PRJ_PATH}/rdConfloader.cpp
)


ADD_LIBRARY(rdstd SHARED ${RDSTD_HEADERS} ${RDSTD_PRJ_SOURCE})

#TARGET_LINK_LIBRARY()

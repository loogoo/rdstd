# *********************************************************************
# * Project:  rdprj
# * Purpose:  cmake script
# * Author:   liy, code_ly@163.com
# *********************************************************************
cmake_minimum_required (VERSION 2.8)
set(PROJECT_NAME rdprj)

#SET(CMAKE_BUILE_TYPE DEBUG)


if(MSVC)
    #string(REPLACE "/W4" "/W0" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    #string(REPLACE "/W4" "/W0" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    # string(REPLACE "/Gm" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    #set(CMAKE_CXX_FLAGS_DEBUG "/Gm /ZI /W3 /Od")
    # add_definitions(-DDISABLE_SOME_FLOATING_POINT)
    # set_target_properties( ${the_target} PROPERTIES COMPILE_FLAGS "/Gm" )
    if(CMAKE_CL_64)
        set_target_properties(${the_target} PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x64")
        add_definitions(-D_WIN64)
    endif()
endif()

if(UNIX)
#     if(CMAKE_COMPILER_IS_GNUCXX OR CV_ICC)
#        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -fno-strict-aliasing")#-Wextra -Wall -W -pthread -O2 -fno-strict-aliasing -pthrea
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fno-strict-aliasing")
#     endif()
    # Select flags.
#    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O0 -g")
#    set(CMAKE_CXX_FLAGS_RELEASE        "-O")
#    set(CMAKE_CXX_FLAGS_DEBUG          "-Wall -g -O")
#    set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O0 -g")
#    set(CMAKE_C_FLAGS_RELEASE          "-O")
#    set(CMAKE_C_FLAGS_DEBUG            "-Wall -g -O2")
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(RDPRJ_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RDPRJ_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src/rdstd)

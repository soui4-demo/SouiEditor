#
# 1394020320@qq.com
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SOUI_INCLUDE}/config)
include_directories(${SOUI_INCLUDE}/components)
include_directories(${SOUI_INCLUDE}/utilities/include)
include_directories(${SOUI_INCLUDE}/SOUI/include)
include_directories(controls.extend)

file(GLOB_RECURSE CTRLS_SRC controls.extend/*.*)

set(CURRENT_SRCS
    SCtrlsRegister.cpp
)
 
set(CURRENT_HEADERS
    stdafx.h
    SCtrlsRegister.h
)
 
add_library(ExtendCtrls STATIC ${CURRENT_HEADERS} ${CURRENT_SRCS} ${CTRLS_SRC})

if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
target_compile_options(ExtendCtrls PRIVATE -fPIC)
target_link_libraries(ExtendCtrls swinx)
endif()
target_precompile_headers(ExtendCtrls PRIVATE "stdafx.h")

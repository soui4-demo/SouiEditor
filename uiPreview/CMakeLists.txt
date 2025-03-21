#
# 1394020320@qq.com
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SOUI_INCLUDE}/config)
include_directories(${SOUI_INCLUDE}/components)
include_directories(${SOUI_INCLUDE}/utilities/include)
include_directories(${SOUI_INCLUDE}/SOUI/include)
include_directories(${SOUI_SRC_ROOT}/controls.extend)


file(GLOB_RECURSE CURRENT_MONITOR  monitor/*.*)
file(GLOB_RECURSE CURRENT_SRCS  src/*.*)

file(GLOB BASE_SRCS  *.h *.cpp)

file(GLOB_RECURSE CURRENT_SOUIS  *.xml *.idx *.ico)
file(GLOB_RECURSE CURRENT_RC *.rc *.rc2)

source_group("Base Files" FILES ${BASE_SRCS})
source_group("Monitor Files" FILES ${CURRENT_MONITOR})
source_group("Source Files" FILES ${CURRENT_SRCS})
source_group("SoUI Resouece" FILES ${CURRENT_SOUIS})
source_group("Resource Files" FILES ${CURRENT_RC})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
add_executable(uiPreview WIN32 ${BASE_SRCS} ${CURRENT_MONITOR} ${CURRENT_SRCS} ${CURRENT_SOUIS} ${CURRENT_RC})
target_link_libraries(uiPreview soui4 utilities4)
else()
add_executable(uiPreview WIN32 ${BASE_SRCS}  ${CURRENT_SRCS} ${CURRENT_SOUIS} ${CURRENT_RC})
target_link_libraries(uiPreview soui4 utilities4 swinx)
endif()



target_precompile_headers(uiPreview PRIVATE "stdafx.h")


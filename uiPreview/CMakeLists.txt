#
# 1394020320@qq.com
#

include_directories(${SOUI_ROOT}/config)
include_directories(${SOUI_ROOT}/components)
include_directories(${SOUI_ROOT}/utilities/include)
include_directories(${SOUI_ROOT}/SOUI/include)
include_directories(${SOUI_ROOT}/controls.extend)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
file(GLOB_RECURSE CURRENT_SRCS  *.cpp)
file(GLOB_RECURSE CURRENT_SOUIS  *.xml *.idx *.ico)
file(GLOB_RECURSE CURRENT_RC *.rc *.rc2)

source_group("Header Files" FILES ${CURRENT_HEADERS})
source_group("Source Files" FILES ${CURRENT_SRCS})
source_group("SoUI Resouece" FILES ${CURRENT_SOUIS})
source_group("Resource Files" FILES ${CURRENT_RC})

#IF (CMAKE_CL_64)
#	link_directories(${SOUI_ROOT}/bin64)
#ELSE (CMAKE_CL_64)
#	link_directories(${SOUI_ROOT}/bin)
#ENDIF (CMAKE_CL_64)

add_executable(uiPreview WIN32 ${CURRENT_HEADERS} ${CURRENT_SRCS} ${CURRENT_SOUIS} ${CURRENT_RC})

#add_dependencies(uiPreview soui-sys-resource)
#target_link_libraries(uiPreview utilities soui ${COM_LIBS})
target_link_libraries(uiPreview
    debug soui4d optimized soui4
    debug utilities4d optimized utilities4
)

set(CMAKE_DEBUG_POSTFIX "d")

target_precompile_headers(uiPreview PRIVATE "stdafx.h")
set_target_properties(uiPreview PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

set_target_properties (uiPreview PROPERTIES
    FOLDER demos
)

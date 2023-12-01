#
# 1394020320@qq.com
#

cmake_minimum_required(VERSION 3.4.3)
project(SouiEditor)
file (TO_CMAKE_PATH "$ENV{SOUI4PATH}" SOUI_ROOT)

message(STATUS "SOUI_ROOT: ${SOUI_ROOT}")
if ("${SOUI_ROOT}" STREQUAL "")
    message(FATAL_ERROR "FATAL:can't find env variable SOUI4PATH, clone soui core and install wizard first, please.")
endif()

include(${SOUI_ROOT}/__cmake/internal_utils.cmake)
include(${SOUI_ROOT}/__cmake/global.cmake)

readSettingFile(UNICODE "1" USE_UNICODE)
readSettingFile(WCHAR "1" WCHAR_AS_DEFAULT)
readSettingFile(MT "0" SHARED_CRT)
readSettingFile(SUPPORT_XP "1" XP_TOOLSET)

#message(STATUS "USE_UNICODE: ${USE_UNICODE}")
#message(STATUS "WCHAR_AS_DEFAULT: ${WCHAR_AS_DEFAULT}")
#message(STATUS "SHARED_CRT: ${SHARED_CRT}")
#message(STATUS "XP_TOOLSET: ${XP_TOOLSET}")

config_compiler_and_linker()

IF (CMAKE_CL_64)
    link_directories(${SOUI_ROOT}/bin64)
ELSE (CMAKE_CL_64)
    link_directories(${SOUI_ROOT}/bin)
ENDIF (CMAKE_CL_64)

add_subdirectory(ExtendCtrls)
add_subdirectory(uieditor)
add_subdirectory(uiPreview)
add_subdirectory(uiviewer)

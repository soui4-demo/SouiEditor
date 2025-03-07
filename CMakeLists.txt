#
# 1394020320@qq.com
#

cmake_minimum_required(VERSION 3.4.3)
project(SouiEditor)
file (TO_CMAKE_PATH "$ENV{SOUI4PATH}" SOUI_SRC_ROOT)

message(STATUS "SOUI_SRC_ROOT: ${SOUI_SRC_ROOT}")
if ("${SOUI_SRC_ROOT}" STREQUAL "")
	message(FATAL_ERROR "FATAL:can't find env variable SOUI_SRC_ROOT, clone soui core and install wizard first, please.")
endif()

message(STATUS "CMAKE_GENERATOR_PLATFORM: ${CMAKE_GENERATOR_PLATFORM}")
if(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
file (TO_CMAKE_PATH "$ENV{SOUI4_INSTALL_32}" SOUI_ROOT)
else()
file (TO_CMAKE_PATH "$ENV{SOUI4_INSTALL_64}" SOUI_ROOT)
endif()

message(STATUS "SOUI_ROOT: ${SOUI_ROOT}")
if ("${SOUI_ROOT}" STREQUAL "")
	message(FATAL_ERROR "FATAL:can't find env variable SOUI4_INSTALL_64, clone soui core and install wizard first, please.")
endif()

include(${SOUI_SRC_ROOT}/__cmake/internal_utils.cmake)
include(${SOUI_SRC_ROOT}/__cmake/global.cmake)

set(SOUI_INCLUDE ${SOUI_ROOT}/include)
readSettingFile(${SOUI_INCLUDE}/config/build.cfg UNICODE "1" USE_UNICODE)
readSettingFile(${SOUI_INCLUDE}/config/build.cfg WCHAR "1" WCHAR_AS_DEFAULT)
readSettingFile(${SOUI_INCLUDE}/config/build.cfg MT "0" SHARED_CRT)
readSettingFile(${SOUI_INCLUDE}/config/build.cfg SUPPORT_XP "1" XP_TOOLSET)


config_compiler_and_linker()
link_directories(${SOUI_ROOT}/lib)

add_subdirectory(ExtendCtrls)
add_subdirectory(uieditor)
add_subdirectory(uiPreview)
add_subdirectory(uiviewer)

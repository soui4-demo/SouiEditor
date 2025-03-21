#
# 1394020320@qq.com
#

cmake_minimum_required(VERSION 3.4.3)
project(SouiEditor)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
file (TO_CMAKE_PATH "$ENV{SOUI4PATH}" SOUI_SRC_ROOT)
message(STATUS "CMAKE_SIZEOF_VOID_P: ${CMAKE_SIZEOF_VOID_P}")
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
file (TO_CMAKE_PATH "$ENV{SOUI4_INSTALL_32}" SOUI_ROOT)
else()
file (TO_CMAKE_PATH "$ENV{SOUI4_INSTALL_64}" SOUI_ROOT)
endif()

else()
#set SOUI_SRC_ROOT to your local path
set(SOUI_SRC_ROOT "/home/flyhigh/work/soui4")
set(SOUI_ROOT "/home/flyhigh/work/soui4.install")
endif()

message(STATUS "SOUI_SRC_ROOT: ${SOUI_SRC_ROOT}")
if ("${SOUI_SRC_ROOT}" STREQUAL "")
	message(FATAL_ERROR "FATAL:can't find env variable SOUI_SRC_ROOT, clone soui core and install wizard first, please.")
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


include_directories(${CMAKE_SOURCE_DIR}/zipparam)
if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
include_directories(${SOUI_ROOT}/include/swinx/include)
else()
if (MSVC_VERSION LESS 1600)
    include_directories(${SOUI_SRC_ROOT}/third-part/stdint)
endif()
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)

link_directories(${SOUI_ROOT}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
else()

link_directories(${SOUI_ROOT}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
endif()

add_subdirectory(copy_files)
add_subdirectory(ExtendCtrls)
add_subdirectory(uieditor)
add_subdirectory(uiPreview)
add_subdirectory(uiviewer)

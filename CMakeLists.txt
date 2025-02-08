#
# 1394020320@qq.com
#

cmake_minimum_required(VERSION 3.4.3)
project(SouiEditor)


set(SOUI_ROOT ${CMAKE_SOURCE_DIR}/depends/soui4)

include(${CMAKE_SOURCE_DIR}/__cmake/internal_utils.cmake)
include(${CMAKE_SOURCE_DIR}/__cmake/global.cmake)

set(SOUI_INCLUDE ${SOUI_ROOT}/include)
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
readSettingFile(${SOUI_INCLUDE}/config/build.cfg UNICODE "1" USE_UNICODE)
readSettingFile(${SOUI_INCLUDE}/config/build.cfg WCHAR "1" WCHAR_AS_DEFAULT)
readSettingFile(${SOUI_INCLUDE}/config/build.cfg MT "0" SHARED_CRT)
readSettingFile(${SOUI_INCLUDE}/config/build.cfg SUPPORT_XP "1" XP_TOOLSET)
else()
set(USE_UNICODE 0)
set(WCHAR_AS_DEFAULT 1)
set(SHARED_CRT 1)
endif()

config_compiler_and_linker()


include_directories(${SOUI_INCLUDE}/components/resprovider-zip)
if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
include_directories(${SOUI_ROOT}/include/swinx/include)
else()
if (MSVC_VERSION LESS 1600)
    include_directories(${SOUI_INCLUDE}/third-part/stdint)
endif()
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
link_directories(${CMAKE_SOURCE_DIR}/depends/soui4/lib/$(PlatformName))
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
else()
link_directories(${CMAKE_SOURCE_DIR}/depends/soui4/lib/deb)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


add_subdirectory(copy_files)
add_subdirectory(Scintilla)
add_subdirectory(ExtendCtrls)
add_subdirectory(uieditor)
add_subdirectory(uiPreview)
add_subdirectory(uiviewer)

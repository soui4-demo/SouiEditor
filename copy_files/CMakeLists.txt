# copy_files/CMakeLists.txt

# 初始化TARGET_DIR变量
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
set(TARGET_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}$(ConfigurationName)")
else()
set(TARGET_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

# 添加自定义目标
add_custom_target(copy_files ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${TARGET_DIR}
)

add_custom_command(TARGET copy_files PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/copy_files/soui-sys-resource.zip
            ${TARGET_DIR}
    COMMENT "Copying ${FILE} to ${TARGET_DIR}/soui-sys-resource.zip"
)

add_custom_command(TARGET copy_files PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/uieditor/uires
            ${TARGET_DIR}/uieditor_uires
    COMMENT "Copying ${FILE} to ${TARGET_DIR}"
)
add_custom_command(TARGET copy_files PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/uieditor/Config
            ${TARGET_DIR}/Config
    COMMENT "Copying ${FILE} to ${TARGET_DIR}"
)

add_custom_command(TARGET copy_files PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/uiPreview/uires
            ${TARGET_DIR}/uipreview_uires
    COMMENT "Copying ${FILE} to ${TARGET_DIR}"
)

file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}" CMAKE_SOURCE_DIR_WIN)
file(TO_NATIVE_PATH "${TARGET_DIR}" TARGET_DIR_WIN)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
add_custom_command(TARGET copy_files PRE_BUILD
    COMMAND xcopy 
            ${CMAKE_SOURCE_DIR_WIN}\\depends\\soui4\\bin\\$(PlatformName)\\$(ConfigurationName)\\*.dll
            ${TARGET_DIR_WIN} /E /I /Y
    COMMENT "Copying ${FILE} to ${TARGET_DIR}"
)
else()
add_custom_command(TARGET copy_files PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/depends/soui4/lib/deb/*.so
            ${TARGET_DIR}
    COMMENT "Copying ${FILE} to ${TARGET_DIR}"
)
endif()
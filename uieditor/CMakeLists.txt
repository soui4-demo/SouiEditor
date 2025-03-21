#
# 1394020320@qq.com
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SOUI_INCLUDE}/config)
include_directories(${SOUI_INCLUDE}/components)
include_directories(${SOUI_INCLUDE}/utilities/include)
include_directories(${SOUI_INCLUDE}/SOUI/include)
include_directories(${SOUI_SRC_ROOT}/third-part/Scintilla/include)
include_directories(${SOUI_SRC_ROOT}/controls.extend)

set(CURRENT_SRCS
    DesignWnd.cpp
    helpapi.cpp
    MainDlg.cpp
    ResManger.cpp
    ScintillaWnd.cpp
    SImageBtnEx.cpp
    SImgCanvas.cpp
    SouiEditor.cpp
    SouiEditorApp.cpp
    SouiRealWndHandler.cpp
    SysdataMgr.cpp
    XmlEditor.cpp
    XmlParser.cpp
    SToolBar.cpp
    spugixml/pugixml.cpp
    Dialog/DlgAbout.cpp
    Dialog/DlgCreatePro.cpp
    Dialog/DlgInput.cpp
    Dialog/DlgNewLayout.cpp
    Dialog/DlgResMgr.cpp
    Dialog/DlgInsertXmlElement.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/SPropertyGrid.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/SPropertyItemBase.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Color.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Option.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Size.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Rect.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Text.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Group.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/colorpicker/ColourPopup.cpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/colorpicker/SColorPicker.cpp
)

set(CURRENT_HEADERS
    stdafx.h
    CDebug.h
    res/resource.h
    CmdLine.h
    DesignWnd.h
    FileHelper.h
    Global.h
    helpapi.h
    MainDlg.h
    ResManger.h
    resource.h
    DropTarget.h
    souidlgs.h
    ScintillaWnd.h
    SImageBtnEx.h
    SImgCanvas.h
    SouiEditorApp.h
    SouiRealWndHandler.h
    SysdataMgr.h
    xpm_icons.h
    XmlEditor.h
    XmlParser.h
    SToolBar.h
    spugixml/pugiconfig.hpp
    spugixml/pugixml.hpp
    Dialog/DlgAbout.h
    Dialog/DlgCreatePro.h
    Dialog/DlgInput.h
    Dialog/DlgNewLayout.h
    Dialog/DlgResMgr.h
    Dialog/DlgInsertXmlElement.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/colorpicker/ColourPopup.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/colorpicker/SColorPicker.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/colorpicker/Tooltipctrl.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/SPropertyEmbedWndHelper.hpp
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/SPropertyGrid.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/SPropertyItem-i.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/SPropertyItemBase.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Color.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Option.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Size.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Rect.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Text.h
    ${SOUI_SRC_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Group.h
    SImgCanvas.h
    ../ExtendCtrls/SCtrlsRegister.h
)

file(GLOB_RECURSE CURRENT_SOUIS  *.xml *.idx *.ico)
file(GLOB_RECURSE CURRENT_RC *.rc *.rc2)

source_group("SoUI Resouece" FILES ${CURRENT_SOUIS})
source_group("Resource Files" FILES ${CURRENT_RC})


add_executable(uieditor WIN32 ${CURRENT_HEADERS} ${CURRENT_SRCS} ${CURRENT_SOUIS} ${CURRENT_RC})

target_link_libraries(uieditor soui4 utilities4 Scintilla ExtendCtrls)
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
target_link_libraries(uieditor imm32)
else()
target_link_libraries(uieditor swinx)
endif()

target_precompile_headers(uieditor PRIVATE "stdafx.h")

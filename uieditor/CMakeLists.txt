#
# 1394020320@qq.com
#

include_directories(${SOUI_ROOT}/config)
include_directories(${SOUI_ROOT}/components)
include_directories(${SOUI_ROOT}/utilities/include)
include_directories(${SOUI_ROOT}/SOUI/include)
include_directories(${SOUI_ROOT}/third-part/Scintilla/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SOUI_ROOT}/controls.extend)

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
    SSwitch.cpp
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
    ${SOUI_ROOT}/controls.extend/propgrid/SPropertyGrid.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/SPropertyItemBase.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Color.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Option.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Size.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Rect.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Text.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Group.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/colorpicker/ColourPopup.cpp
    ${SOUI_ROOT}/controls.extend/propgrid/colorpicker/SColorPicker.cpp
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
    SSwitch.h
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
    ${SOUI_ROOT}/controls.extend/propgrid/colorpicker/ColourPopup.h
    ${SOUI_ROOT}/controls.extend/propgrid/colorpicker/SColorPicker.h
    ${SOUI_ROOT}/controls.extend/propgrid/colorpicker/Tooltipctrl.h
    ${SOUI_ROOT}/controls.extend/propgrid/SPropertyEmbedWndHelper.hpp
    ${SOUI_ROOT}/controls.extend/propgrid/SPropertyGrid.h
    ${SOUI_ROOT}/controls.extend/propgrid/SPropertyItem-i.h
    ${SOUI_ROOT}/controls.extend/propgrid/SPropertyItemBase.h
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Color.h
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Option.h
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Size.h
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Rect.h
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Text.h
    ${SOUI_ROOT}/controls.extend/propgrid/propitem/SPropertyItem-Group.h
    SImgCanvas.h
    ../ExtendCtrls/SCtrlsRegister.h
)

file(GLOB_RECURSE CURRENT_SOUIS  *.xml *.idx *.ico)
file(GLOB_RECURSE CURRENT_RC *.rc *.rc2)

source_group("SoUI Resouece" FILES ${CURRENT_SOUIS})
source_group("Resource Files" FILES ${CURRENT_RC})

#IF (CMAKE_CL_64)
#	link_directories(${SOUI_ROOT}/bin64)
#ELSE (CMAKE_CL_64)
#	link_directories(${SOUI_ROOT}/bin)
#ENDIF (CMAKE_CL_64)

add_executable(uieditor WIN32 ${CURRENT_HEADERS} ${CURRENT_SRCS} ${CURRENT_SOUIS} ${CURRENT_RC})

#add_dependencies(uieditor soui-sys-resource)
#target_link_libraries(uieditor utilities soui ${COM_LIBS})
target_link_libraries(uieditor
    debug soui4d optimized soui4
    debug utilities4d optimized utilities4
    debug Scintillad optimized Scintilla
    debug ExtendCtrlsd optimized ExtendCtrls
    imm32
)

set(CMAKE_DEBUG_POSTFIX "d")

target_precompile_headers(uieditor PRIVATE "stdafx.h")
set_target_properties(uieditor PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

set_target_properties (uieditor PROPERTIES
    FOLDER demos
)

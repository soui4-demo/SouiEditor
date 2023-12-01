#
# 1394020320@qq.com
#

include_directories(${SOUI_ROOT}/config)
include_directories(${SOUI_ROOT}/components)
include_directories(${SOUI_ROOT}/utilities/include)
include_directories(${SOUI_ROOT}/SOUI/include)
include_directories(${SOUI_ROOT}/controls.extend)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CURRENT_SRCS
    SCtrlsRegister.cpp
    ${SOUI_ROOT}/controls.extend/image3d/3dlib.cpp
    ${SOUI_ROOT}/controls.extend/image3d/3dmatrix.cpp
    ${SOUI_ROOT}/controls.extend/image3d/3dtransform.cpp
    ${SOUI_ROOT}/controls.extend/ExtendSkins.cpp
    ${SOUI_ROOT}/controls.extend/SButtonEx.cpp
    ${SOUI_ROOT}/controls.extend/SChromeTabCtrl.cpp
    ${SOUI_ROOT}/controls.extend/SFreeMoveWindow.cpp
    ${SOUI_ROOT}/controls.extend/gif/SGifPlayer.cpp
    ${SOUI_ROOT}/controls.extend/SImageMaskWnd.cpp
    ${SOUI_ROOT}/controls.extend/gif/SSkinAPNG.cpp
    ${SOUI_ROOT}/controls.extend/gif/SSkinGif.cpp
    ${SOUI_ROOT}/controls.extend/STabCtrl2.cpp
    ${SOUI_ROOT}/controls.extend/SText.cpp
    ${SOUI_ROOT}/controls.extend/STurn3DView.cpp
    ${SOUI_ROOT}/controls.extend/SScrollText.cpp
    ${SOUI_ROOT}/controls.extend/SIPAddressCtrl.cpp
    ${SOUI_ROOT}/controls.extend/SListCtrlEx.cpp
    ${SOUI_ROOT}/controls.extend/SRatingBar.cpp
    ${SOUI_ROOT}/controls.extend/SRadioBox2.cpp
    ${SOUI_ROOT}/controls.extend/SMcListViewEx/SHeaderCtrlEx.cpp
    ${SOUI_ROOT}/controls.extend/SGroupList.cpp
    ${SOUI_ROOT}/controls.extend/SHexEdit.cpp
    ${SOUI_ROOT}/controls.extend/SByteArray.cpp
)

set(CURRENT_HEADERS
    stdafx.h
    SCtrlsRegister.h
    ${SOUI_ROOT}/controls.extend/image3d/3dlib.h
    ${SOUI_ROOT}/controls.extend/image3d/3dmatrix.h
    ${SOUI_ROOT}/controls.extend/image3d/3dTransform.h
    ${SOUI_ROOT}/controls.extend/ExtendSkins.h
    ${SOUI_ROOT}/controls.extend/image3d/PerspectiveTransform.h
    ${SOUI_ROOT}/controls.extend/SButtonEx.h
    ${SOUI_ROOT}/controls.extend/SChromeTabCtrl.h
    ${SOUI_ROOT}/controls.extend/SFreeMoveWindow.h
    ${SOUI_ROOT}/controls.extend/gif/SGifPlayer.h
    ${SOUI_ROOT}/controls.extend/SImageMaskWnd.h
    ${SOUI_ROOT}/controls.extend/gif/SSkinAPNG.h
    ${SOUI_ROOT}/controls.extend/gif/SSkinGif.h
    ${SOUI_ROOT}/controls.extend/STabCtrl2.h
    ${SOUI_ROOT}/controls.extend/SText.h
    ${SOUI_ROOT}/controls.extend/STurn3DView.h
    ${SOUI_ROOT}/controls.extend/SScrollText.h
    ${SOUI_ROOT}/controls.extend/SIPAddressCtrl.h
    ${SOUI_ROOT}/controls.extend/SListCtrlEx.h
    ${SOUI_ROOT}/controls.extend/SRatingBar.h
    ${SOUI_ROOT}/controls.extend/SRadioBox2.h
    ${SOUI_ROOT}/controls.extend/SMcListViewEx/SHeaderCtrlEx.h
    ${SOUI_ROOT}/controls.extend/SGroupList.h
    ${SOUI_ROOT}/controls.extend/SHexEdit.h
    ${SOUI_ROOT}/controls.extend/SByteArray.h
)

#source_group("Header Files" FILES ${CURRENT_HEADERS})
#source_group("Source Files" FILES ${CURRENT_SRCS})

add_library(ExtendCtrls STATIC ${CURRENT_HEADERS} ${CURRENT_SRCS})

set(CMAKE_DEBUG_POSTFIX "d")

target_precompile_headers(ExtendCtrls PRIVATE "stdafx.h")
set_target_properties(ExtendCtrls PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

set_target_properties (ExtendCtrls PROPERTIES
    FOLDER demos
)

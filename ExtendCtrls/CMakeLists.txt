#
# 1394020320@qq.com
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SOUI_INCLUDE}/config)
include_directories(${SOUI_INCLUDE}/components)
include_directories(${SOUI_INCLUDE}/utilities/include)
include_directories(${SOUI_INCLUDE}/SOUI/include)
include_directories(${SOUI_SRC_ROOT}/controls.extend)


set(CURRENT_SRCS
    SCtrlsRegister.cpp
    ${SOUI_SRC_ROOT}/controls.extend/image3d/3dlib.cpp
    ${SOUI_SRC_ROOT}/controls.extend/image3d/3dmatrix.cpp
    ${SOUI_SRC_ROOT}/controls.extend/image3d/3dtransform.cpp
    ${SOUI_SRC_ROOT}/controls.extend/ExtendSkins.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SButtonEx.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SChromeTabCtrl.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SFreeMoveWindow.cpp
    ${SOUI_SRC_ROOT}/controls.extend/gif/SGifPlayer.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SImageMaskWnd.cpp
    ${SOUI_SRC_ROOT}/controls.extend/gif/SSkinAni.cpp
    ${SOUI_SRC_ROOT}/controls.extend/STabCtrl2.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SText.cpp
    ${SOUI_SRC_ROOT}/controls.extend/STurn3DView.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SScrollText.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SIPAddressCtrl.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SListCtrlEx.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SRatingBar.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SRadioBox2.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SMcListViewEx/SHeaderCtrlEx.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SGroupList.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SHexEdit.cpp
    ${SOUI_SRC_ROOT}/controls.extend/SByteArray.cpp
)

set(CURRENT_HEADERS
    stdafx.h
    SCtrlsRegister.h
    ${SOUI_SRC_ROOT}/controls.extend/image3d/3dlib.h
    ${SOUI_SRC_ROOT}/controls.extend/image3d/3dmatrix.h
    ${SOUI_SRC_ROOT}/controls.extend/image3d/3dTransform.h
    ${SOUI_SRC_ROOT}/controls.extend/ExtendSkins.h
    ${SOUI_SRC_ROOT}/controls.extend/image3d/PerspectiveTransform.h
    ${SOUI_SRC_ROOT}/controls.extend/SButtonEx.h
    ${SOUI_SRC_ROOT}/controls.extend/SChromeTabCtrl.h
    ${SOUI_SRC_ROOT}/controls.extend/SFreeMoveWindow.h
    ${SOUI_SRC_ROOT}/controls.extend/gif/SGifPlayer.h
    ${SOUI_SRC_ROOT}/controls.extend/SImageMaskWnd.h
    ${SOUI_SRC_ROOT}/controls.extend/gif/SSkinAni.h
    ${SOUI_SRC_ROOT}/controls.extend/STabCtrl2.h
    ${SOUI_SRC_ROOT}/controls.extend/SText.h
    ${SOUI_SRC_ROOT}/controls.extend/STurn3DView.h
    ${SOUI_SRC_ROOT}/controls.extend/SScrollText.h
    ${SOUI_SRC_ROOT}/controls.extend/SIPAddressCtrl.h
    ${SOUI_SRC_ROOT}/controls.extend/SListCtrlEx.h
    ${SOUI_SRC_ROOT}/controls.extend/SRatingBar.h
    ${SOUI_SRC_ROOT}/controls.extend/SRadioBox2.h
    ${SOUI_SRC_ROOT}/controls.extend/SMcListViewEx/SHeaderCtrlEx.h
    ${SOUI_SRC_ROOT}/controls.extend/SGroupList.h
    ${SOUI_SRC_ROOT}/controls.extend/SHexEdit.h
    ${SOUI_SRC_ROOT}/controls.extend/SByteArray.h
)

add_library(ExtendCtrls STATIC ${CURRENT_HEADERS} ${CURRENT_SRCS})


target_precompile_headers(ExtendCtrls PRIVATE "stdafx.h")

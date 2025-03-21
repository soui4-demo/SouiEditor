#
# 1394020320@qq.com
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SOUI_INCLUDE}/config)
include_directories(${SOUI_INCLUDE}/components)
include_directories(${SOUI_INCLUDE}/utilities/include)
include_directories(${SOUI_INCLUDE}/SOUI/include)
include_directories(controls.extend)


set(CURRENT_SRCS
    SCtrlsRegister.cpp
    controls.extend/image3d/3dlib.cpp
    controls.extend/image3d/3dmatrix.cpp
    controls.extend/image3d/3dtransform.cpp
    controls.extend/ExtendSkins.cpp
    controls.extend/SButtonEx.cpp
    controls.extend/SChromeTabCtrl.cpp
    controls.extend/SFreeMoveWindow.cpp
    controls.extend/gif/SGifPlayer.cpp
    controls.extend/SImageMaskWnd.cpp
    controls.extend/gif/SSkinAni.cpp
    controls.extend/STabCtrl2.cpp
    controls.extend/SText.cpp
    controls.extend/STurn3DView.cpp
    controls.extend/SScrollText.cpp
    controls.extend/SIPAddressCtrl.cpp
    controls.extend/SListCtrlEx.cpp
    controls.extend/SRatingBar.cpp
    controls.extend/SRadioBox2.cpp
    controls.extend/SMcListViewEx/SHeaderCtrlEx.cpp
    controls.extend/SGroupList.cpp
    controls.extend/SHexEdit.cpp
    controls.extend/SByteArray.cpp
)

set(CURRENT_HEADERS
    stdafx.h
    SCtrlsRegister.h
    controls.extend/image3d/3dlib.h
    controls.extend/image3d/3dmatrix.h
    controls.extend/image3d/3dTransform.h
    controls.extend/ExtendSkins.h
    controls.extend/image3d/PerspectiveTransform.h
    controls.extend/SButtonEx.h
    controls.extend/SChromeTabCtrl.h
    controls.extend/SFreeMoveWindow.h
    controls.extend/gif/SGifPlayer.h
    controls.extend/SImageMaskWnd.h
    controls.extend/gif/SSkinAni.h
    controls.extend/STabCtrl2.h
    controls.extend/SText.h
    controls.extend/STurn3DView.h
    controls.extend/SScrollText.h
    controls.extend/SIPAddressCtrl.h
    controls.extend/SListCtrlEx.h
    controls.extend/SRatingBar.h
    controls.extend/SRadioBox2.h
    controls.extend/SMcListViewEx/SHeaderCtrlEx.h
    controls.extend/SGroupList.h
    controls.extend/SHexEdit.h
    controls.extend/SByteArray.h
)

add_library(ExtendCtrls STATIC ${CURRENT_HEADERS} ${CURRENT_SRCS})

if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
target_compile_options(ExtendCtrls PRIVATE -fPIC)
target_link_libraries(ExtendCtrls swinx)
endif()
target_precompile_headers(ExtendCtrls PRIVATE "stdafx.h")

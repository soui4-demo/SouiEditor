﻿//////////////////////////////////////////////////////////////////////////
//   File Name: Dui3DView.h
// Description: SImg3DView
//     Creator: ZhangZhiBin QQ->276883782
//     Version: 2014.02.06 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "image3d/3dTransform.h"
#include <event/SEvents.h>

namespace SOUI
{
DEF_EVT_EXT(EventTurn3d, EVT_EXTERNAL_BEGIN + 4000, { BOOL bTurn2Front_; });

class STurn3dView : public SWindow {
    DEF_SOBJECT(SWindow, L"Turn3dView")
  public:
    STurn3dView();
    virtual ~STurn3dView();

    BOOL Turn(SWindow *pWndFront, SWindow *pWndBack, BOOL bTurn2Front = TRUE);

    SOUI_ATTRS_BEGIN()
    ATTR_INT(L"zStep", m_nZStep, FALSE)
    ATTR_INT(L"yStep", m_nYStep, FALSE)
    SOUI_ATTRS_END()

  protected:
    void OnTimer(char idEvent);
    void OnPaint(IRenderTarget *pRT);

    SOUI_MSG_MAP_BEGIN()
    MSG_WM_PAINT_EX(OnPaint)
    MSG_WM_TIMER_EX(OnTimer)
    SOUI_MSG_MAP_END()
  protected:
    int m_nZStep;       // z轴的每一步距离
    int m_nYStep;       //每次动画绕Y轴旋转m_nYStep角度
    BOOL m_bTurn2Front; //翻转方向

    IMAGE3D::PARAM3DTRANSFORM m_3dparam;
    SAutoRefPtr<IBitmapS> m_bmpBefore;
    SAutoRefPtr<IBitmapS> m_bmpAfter;
    SAutoRefPtr<IBitmapS> m_bmpTrans;

    int m_nFrameIndex; //翻转到第几帧
    BOOL m_bTurning;   //正在翻转
};

} // namespace SOUI
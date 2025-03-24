﻿#include "stdafx.h"
#include "TipWnd.h"

#define TIMER_END_TIP 100

namespace SOUI
{

static SStringT s_TipLayout;

STipWnd::STipWnd(const SStringT &strLayout)
    : SHostWnd(strLayout)
{
}

STipWnd::~STipWnd()
{
}

void STipWnd::OnFinalMessage(HWND hWnd)
{
    __baseCls::OnFinalMessage(hWnd);
    delete this;
}

void STipWnd::SetTip(const SStringT &strTip)
{
    SWindow *pText = FindChildByName(L"txt_tip");
    pText->SetWindowText(strTip);
}

void STipWnd::SetLayout(LPCTSTR pszLayout)
{
    s_TipLayout = pszLayout;
}

void STipWnd::ShowTip(int x, int y, AnchorType at, const SStringT &strTip)
{
    STipWnd *pTipWnd = new STipWnd(s_TipLayout);
    pTipWnd->m_ptAnchor.x = x;
    pTipWnd->m_ptAnchor.y = y;
    pTipWnd->m_anchorType = at;
    pTipWnd->Create(0);
    pTipWnd->SetTip(strTip);
    pTipWnd->SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0,
                          SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    pTipWnd->SetTimer(TIMER_END_TIP, 3000);
}

void STipWnd::OnWindowPosChanging(LPWINDOWPOS lpWndPos)
{
    if (!(lpWndPos->flags & SWP_NOSIZE))
    { //窗口大小改变，根据设置的anchor移动位置
        switch (m_anchorType)
        {
        case AT_LEFT_TOP:
            lpWndPos->x = m_ptAnchor.x;
            lpWndPos->y = m_ptAnchor.y;
            break;
        case AT_LEFT_BOTTOM:
            lpWndPos->x = m_ptAnchor.x;
            lpWndPos->y = m_ptAnchor.y - lpWndPos->cy;
            break;
        case AT_RIGHT_TOP:
            lpWndPos->x = m_ptAnchor.x - lpWndPos->cx;
            lpWndPos->y = m_ptAnchor.y;
            break;
        case AT_RIGHT_BOTTOM:
            lpWndPos->x = m_ptAnchor.x - lpWndPos->cx;
            lpWndPos->y = m_ptAnchor.y - lpWndPos->cy;
            break;
        }
        lpWndPos->flags &= ~SWP_NOMOVE;
    }
}

void STipWnd::OnTimer(UINT_PTR timerID)
{
    SetMsgHandled(FALSE);
    if (timerID == TIMER_END_TIP)
    {
        SNativeWnd::DestroyWindow();
    }
}
} // namespace SOUI

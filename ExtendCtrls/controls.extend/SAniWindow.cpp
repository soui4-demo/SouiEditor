#include "stdafx.h"
#include "SAniWindow.h"
#include <animation/SInterpolatorImpl.h>
namespace SOUI
{
SAniWindow::SAniWindow(void)
    : m_nSteps(20)
    , m_iAniStep(0)
    , m_aniMode(AM_NONE)
    , m_bSaveSize(true)
    , m_bEnableAni(true)
{
    m_bClipClient = TRUE;
    m_bDisplay = FALSE;
    m_aniInterpolator.Attach(
        SApplication::getSingleton().CreateInterpolatorByName(SLinearInterpolator::GetClassName()));
}

SAniWindow::~SAniWindow(void)
{
}

void SAniWindow::OnNextFrame()
{
    SASSERT(m_iAniStep < m_nSteps);
    SASSERT(m_aniMode != AM_NONE);
    m_iAniStep++;
    m_layoutParamTmp->SetSpecifiedSize(Vert, SLayoutSize((float)GetHeight(), SLayoutSize::px));
    RequestRelayout();
    Update();
    if (m_iAniStep == m_nSteps)
    {
        if (m_aniMode == AM_HIDE)
        {
            m_aniMode = AM_NONE;
            m_iAniStep = 0;
            GetContainer()->UnregisterTimelineHandler(this);
            Invalidate();
            SWindow::OnShowWindow(false, NormalShow);
        }
        else
        { // animating show finish.
            m_aniMode = AM_NONE;
            m_iAniStep = 0;
            GetContainer()->UnregisterTimelineHandler(this);
        }
        m_bSaveSize = true;
    }
}

void SAniWindow::OnShowWindow(BOOL bShow, UINT nStatus)
{
    if (nStatus == NormalShow && m_bEnableAni && m_szWnd.cx > 0 && m_szWnd.cy > 0)
    {
        if (m_aniMode != AM_NONE)
        {
            if (bShow)
            {
                m_aniMode = AM_SHOW;
            }
            else
            {
                m_aniMode = AM_HIDE;
            }
            return;
        }
        if (bShow)
        {
            SWindow::OnShowWindow(bShow, nStatus);
            // start animator
            m_aniMode = AM_SHOW;
        }
        else
        {
            m_aniMode = AM_HIDE;
        }
        m_bSaveSize = false;
        m_iAniStep = 0;
        GetContainer()->RegisterTimelineHandler(this);
        m_layoutParamTmp->SetSpecifiedSize(Vert, SLayoutSize((float)GetHeight(), SLayoutSize::px));
    }
    else
    {
        SWindow::OnShowWindow(bShow, nStatus);
    }
}

int SAniWindow::OnCreate(void *)
{
    __baseCls::OnCreate(NULL);
    m_layoutParamTmp.Attach(__baseCls::GetLayoutParam()->Clone());

    return 0;
}

BOOL SAniWindow::OnRelayout(const CRect &rcWnd)
{
    BOOL bRet = __baseCls::OnRelayout(rcWnd);
    if (m_bSaveSize)
    {
        m_szWnd = rcWnd.Size();
    }
    return bRet;
}

ILayoutParam *SAniWindow::GetLayoutParam() const
{
    if (m_aniMode == AM_NONE)
        return __baseCls::GetLayoutParam();
    else
        return m_layoutParamTmp;
}

int SAniWindow::GetHeight() const
{
    SASSERT(m_aniMode != AM_NONE);
    int nHei = m_szWnd.cy;
    nHei = (int)(m_aniInterpolator->getInterpolation(m_iAniStep * 1.f / m_nSteps) * nHei);
    if (m_aniMode == AM_HIDE)
        nHei = m_szWnd.cy - nHei;
    return nHei;
}

void SAniWindow::EnableAnimate(bool bEnable)
{
    m_bEnableAni = bEnable;
}

} // namespace SOUI

#pragma once

namespace SOUI
{

class SAniWindow
    : public SWindow
    , protected ITimelineHandler {
    DEF_SOBJECT(SWindow, L"AniWindow")
  public:
    SAniWindow(void);
    ~SAniWindow(void);

    void EnableAnimate(bool bEnable);

  protected:
    STDMETHOD_(void, OnNextFrame)(THIS_) OVERRIDE;
    STDMETHOD_(ILayoutParam *, GetLayoutParam)(THIS) SCONST OVERRIDE;

    virtual BOOL OnRelayout(const CRect &rcWnd) OVERRIDE;

    int GetHeight() const;

  protected:
    void OnShowWindow(BOOL bShow, UINT nStatus);
    int OnCreate(void *);
    SOUI_MSG_MAP_BEGIN()
    MSG_WM_CREATE(OnCreate)
    MSG_WM_SHOWWINDOW(OnShowWindow)
    SOUI_MSG_MAP_END()

  public:
    SOUI_ATTRS_BEGIN()
    ATTR_INTERPOLATOR(L"Interpolator", m_aniInterpolator, FALSE)
    ATTR_CHAIN_PTR(m_aniInterpolator, 0) // chain attributes to interpolator
    ATTR_INT(L"steps", m_nSteps, FALSE)
    SOUI_ATTRS_END()
  protected:
    enum AniMode
    {
        AM_NONE = 0,
        AM_SHOW,
        AM_HIDE,
    };
    SAutoRefPtr<IInterpolator> m_aniInterpolator;
    int m_nSteps;
    int m_iAniStep;
    CSize m_szWnd;

    AniMode m_aniMode;
    bool m_bSaveSize;
    SAutoRefPtr<ILayoutParam> m_layoutParamTmp;
    bool m_bEnableAni;
};

} // namespace SOUI

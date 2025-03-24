#pragma once

namespace SOUI
{
class STipWnd : public SHostWnd {
	typedef SHostWnd __baseCls;
  public:
    STipWnd(const SStringT &strLayout);
    ~STipWnd();

    enum AnchorType
    {
        AT_LEFT_TOP,
        AT_LEFT_BOTTOM,
        AT_RIGHT_TOP,
        AT_RIGHT_BOTTOM,
    };
    static void SetLayout(LPCTSTR pszLayout);
    static void ShowTip(int x, int y, AnchorType at, const SStringT &strTip);

  protected:
    virtual void OnFinalMessage(HWND hWnd);

    void SetTip(const SStringT &strTip);

    void OnWindowPosChanging(LPWINDOWPOS lpWndPos);

    void OnTimer(UINT_PTR timerID);
    BEGIN_MSG_MAP_EX(STipWnd)
    MSG_WM_TIMER(OnTimer)
    MSG_WM_WINDOWPOSCHANGING(OnWindowPosChanging)
    CHAIN_MSG_MAP(SHostWnd)
    END_MSG_MAP()

    CPoint m_ptAnchor;
    AnchorType m_anchorType;
};
} // namespace SOUI

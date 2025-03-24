#pragma once

#include <core/SWnd.h>
#include "SAnimator.h"

namespace SOUI
{

#define EVT_CHROMETAB_BEGIN      (EVT_EXTERNAL_BEGIN + 400)
#define EVT_CHROMETAB_NEW        (EVT_CHROMETAB_BEGIN + 0)
#define EVT_CHROMETAB_CLOSE      (EVT_CHROMETAB_BEGIN + 1)
#define EVT_CHROMETAB_SELCHANGED (EVT_CHROMETAB_BEGIN + 2)
#define EVT_CHROMETAB_DBCLICK    (EVT_CHROMETAB_BEGIN + 3)
class SChromeTabCtrl;
//////////////////////////////////////////////////////////////////////////
// SChromeTab
class SChromeTab
    : public SWindow
    , public SAnimator {
    DEF_SOBJECT(SWindow, L"chromeTab")
    friend class SChromeTabCtrl;

public:
    SChromeTab(SChromeTabCtrl *pHost);

    void MoveTo(const CRect &rcEnd);
    BOOL IsDragable();

    SOUI_ATTRS_BEGIN()
    ATTR_INT(L"allowClose", m_bAllowClose, FALSE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
    MSG_WM_MOUSEMOVE(OnMouseMove)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_LBUTTONUP(OnLButtonUp)
    MSG_WM_LBUTTONDBLCLK(OnLButtonDbClick)
    SOUI_MSG_MAP_END()

  protected:
    virtual void OnAnimatorState(int percent);
    virtual void WINAPI OnFinalRelease()
    {
        delete this;
    }
    void OnMouseMove(UINT nFlags, CPoint pt);
    void OnLButtonUp(UINT nFlags, CPoint pt);
    void OnLButtonDown(UINT nFlags, CPoint pt);
    void OnLButtonDbClick(UINT nFlags, CPoint pt);

    CRect m_rcBegin, m_rcEnd;
    BOOL m_bAllowClose;
    CPoint m_ptDrag;
    int m_iOrder;
    int m_iTabIndex;
    bool m_bDrag;
    SChromeTabCtrl *m_pHost;
};

DEF_EVT_EXT(EventChromeTabNew, EVT_CHROMETAB_NEW, {
    SWindow *pNewTab;
    int iNewTab;
});

DEF_EVT_EXT(EventChromeTabClose, EVT_CHROMETAB_CLOSE, {
    SWindow *pCloseTab;
    int iCloseTab;
});

DEF_EVT_EXT(EventChromeTabSelChanged, EVT_CHROMETAB_SELCHANGED, {
    int iOldSel;
    int iNewSel;
});

DEF_EVT_EXT(EventChromeTabDbClick, EVT_CHROMETAB_DBCLICK, {
    int iTabIndex;
    int iOrder;
});

class SChromeTabCtrl
    : public SWindow
    , public ITimelineHandler {
    DEF_SOBJECT(SWindow, L"chromeTabCtrl")
    friend class SChromeTab;

  public:
    enum TABDIR
    {
        TDIR_HORZ,
        TDIR_VERT,
    };

    SChromeTabCtrl(void);
    ~SChromeTabCtrl(void);

    BOOL InsertTab(LPCTSTR pszTitle, int iPos = -1);

    BOOL RemoveTab(int iTab);
    BOOL RemoveTab(SChromeTab *pTab);

    void SetCurSel(int iTab, bool bSendNotify = true);

    int GetCurSel() const;

    int GetTabIndex(int iTab) const;
    int GetTabOrder(int iTabIndex) const;

    int GetTabCount() const;
    SWindow *GetTabWindow(int iPos);

  protected:
    int ChangeTabPos(SChromeTab *pCurMove, CPoint ptCur);

    virtual BOOL CreateChildren(SXmlNode xmlNode);

    STDMETHOD_(void, UpdateChildrenPosition)(THIS) OVERRIDE;

    STDMETHOD_(void, OnNextFrame)(THIS_) OVERRIDE;
    void OnContainerChanged(ISwndContainer *pOldContainer, ISwndContainer *pNewContainer);

    BOOL OnBtnNewClick(IEvtArgs *pEvt);
    BOOL OnBtnCloseTabClick(IEvtArgs *pEvt);
    BOOL OnTabClick(IEvtArgs *pEvt);

    int OnCreate(LPVOID);
    void OnDestroy();

    SOUI_MSG_MAP_BEGIN()
    MSG_WM_CREATE(OnCreate)
    MSG_WM_DESTROY(OnDestroy)
    SOUI_MSG_MAP_END()

    SOUI_ATTRS_BEGIN()
    ATTR_INT(L"tabDesiredSize", m_nDesiredSize, FALSE)
    ATTR_INT(L"enableDrag", m_bEnableDrag, FALSE)
    ATTR_ENUM_BEGIN(L"tabAlign", TABDIR, FALSE)
    ATTR_ENUM_VALUE(L"vertical", TDIR_VERT)
    ATTR_ENUM_VALUE(L"horizontal", TDIR_HORZ)
    ATTR_ENUM_END(m_tabAlign)
    SOUI_ATTRS_END()

    int m_nDesiredSize;
    TABDIR m_tabAlign;
    BOOL m_bEnableDrag;

    SArray<SChromeTab *> m_lstTabOrder;

    SChromeTab *m_pBtnNew;
    SChromeTab *m_pSelTab;

    SXmlDoc m_xmlStyle;
};

} // namespace SOUI

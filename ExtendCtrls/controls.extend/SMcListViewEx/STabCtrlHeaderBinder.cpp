#include "stdafx.h"
#include "STabCtrlHeaderBinder.h"
namespace SOUI
{

STabCtrlHeaderBinder::STabCtrlHeaderBinder(STabCtrl *_host)
    : m_pTabHost(_host)
{
    if (m_pTabHost)
    {
        m_pTabHost->GetEventSet()->subscribeEvent(
            EventTabSelChanged::EventID, Subscriber(&STabCtrlHeaderBinder::TabSelChanged, this));
    }
}

STabCtrlHeaderBinder::~STabCtrlHeaderBinder()
{
}

void STabCtrlHeaderBinder::BindHost(STabCtrl *_host)
{
    SASSERT(_host);
    if (m_pTabHost)
    {
        m_lstPages.RemoveAll();
        m_pTabHost->GetEventSet()->unsubscribeEvent(
            EventTabSelChanged::EventID, Subscriber(&STabCtrlHeaderBinder::TabSelChanged, this));
    }
    m_pTabHost = _host;
    if (m_pTabHost)
    {
        m_pTabHost->GetEventSet()->subscribeEvent(
            EventTabSelChanged::EventID, Subscriber(&STabCtrlHeaderBinder::TabSelChanged, this));
    }
}

void STabCtrlHeaderBinder::Bind(SWindow *_pWnd, int _idx, DWORD _evtcode)
{
    SASSERT(_pWnd);
    if (_pWnd)
    {
        if (_pWnd->GetEventSet()->subscribeEvent(
                _evtcode, Subscriber(&STabCtrlHeaderBinder::EvtHander, this)))
            m_lstPages[_pWnd] = _idx;
        if (m_pTabHost->GetCurSel() == _idx)
            _pWnd->ModifyState(WndState_PushDown, 0, TRUE);
    }
}

BOOL STabCtrlHeaderBinder::EvtHander(IEvtArgs *e)
{
    if (SMap<SWindow *, int>::CPair *pair = m_lstPages.Lookup((SWindow *)e->Sender()))
    {
        // m_pTabHost->GetEventSet()->setMutedState(true);
        m_pTabHost->SetCurSel(pair->m_value);
        // pair->m_key->SetCheck(TRUE);
        // m_pTabHost->GetEventSet()->setMutedState(false);
        return TRUE;
    }
    return FALSE;
}
BOOL STabCtrlHeaderBinder::TabSelChanged(EventTabSelChanged *evt_sel)
{
    SPOSITION pos = m_lstPages.GetStartPosition();
    SMap<SWindow *, int>::CPair *pair;
    while (pos)
    {
        pair = m_lstPages.GetNext(pos);
        if (pair->m_value == (int)evt_sel->uNewSel)
        {
            pair->m_key->ModifyState(WndState_PushDown, 0, TRUE);
            // pair->m_key->SetCheck(TRUE);
            pair->m_key->SetFocus();
        }
        else if (pair->m_value == (int)evt_sel->uOldSel)
        {
            pair->m_key->ModifyState(0, WndState_PushDown, TRUE);
            // pair->m_key->SetCheck(FALSE);
        }
    }
    return FALSE;
}
} // namespace SOUI
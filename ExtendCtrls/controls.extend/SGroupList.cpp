﻿#include "stdafx.h"
#include "SGroupList.h"

namespace SOUI
{
using namespace GroupListStuct;

SGroupList::SGroupList()
    : m_pSelectedItem(NULL)
{
    GetEventSet()->addEvent(EVENTID(EventGroupListInitGroup));
    GetEventSet()->addEvent(EVENTID(EventGroupListInitItem));
    GetEventSet()->addEvent(EVENTID(EventGroupListItemCheck));
    GetEventSet()->addEvent(EVENTID(EventGroupStateChanged));
}

SGroupList::~SGroupList()
{
}

BOOL SGroupList::CreateChildren(SXmlNode xmlNode)
{
    SXmlNode groupTemplate = xmlNode.child(L"groupTemplate");
    SXmlNode itemTemplate = xmlNode.child(L"itemTemplate");
    SASSERT(groupTemplate && itemTemplate);
    m_groupTemplate = m_xmlDoc.root().append_copy(groupTemplate);
    m_itemTemplate = m_xmlDoc.root().append_copy(itemTemplate);

    SXmlNode xmlData = xmlNode.child(L"data");
    if (xmlData)
    {
        SXmlNode xmlGroup = xmlData.child(L"group");
        while (xmlGroup)
        {
            SStringT strText = S_CW2T(xmlGroup.attribute(L"text").as_string());
            SStringW strName = xmlGroup.attribute(L"name").as_string();
            SStringW strTip = xmlGroup.attribute(L"tip").as_string();
            SWindow *pGroup
                = InsertGroup(-1, strName, strText, xmlGroup.attribute(L"icon").as_int(),
                              xmlGroup.attribute(L"id").as_int(), strTip);
            SXmlNode xmlItem = xmlGroup.child(L"item");
            while (xmlItem)
            {
                SStringT strText = S_CW2T(xmlItem.attribute(L"text").as_string());
                SStringW strName = xmlItem.attribute(L"name").as_string();
                SStringW strTip = xmlItem.attribute(L"tip").as_string();
                InsertItem(pGroup, -1, strName, strText, xmlItem.attribute(L"icon").as_int(),
                           xmlItem.attribute(L"id").as_int(), strTip);
                xmlItem = xmlItem.next_sibling(L"item");
            }
            xmlGroup = xmlGroup.next_sibling(L"group");
        }
    }
    return TRUE;
}

void SGroupList::OnDestroy()
{
    SWindow *pGroup = GetWindow(GSW_FIRSTCHILD);
    while (pGroup)
    {
        GroupInfo *pGroupInfo = (GroupInfo *)pGroup->GetUserData();
        delete pGroupInfo;
        SWindow *pContainer = pGroup->FindChildByName(L"container");
        SASSERT(pContainer);
        SWindow *pItem = pContainer->GetWindow(GSW_FIRSTCHILD);
        while (pItem)
        {
            ItemInfo *pItemInfo = (ItemInfo *)pItem->GetUserData();
            delete pItemInfo;
            pItem = pItem->GetWindow(GSW_NEXTSIBLING);
        }
        pGroup = pGroup->GetWindow(GSW_NEXTSIBLING);
    }
    __baseCls::OnDestroy();
}

bool SGroupList::SelectPage(int nID)
{
    SWindow *pItem = FindChildByID(nID);
    if (!pItem)
        return false;
    EventCmd evt(pItem);
    OnItemClick(&evt);
    return true;
}

SWindow *SGroupList::InsertGroup(int iGroup,
                                 const SStringW &name,
                                 const SStringT &text,
                                 int iIcon,
                                 int nID,
                                 const SStringW &strTip)
{
    SWindow *pInsertAfter = ICWND_FIRST;
    if (iGroup < 0)
    {
        pInsertAfter = ICWND_LAST;
    }
    else
    {
        for (int i = 0; i < iGroup; i++)
        {
            if (pInsertAfter == ICWND_FIRST)
                pInsertAfter = GetWindow(GSW_FIRSTCHILD);
            else
                pInsertAfter = pInsertAfter->GetWindow(GSW_NEXTSIBLING);
            if (!pInsertAfter)
            {
                pInsertAfter = ICWND_LAST;
                break;
            }
        }
    }

    SWindow *pGroup = CreateChildByName(
        m_groupTemplate.attribute(L"class_name").as_string(L"window"));
    SASSERT(pGroup);
    InsertChild(pGroup, pInsertAfter);
    pGroup->InitFromXml(&m_groupTemplate);
    pGroup->SetName(name);
    pGroup->SetID(nID);
    GroupInfo *pItemInfo = new GroupInfo;
    pItemInfo->bCollapsed = false;
    pItemInfo->strText = text;
    pItemInfo->strName = name;
    pItemInfo->iIcon = iIcon;
    pItemInfo->id = nID;
    pGroup->SetUserData((ULONG_PTR)pItemInfo);

    pGroup->FindChildByName(L"container")->SetVisible(!pItemInfo->bCollapsed);

    EventGroupListInitGroup evt(this);
    evt.pItem = pGroup->FindChildByName(L"title");
    evt.pGroupInfo = pItemInfo;
    evt.pItem->SetAttribute(L"tip", strTip);
    FireEvent(evt);

    evt.pItem->GetEventSet()->subscribeEvent(EventCmd::EventID,
                                             Subscriber(&SGroupList::OnGroupClick, this));
    RequestRelayout();

    return pGroup;
}

SWindow *SGroupList::InsertItem(SWindow *pGroup,
                                int iItem,
                                const SStringW &name,
                                const SStringT &text,
                                int iIcon,
                                int nID,
                                const SStringW &strTip)
{
    SWindow *pItemContainer = pGroup->FindChildByName(L"container");

    SWindow *pInsertAfter = ICWND_FIRST;
    if (iItem < 0)
    {
        pInsertAfter = ICWND_LAST;
    }
    else
    {
        for (int i = 0; i < iItem; i++)
        {
            if (pInsertAfter == ICWND_FIRST)
                pInsertAfter = pItemContainer->GetWindow(GSW_FIRSTCHILD);
            else
                pInsertAfter = pInsertAfter->GetWindow(GSW_NEXTSIBLING);
            if (!pInsertAfter)
            {
                pInsertAfter = ICWND_LAST;
                break;
            }
        }
    }
    SWindow *pItem = CreateChildByName(
        m_itemTemplate.attribute(L"class_name").as_string());
    SASSERT(pItem);
    pItemContainer->InsertChild(pItem, pInsertAfter);
    pItem->InitFromXml(&m_itemTemplate);
    pItem->SetName(name);
    pItem->SetID(nID);
    pItem->SetAttribute(L"tip", strTip);

    ItemInfo *pItemInfo = new ItemInfo;
    pItemInfo->strText = text;
    pItemInfo->strName = name;
    pItemInfo->iIcon = iIcon;
    pItemInfo->id = nID;
    pItem->SetUserData((ULONG_PTR)pItemInfo);

    EventGroupListInitItem evt(this);
    evt.pItem = pItem;
    evt.pItemInfo = pItemInfo;
    FireEvent(evt);
    evt.pItem->GetEventSet()->subscribeEvent(EventCmd::EventID,
                                             Subscriber(&SGroupList::OnItemClick, this));
    RequestRelayout();

    return pItem;
}

BOOL SGroupList::OnGroupClick(IEvtArgs *e)
{
    e->SetBubbleUp(FALSE);
    SWindow *pSender = sobj_cast<SWindow>(e->Sender());
    GroupInfo *pInfo = (GroupInfo *)pSender->GetParent()->GetUserData();
    pInfo->bCollapsed = !pInfo->bCollapsed;
    pSender->GetParent()->FindChildByName(L"container")->SetVisible(!pInfo->bCollapsed);
    EventGroupStateChanged evt(this);
    evt.pItem = pSender->GetParent();
    evt.pGroupInfo = pInfo;
    FireEvent(evt);
    RequestRelayout();
    return true;
}

BOOL SGroupList::OnItemClick(IEvtArgs *e)
{
    SWindow *pSender = sobj_cast<SWindow>(e->Sender());
    if (m_pSelectedItem != pSender)
    {
        pSender->SetCheck(TRUE);
        if (m_pSelectedItem)
        {
            m_pSelectedItem->SetCheck(FALSE);
        }
        m_pSelectedItem = pSender;
        EventGroupListItemCheck evt(this);
        evt.pItem = pSender;
        evt.pItemInfo = (ItemInfo *)pSender->GetUserData();
        FireEvent(evt);
    }
    e->SetBubbleUp(false);
    return true;
}

} // namespace SOUI

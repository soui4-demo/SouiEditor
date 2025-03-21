// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "DropTarget.h"
#include "LayoutAdapter.h"
#ifdef _WIN32
#include "../monitor/PathMonitor.h"
#endif//_WIN32

class CMainDlg : public SHostWnd, public CDropTarget::IDropListener
{
	SListView * m_lvLayout;
	SEdit	  * m_editFilter;
	SAutoRefPtr<CLayoutAdapter> m_adapter;
	SStringT m_strPrevFile;
	SStringT m_strPrevName;
	FILETIME m_modifyTime;
	FILETIME m_idxTime;
	DWORD	 m_dwPrevTime;
	HWND	m_hViewer;
	#ifdef _WIN32
	CPathMonitor m_pathMonitor;
	#endif//_WIN32
public:
	CMainDlg();
	~CMainDlg();

	void OpenUires(SStringT strUires);
	void OnFileChanged();
	void StartPreviewProcess(SStringT strLayout);
	void QuitViewer();
	void SendCopyDataToViewer(DWORD dwMsgId,LPVOID pData,DWORD dwLen);
	static FILETIME GetFileModifyTime(SStringT filename);
protected:
	virtual BOOL OnDrop(LPCTSTR pszName);
protected:
	void OnClose();
	void OnMinimize();
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnBtnOpen();
	void OnBtnClose();
	void OnBtnAbout();
	void OnEditChanged(IEvtArgs *e);
	void OnItemDbClick(IEvtArgs *e);
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_ID_HANDLER(R.id.edit_filter,EventRENotify::EventID,OnEditChanged)
		EVENT_ID_HANDLER(R.id.lv_layout,EventOfPanel::EventID,OnItemDbClick)
		EVENT_ID_COMMAND(R.id.btn_open_uires,OnBtnOpen)
		EVENT_ID_COMMAND(R.id.btn_close_uires,OnBtnClose)
		EVENT_ID_COMMAND(R.id.btn_about,OnBtnAbout)
	EVENT_MAP_END2(SHostWnd)
		
	LRESULT OnViewerCreate(UINT uMsg,WPARAM wp,LPARAM lp);
	LRESULT OnViewerDestroy(UINT uMsg,WPARAM wp,LPARAM lp);

	void OnTimer(UINT_PTR timeID);
	void OnDestroy();
	BEGIN_MSG_MAP_EX(CMainDlg)
		MESSAGE_HANDLER_EX(kmsg_viewer_create,OnViewerCreate)
		MESSAGE_HANDLER_EX(kmsg_viewer_destroy,OnViewerDestroy)

		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_TIMER(OnTimer)
		CHAIN_MSG_MAP(SHostWnd)
	END_MSG_MAP()
};

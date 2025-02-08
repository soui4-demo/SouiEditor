// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
#include "helper/SFunctor.hpp"
#include "../uieditor/FileHelper.h"

CMainDlg::CMainDlg() 
: SHostWnd(_T("LAYOUT:XML_MAINWND"))
#ifdef _WIN32
,m_pathMonitor(this)
#endif//_WIN32
,m_hViewer(0)
,m_dwPrevTime(0)
{
}

CMainDlg::~CMainDlg()
{
	#ifdef _WIN32
	m_pathMonitor.EndThread();
	#endif
}

void CMainDlg::OnTimer(UINT_PTR timeID)
{
	if(timeID == 100)
	{
		if(m_hViewer)
		{
			::PostMessage(m_hViewer,kmsg_heart,0,0);
		}
	}else
	{
		SetMsgHandled(FALSE);
	}
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	HRESULT hr=::RegisterDragDrop(m_hWnd,GetDropTarget());
	m_lvLayout = FindChildByID2<SListView>(R.id.lv_layout);
	m_editFilter = FindChildByID2<SEdit>(R.id.edit_filter);
	CDropTarget * pDropTarget = new CDropTarget(this);
	RegisterDragDrop(m_lvLayout->GetSwnd(),pDropTarget);
	pDropTarget->Release();

	m_adapter.Attach(new CLayoutAdapter);
	m_lvLayout->SetAdapter(m_adapter);

	SetTimer(100,4000);
	return 0;
}

//TODO:消息映射
void CMainDlg::OnClose()
{
	SNativeWnd::DestroyWindow();
}

void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}


BOOL CMainDlg::OnDrop(LPCTSTR pszName)
{
	SStringT strUires = pszName;
	if(GetFileAttributes(pszName)&FILE_ATTRIBUTE_DIRECTORY)
	{
		strUires += _T("\\uires.idx");
	}
	if(strUires.EndsWith(_T("uires.idx"),true))
	{
		OpenUires(strUires);
		return TRUE;
	}
	return FALSE;
}

void CMainDlg::OpenUires(SStringT strUires)
{
	if(m_adapter->OpenUires(strUires))
	{
		m_editFilter->SetWindowText(NULL);
		m_idxTime = GetFileModifyTime(strUires);
			#ifdef _WIN32
		m_pathMonitor.SetPath(m_adapter->GetDir());
		#endif//_WIN32
	}
}

void CMainDlg::OnEditChanged(IEvtArgs *e)
{
	EventRENotify *e2 = sobj_cast<EventRENotify>(e);
	if(e2->iNotify == EN_CHANGE)
	{
		SStringT strFilter = m_editFilter->GetWindowText();
		m_adapter->SetFilter(strFilter);
	}
}

void CMainDlg::OnItemDbClick(IEvtArgs *e)
{
	EventOfPanel *e2=sobj_cast<EventOfPanel>(e);
	if(e2->pOrgEvt->GetID() == EventItemPanelDbclick::EventID)
	{
		int iSel = m_lvLayout->GetSel();
		SStringT strPrevFile = m_adapter->GetPath(iSel);
		SStringT strPrevName = m_adapter->GetName(iSel);
		if(m_strPrevFile != strPrevFile)
		{
			if(!m_strPrevFile.IsEmpty())
			{
				QuitViewer();
			}
			m_strPrevFile = strPrevFile;
			m_strPrevName = strPrevName;
			StartPreviewProcess(m_strPrevName);
			m_modifyTime = GetFileModifyTime(m_strPrevFile);
		}
	}
}


void CMainDlg::StartPreviewProcess(SStringT strLayout)
{
	SStringT binDir = SApplication::getSingleton().GetAppDir();
	SStringT strPreviewExePath = binDir + _T("/uiviewer");

	TCHAR buffer[32] = { 0 };
	SStringT strCommandLine = strPreviewExePath + _T(" ");
	strCommandLine += _T("\"");
	SStringT projDir = m_adapter->GetDir();
	projDir.TrimRight('\\');
	strCommandLine += projDir;
	strCommandLine += _T("\" LAYOUT:");
	strCommandLine += strLayout;

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	::ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	si.wShowWindow = SW_SHOWNORMAL;
	si.dwFlags = STARTF_USESHOWWINDOW;

	if (!CreateProcess(NULL, (LPTSTR)strCommandLine.c_str(), 
		NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		int err = GetLastError();
		return;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void CMainDlg::OnFileChanged()
{
	if(GetFileAttributes(m_strPrevFile)!=INVALID_FILE_ATTRIBUTES)
	{//update preview
		FILETIME ft = GetFileModifyTime(m_strPrevFile);
		if(memcmp(&ft,&m_modifyTime,sizeof(ft))!=0)
		{
			if(GetTickCount()-m_dwPrevTime<2000)
				return;
			pugi::xml_document xmlDoc;
			if(xmlDoc.load_file(m_strPrevFile))
			{
				m_modifyTime = ft;
				m_dwPrevTime = GetTickCount();
				SendCopyDataToViewer(update_file_id,NULL,0);
			}
		}
	}else if(!m_strPrevFile.IsEmpty())
	{//close preview
		QuitViewer();
	}

	//index changed
	SStringT strUires = m_adapter->GetDir()+_T("uires.idx");
	FILETIME ft = GetFileModifyTime(strUires);
	if(memcmp(&ft,&m_idxTime,sizeof(ft))!=0)
	{
		OpenUires(strUires);
	}

}

FILETIME CMainDlg::GetFileModifyTime(SStringT filename)
{
	FILETIME ret={0};
	HANDLE hFile = CreateFile(filename,GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		GetFileTime(hFile,NULL,NULL,&ret);
		CloseHandle(hFile);
	}
	return ret;
}

LRESULT CMainDlg::OnViewerCreate(UINT uMsg,WPARAM wp,LPARAM lp)
{
	m_hViewer = (HWND)wp;
	CRect rcWnd;
	GetNative()->GetWindowRect(&rcWnd);
	POINT pt = { rcWnd.right+5,rcWnd.top};
	SendCopyDataToViewer(setviewerpos_id,&pt,sizeof(POINT));
	return 0;
}


void CMainDlg::QuitViewer()
{
	SendCopyDataToViewer(exitviewer_id,NULL,0);
}

void CMainDlg::SendCopyDataToViewer(DWORD dwMsgId,LPVOID pData,DWORD dwLen)
{
	if (m_hViewer)
	{
		COPYDATASTRUCT cds;
		cds.dwData = dwMsgId;
		cds.cbData = dwLen;
		cds.lpData = pData;
		::SendMessage(m_hViewer, WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cds);
	}
}

LRESULT CMainDlg::OnViewerDestroy(UINT uMsg,WPARAM wp,LPARAM lp)
{
	m_strPrevFile.Empty();
	m_strPrevName.Empty();
	memset(&m_modifyTime,0,sizeof(m_modifyTime));
	m_hViewer = 0;
	return 0;
}

void CMainDlg::OnDestroy()
{
	QuitViewer();
	SetMsgHandled(FALSE);
}

void CMainDlg::OnBtnOpen()
{
	CFileDialogEx OpenDlg(TRUE, NULL, _T("idx"), _T("uires.idx"), 6, _T("soui skin index(*.idx)\0*.idx\0All files (*.*)\0*.*\0\0"));
	if (IDOK == OpenDlg.DoModal())
	{
		OpenUires(OpenDlg.m_szFileName);
	}
}

void CMainDlg::OnBtnClose()
{
	QuitViewer();
	m_adapter->CloseUires();
	#ifdef _WIN32
	m_pathMonitor.EndThread();
	#endif//_WIN32
}

void CMainDlg::OnBtnAbout()
{
	SHostDialog dlgAbout(UIRES.LAYOUT.dlg_about);
	dlgAbout.DoModal();
}

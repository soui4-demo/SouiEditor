#include "stdafx.h"
#include "PathMonitor.h"
#include "../src/MainDlg.h"
#include <helper/SFunctor.hpp>

CPathMonitor::CPathMonitor(CMainDlg *pMainDlg):m_pMainDlg(pMainDlg)
{
}

CPathMonitor::~CPathMonitor(void)
{
}

UINT CPathMonitor::Run()
{
	HANDLE h = FindFirstChangeNotification(m_strPath.c_str(),TRUE,FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_DIR_NAME);
	if(h!=INVALID_HANDLE_VALUE)
	{
		HANDLE hs[2]={m_evtStop,h};
		for(;;)
		{
			DWORD dwRet = WaitForMultipleObjects(2,hs,FALSE,INFINITE);
			if(dwRet==WAIT_OBJECT_0)
			{
				break;
			}
			STaskHelper::post(m_pMainDlg->GetMsgLoop(),m_pMainDlg,&CMainDlg::OnFileChanged);
			if(!FindNextChangeNotification(h))
			{
				break;
			}
		}
		FindCloseChangeNotification(h);
	}
	return 0;
}

void CPathMonitor::SetPath(LPCTSTR pszPath)
{
	if(IsRunning())
		EndThread();
	m_strPath = pszPath;
	BeginThread();
}

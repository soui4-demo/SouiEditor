// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "MainDlg.h"
#include <Shellapi.h>
#include "SUnkWnd.h"
#include "Adapter.h"

#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

class SApp : public SApplication
{
public:
	SApp(IRenderFactory *pRendFactory,HINSTANCE hInst):SApplication(pRendFactory,hInst){}
protected:
	virtual SWindow * CreateWindowByName(LPCWSTR pszWndClass) const
	{
		SWindow *pRet = SApplication::CreateWindowByName(pszWndClass);
		if(pRet)
		{
			if (pRet->IsClass(SMCListView::GetClassName()))
			{
				CBaseMcAdapterFix *mcAdapter = new CBaseMcAdapterFix();
				((SMCListView*)pRet)->SetAdapter(mcAdapter);
				mcAdapter->Release();
			}
			if (pRet->IsClass(SListView::GetClassName()))
			{
				CBaseAdapterFix *listAdapter = new CBaseAdapterFix();
				((SListView*)pRet)->SetAdapter(listAdapter);
				listAdapter->Release();
			}
			if (pRet->IsClass(STileView::GetClassName()))
			{
				CBaseAdapterFix *listAdapter = new CBaseAdapterFix();
				((STileView*)pRet)->SetAdapter(listAdapter);
				listAdapter->Release();
			}
			if(pRet->IsClass(STreeView::GetClassName()))
			{//todo:

			}
		}
		return pRet;
	}

	virtual IObject * OnCreateUnknownObject(const SObjectInfo & objInfo) const
	{
		if(objInfo.mType == SWindow::GetClassType())
		{
			SUnkWnd * pRet = new SUnkWnd();
			pRet->SetOriClassName(objInfo.mName);
			return pRet;
		}else
		{
			return NULL;
		}
	}
};

class SUiViewer
{
private:
	SComMgr m_ComMgr;
	bool m_bInitSucessed;
	SApplication * m_theApp;
public:
	SUiViewer(HINSTANCE hInstance):m_theApp(NULL), m_bInitSucessed(false){
		
		CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
		BOOL bLoaded = FALSE;
		//使用GDI渲染界面
		bLoaded = m_ComMgr.CreateRender_Skia((IObjRef * *)& pRenderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [render] failed!"));
		//设置图像解码引擎。默认为GDIP。基本主流图片都能解码。系统自带，无需其它库
		CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
		bLoaded = m_ComMgr.CreateImgDecoder((IObjRef * *)& pImgDecoderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("imgdecoder"));

		pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
		m_theApp = new SApp(pRenderFactory, hInstance);	
		m_bInitSucessed = (TRUE==bLoaded);
	};

	operator bool()const
	{
		return m_bInitSucessed;
	}
	//加载系统资源
	BOOL LoadSystemRes()
	{
		BOOL bLoaded = FALSE;

		//从DLL加载系统资源
		{
			HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
			if (hModSysResource)
			{
				CAutoRefPtr<IResProvider> sysResProvider;
				CreateResProvider(RES_PE, (IObjRef * *)& sysResProvider);
				sysResProvider->Init((WPARAM)hModSysResource, 0);
				m_theApp->LoadSystemNamedResource(sysResProvider);
				FreeLibrary(hModSysResource);
			}
			else
			{
				SASSERT(0);
			}
		}

		return bLoaded;
	}
	//加载用户资源
	BOOL LoadUserRes(LPCTSTR pszDir)
	{
		SAutoRefPtr<IResProvider>   pResProvider;
		CreateResProvider(RES_FILE, (IObjRef * *)& pResProvider);
		BOOL bLoaded = pResProvider->Init((LPARAM)pszDir, 0);
		if(bLoaded)
		{
			m_theApp->AddResProvider(pResProvider);
		}
		return bLoaded;
	}
	
	void RegCustomCtrls()
	{
		m_theApp->RegisterWindowClass<SUnkWnd>();
	}

	~SUiViewer()
	{
		if (m_theApp)
		{
			delete m_theApp;
			m_theApp = NULL;
		}
	}

	int Run(SHostWnd *pHostWnd)
	{
		pHostWnd->Create(GetActiveWindow());
		pHostWnd->SendMessage(WM_INITDIALOG);
		pHostWnd->CenterWindow();
		pHostWnd->ShowWindow(SW_SHOWNORMAL);
		return m_theApp->Run(pHostWnd->m_hWnd);
	}
};


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));
	int nRet = 0;
	{
		SUiViewer souiEngine(hInstance);
		if (souiEngine)
		{
			souiEngine.LoadSystemRes();
			souiEngine.RegCustomCtrls();
			int nArgs = 0;
			LPWSTR * args = CommandLineToArgvW(GetCommandLineW(),&nArgs);
			if(nArgs==3)
			{
				souiEngine.LoadUserRes(S_CW2T(args[1]));
				CMainDlg dlg(S_CW2T(args[2]));
				nRet = souiEngine.Run(&dlg);
			}
			LocalFree(args);
		}
	}
	OleUninitialize();
	return nRet;
}

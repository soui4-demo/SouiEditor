// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "PreviewHost.h"
#include <Shellapi.h>
#include "PreviewContainer.h"
#include "../ExtendCtrls/SCtrlsRegister.h"
#include <SouiFactory.h>

#pragma comment(lib,"imm32.lib")
#pragma comment(lib, "shlwapi.lib")

#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")

class SApp : public SApplication
{
public:
	SApp(IRenderFactory *pRendFactory,HINSTANCE hInst):SApplication(pRendFactory,hInst){}
protected:
	virtual IObject * OnCreateUnknownObject(const SObjectInfo & objInfo) const
	{
		if(objInfo.nType == SWindow::GetClassType())
		{
			return CreateWindowByName(SWindow::GetClassName());
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
	SouiFactory m_souiFac;
	HWND m_hDesignParent;

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
				SAutoRefPtr<IResProvider> sysResProvider;
				sysResProvider.Attach(m_souiFac.CreateResProvider(RES_PE));
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
		pResProvider.Attach(m_souiFac.CreateResProvider(RES_FILE));
		BOOL bLoaded = pResProvider->Init((LPARAM)pszDir, 0);
		if(bLoaded)
		{
			m_theApp->AddResProvider(pResProvider);
		}
		return bLoaded;
	}
	
	void RegCustomCtrls()
	{
		SCtrlsRegister::RegisterCtrls(m_theApp);
	}

	~SUiViewer()
	{
		if (m_theApp)
		{
			delete m_theApp;
			m_theApp = NULL;
		}
	}

	int Run(SNativeWnd *pHostWnd, HWND hParent)
	{
		m_hDesignParent = hParent;
		if (hParent)
		{
			CRect rc;
			::GetClientRect(hParent,&rc);
			pHostWnd->CreateNative(L"SouiPreview",WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|WS_CLIPCHILDREN,0,0,0,rc.Width(),rc.Height(),m_hDesignParent,0,NULL);
		}else
		{
			pHostWnd->CreateNative(L"SouiPreview",WS_HSCROLL|WS_VSCROLL|WS_MAXIMIZEBOX|WS_SYSMENU|WS_MINIMIZEBOX|WS_CAPTION|WS_THICKFRAME|WS_CLIPCHILDREN,0,0,0,500,500,GetActiveWindow(),0,NULL);
			pHostWnd->ShowWindow(SW_SHOW);
		}
		return m_theApp->Run(pHostWnd->m_hWnd);
	}
};


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));
	int nRet = 0;
	{
		//char szBuf[MAX_PATH] = { 0 };
		//sprintf_s(szBuf, MAX_PATH, "C:\\Windows\\System32\\VSJitDebugger.exe -p %d",
		//	GetCurrentProcessId());
		//WinExec(szBuf, SW_SHOW);

		SUiViewer souiEngine(hInstance);
		if (souiEngine)
		{
			souiEngine.LoadSystemRes();
			souiEngine.RegCustomCtrls();
			int nArgs = 0;
			LPWSTR pszCmds = GetCommandLineW();
			LPWSTR * args = CommandLineToArgvW(pszCmds,&nArgs);
			if(nArgs >= 3)
			{
				HWND hParent = NULL, hEditor = NULL;
				if (nArgs >= 4)
					hEditor = (HWND)_wtol(args[3]);
				if (nArgs >= 5)
					hParent = (HWND)_wtol(args[4]);
				
				SStringT resFolder = S_CW2T(args[1]);
				resFolder.Trim('"');
				souiEngine.LoadUserRes(resFolder);

				CPreviewContainer prevWnd(S_CW2T(args[2]), hEditor);
				nRet = souiEngine.Run(&prevWnd, hParent);
			}
			LocalFree(args);
		}
	}
	OleUninitialize();
	return nRet;
}

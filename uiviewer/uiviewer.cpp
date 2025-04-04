// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "PreviewHost.h"
#include <shellapi.h>
#include "PreviewContainer.h"
#include "../ExtendCtrls/SCtrlsRegister.h"
#include <SouiFactory.h>
#include <zipresprovider-param.h>
#ifndef _WIN32
#include <logdef.h>
#endif//_WIN32

#pragma comment(lib,"imm32.lib")
#pragma comment(lib, "shlwapi.lib")

#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")

void SWinxLog(const char* pLogStr, int level){
	//SLOG("swinx",level)<<pLogStr;
}

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
		SetCurrentDirectory(m_theApp->GetAppDir());
		m_bInitSucessed = (TRUE==bLoaded);

		SAutoRefPtr<ILogMgr> logMgr;
		if(m_ComMgr.CreateLog4z((IObjRef**)&logMgr)){
			m_theApp->SetLogManager(logMgr);
			logMgr->setLoggerName("uiviewer");
			logMgr->setLoggerLevel(LOG_LEVEL_INFO);
			logMgr->start();
		}
		#ifndef _WIN32
		SetSwinxLogCallback(SWinxLog,SLOG_INFO);
		#endif//_WIN32
	};

	operator bool()const
	{
		return m_bInitSucessed;
	}
	//加载系统资源
	BOOL LoadSystemRes()
	{
	#ifdef _WIN32
		BOOL bLoaded = FALSE;
		//从DLL加载系统资源
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
		return bLoaded;
#else
		IResProvider* sysResProvider;
		BOOL bLoaded = m_ComMgr.CreateResProvider_ZIP((IObjRef**)&sysResProvider);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));
		ZIPRES_PARAM param;
		ZipFile(&param,m_theApp->GetRenderFactory(),"soui-sys-resource.zip");
		bLoaded = sysResProvider->Init((WPARAM)&param, 0);
		SASSERT(bLoaded);
		if(bLoaded){
			m_theApp->LoadSystemNamedResource(sysResProvider);
		}
		sysResProvider->Release();
		return bLoaded;
#endif
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
		#ifndef _WIN32
		//hParent = 0;
		#endif//_WIN32
		if (hParent)
		{
			CRect rc;
			::GetClientRect(hParent,&rc);
			pHostWnd->CreateNative(_T("SouiPreview"),WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|WS_CLIPCHILDREN,0,0,0,rc.Width(),rc.Height(),hParent,0,NULL);
		}else
		{
			pHostWnd->CreateNative(_T("SouiPreview"),WS_HSCROLL|WS_VSCROLL|WS_MAXIMIZEBOX|WS_SYSMENU|WS_MINIMIZEBOX|WS_CAPTION|WS_THICKFRAME|WS_CLIPCHILDREN,0,0,0,500,500,GetActiveWindow(),0,NULL);
			pHostWnd->ShowWindow(SW_SHOW);
		}
		return m_theApp->Run(pHostWnd->m_hWnd);
	}
};

#ifdef _WIN32
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
			HWND hParent = NULL, hEditor = NULL;
			SStringT strLayout;
			if(nArgs >= 3)
			{
				strLayout = S_CW2T(args[2]);
				if (nArgs >= 4)
					hEditor = (HWND)_wtol(args[3]);
				if (nArgs >= 5)
					hParent = (HWND)_wtol(args[4]);
				
				SStringT resFolder = S_CW2T(args[1]);
				resFolder.Trim('"');
				souiEngine.LoadUserRes(resFolder);
			}
			CPreviewContainer prevWnd(strLayout, hEditor);
			LocalFree(args);
			nRet = souiEngine.Run(&prevWnd, hParent);
		}
	}
	OleUninitialize();
	return nRet;
}
#else
int main(int nArgs,char **args)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));
	int nRet = 0;
	{
		SUiViewer souiEngine(hInstance);
		if (souiEngine)
		{
			souiEngine.LoadSystemRes();
			souiEngine.RegCustomCtrls();
			if(nArgs >= 3)
			{
				HWND hParent = NULL, hEditor = NULL;
				if (nArgs >= 4)
					hEditor = (HWND)atol(args[3]);
				if (nArgs >= 5)
					hParent = (HWND)atol(args[4]);
				
				SStringT resFolder = S_CA2T(args[1]);
				resFolder.Trim('"');
				souiEngine.LoadUserRes(resFolder);

				CPreviewContainer prevWnd(S_CA2T(args[2]), hEditor);
				nRet = souiEngine.Run(&prevWnd, hParent);
			}
		}
	}
	OleUninitialize();
	return nRet;
}
#endif

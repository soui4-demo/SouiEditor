// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "MainDlg.h"
#include <SouiFactory.h>

//从PE文件加载，注意从文件加载路径位置
#define RES_TYPE 0
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")

//定义唯一的一个R,UIRES对象,ROBJ_IN_CPP是resource.h中定义的宏。
#define INIT_R_DATA
#include "res\resource.h"

class SOUIEngine
{
private:
	SComMgr m_ComMgr;
	SApplication *m_theApp;
	SouiFactory m_souiFac;
	bool m_bInitSucessed;
public:
	SOUIEngine(HINSTANCE hInstance):m_theApp(NULL), m_bInitSucessed(false){
		
		CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
		BOOL bLoaded = FALSE;
		//使用Skia渲染界面
		bLoaded = m_ComMgr.CreateRender_Skia((IObjRef * *)& pRenderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [render] failed!"));
		//设置图像解码引擎。默认为GDIP。基本主流图片都能解码。系统自带，无需其它库
		CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
		bLoaded = m_ComMgr.CreateImgDecoder((IObjRef * *)& pImgDecoderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("imgdecoder"));

		pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
		m_theApp = new SApplication(pRenderFactory, hInstance,ksz_uipreview_cls);	
		m_bInitSucessed = (TRUE==bLoaded);
	};
	operator bool()const
	{
		return m_bInitSucessed;
	}
	//加载系统资源
	bool LoadSystemRes()
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

		return TRUE==bLoaded;
	}
	//加载用户资源
	bool LoadUserRes()
	{
		SAutoRefPtr<IResProvider>   pResProvider;
		BOOL bLoaded = FALSE;
#ifdef _DEBUG		
		//选择了仅在Release版本打包资源则在DEBUG下始终使用文件加载
		{
			pResProvider.Attach(m_souiFac.CreateResProvider(RES_FILE));
			bLoaded = pResProvider->Init((LPARAM)_T("uires"), 0);
			SASSERT(bLoaded);
		}
#else
		{
			pResProvider.Attach(m_souiFac.CreateResProvider(RES_PE));
			bLoaded = pResProvider->Init((WPARAM)m_theApp->GetModule(), 0);
			SASSERT(bLoaded);
		}
#endif
		m_theApp->InitXmlNamedID((const LPCWSTR*)&R.name, (const int*)&R.id,sizeof(R.id)/sizeof(int));
		m_theApp->AddResProvider(pResProvider);
		return TRUE==bLoaded;
	}

	~SOUIEngine()
	{
		if (m_theApp)
		{
			delete m_theApp;
			m_theApp = NULL;
		}
	}

	template<class MainWnd>
	int Run()
	{
		MainWnd dlgMain;
		dlgMain.Create(GetActiveWindow());
		SetWindowText(dlgMain.m_hWnd,ksz_uipreview_wnd);
		dlgMain.SendMessage(WM_INITDIALOG);
		dlgMain.CenterWindow(dlgMain.m_hWnd);
		dlgMain.ShowWindow(SW_SHOWNORMAL);
		return m_theApp->Run(dlgMain.m_hWnd);
	}

	SApplication* GetApp()
	{
		return m_theApp;
	}
};
//debug时方便调试设置当前目录以便从文件加载资源
void SetDefaultDir()
{
	TCHAR szCurrentDir[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szCurrentDir, sizeof(szCurrentDir));

	LPTSTR lpInsertPos = _tcsrchr(szCurrentDir, _T('\\'));
#ifdef _DEBUG
	_tcscpy(lpInsertPos + 1, _T("..\\uiPreview"));
#else
	_tcscpy(lpInsertPos + 1, _T("\0"));
#endif
	SetCurrentDirectory(szCurrentDir);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));
	SetDefaultDir();
	int nRet = 0;
	{
		SOUIEngine souiEngine(hInstance);
		if (souiEngine)
		{
			//加载系统资源
			souiEngine.LoadSystemRes();
			//加载用户资源
			souiEngine.LoadUserRes();
			nRet = souiEngine.Run<CMainDlg>();
		}
		else
		{
			MessageBox(NULL, _T("无法正常初使化SOUI"), _T("错误"), MB_OK | MB_ICONERROR);
		}
	}
	OleUninitialize();
	return nRet;
}

#pragma once
#include "core/shostwnd.h"
#include "core/smsgloop.h"
#include "core/SHostDialog.h"
//#include "control/SRichEdit.h"
//#include "extend.ctrls/SImageEx.h"

namespace SOUI
{
	class SDlgAbout: public SHostDialog
	{
		DEF_SOBJECT(SHostDialog,L"dlgabout")
	public:
		SDlgAbout();

		~SDlgAbout(void)
		{

		}

		void OnClose();
		void OnBtnDlgOpenFile();

		BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	protected:
		void OnOK();

		EVENT_MAP_BEGIN()

			EVENT_ID_COMMAND(IDOK,OnOK)
			EVENT_MAP_END()

			BEGIN_MSG_MAP_EX(SDlgAbout)
			MSG_WM_INITDIALOG(OnInitDialog)
			CHAIN_MSG_MAP(SHostDialog)
			REFLECT_NOTIFICATIONS_EX()
			END_MSG_MAP()
	};

}
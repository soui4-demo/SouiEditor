/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       SHostDialog.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI的Dialog模块
*/

#pragma once
#include "core/shostwnd.h"
#include "core/smsgloop.h"
#include "core/SHostDialog.h"
#include "control/SRichEdit.h"

namespace SOUI
{
	class SDlgCreatePro: public SHostDialog
	{
		DEF_SOBJECT(SHostDialog,L"dlgcreatepro")
	public:
		SDlgCreatePro(LPCTSTR pszXmlName):SHostDialog(pszXmlName)
		{

		}
		~SDlgCreatePro(void)
		{

		}

	protected:
		void OnOK();

		EVENT_MAP_BEGIN()
			EVENT_ID_COMMAND(IDOK,OnOK)
			EVENT_MAP_END()

			BEGIN_MSG_MAP_EX(SCreateProDlg)
			CHAIN_MSG_MAP(SHostDialog)
			REFLECT_NOTIFICATIONS_EX()
			END_MSG_MAP()

	public:
		SStringT m_strinput;
	};

}
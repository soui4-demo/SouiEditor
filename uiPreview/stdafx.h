// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#define  _CRT_SECURE_NO_WARNINGS
#define	 DLL_SOUI
#include <souistd.h>
#include <core/SHostDialog.h>
#include <control/SMessageBox.h>
#include <control/SouiCtrls.h>
#include <res.mgr/SObjDefAttr.h>
#include <com-cfg.h>
#include "resource.h"
#include "res/resource.h"
using namespace SOUI;

#include <string>
#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

#include "../uieditor/Global.h"
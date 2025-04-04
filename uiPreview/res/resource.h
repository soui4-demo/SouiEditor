//stamp:0932f40c6fc58764
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#ifndef _UIRES_H_
#define _UIRES_H_
	struct _UIRES{
		struct _UIDEF{
			const TCHAR * XML_INIT;
			}UIDEF;
		struct _LAYOUT{
			const TCHAR * XML_MAINWND;
			const TCHAR * dlg_about;
			}LAYOUT;
		struct _values{
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
			}values;
		struct _img{
			const TCHAR * png_item_bk;
			}img;
		struct _ICON{
			const TCHAR * ICON_LOGO;
			}ICON;
	};
#endif//_UIRES_H_
#ifdef INIT_R_DATA
struct _UIRES UIRES={
		{
			_T("UIDEF:XML_INIT"),
		},
		{
			_T("LAYOUT:XML_MAINWND"),
			_T("LAYOUT:dlg_about"),
		},
		{
			_T("values:string"),
			_T("values:color"),
			_T("values:skin"),
		},
		{
			_T("img:png_item_bk"),
		},
		{
			_T("ICON:ICON_LOGO"),
		},
	};
#else
extern struct _UIRES UIRES;
#endif//INIT_R_DATA

#ifndef _R_H_
#define _R_H_
struct _R{
	struct _name{
		 const wchar_t * btn_about;
		 const wchar_t * btn_close;
		 const wchar_t * btn_close_uires;
		 const wchar_t * btn_min;
		 const wchar_t * btn_open_uires;
		 const wchar_t * edit_filter;
		 const wchar_t * lv_layout;
		 const wchar_t * txt_name;
		 const wchar_t * txt_path;
	}name;
	struct _id{
		int btn_about;
		int btn_close;
		int btn_close_uires;
		int btn_min;
		int btn_open_uires;
		int edit_filter;
		int lv_layout;
		int txt_name;
		int txt_path;
	}id;
	struct _color{
		int blue;
		int gray;
		int green;
		int red;
		int white;
	}color;
	struct _string{
		int about;
		int title;
		int ver;
	}string;

};
#endif//_R_H_
#ifdef INIT_R_DATA
struct _R R={
	{
		L"btn_about",
		L"btn_close",
		L"btn_close_uires",
		L"btn_min",
		L"btn_open_uires",
		L"edit_filter",
		L"lv_layout",
		L"txt_name",
		L"txt_path"
	}
	,
	{
		65536,
		65538,
		65540,
		65537,
		65539,
		65541,
		65542,
		65543,
		65544
	}
	,
	{
		0,
		1,
		2,
		3,
		4
	}
	,
	{
		0,
		1,
		2
	}
	
};
#else
extern struct _R R;
#endif//INIT_R_DATA

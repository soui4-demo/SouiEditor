﻿#ifndef _SCHAT_EDIT_H_
#define _SCHAT_EDIT_H_

SNSBEGIN

#define EVT_CHATEDIT_KEYRETURN (EVT_EXTERNAL_BEGIN + 500)

DEF_EVT_EXT(EventChatEditKeyReturn, EVT_CHATEDIT_KEYRETURN, { bool bCancel; });

class SChatEdit : public SRichEdit {
    DEF_SOBJECT(SRichEdit, L"chatedit")
  public:
    SChatEdit(void);
    ~SChatEdit(void);

    //************************************
    // Method:    AppendFormatText
    // FullName:  SOUI::SChatEdit::AppendFormatText
    // Access:    public
    // Returns:   BOOL -- success:TRUE
    // Qualifier:
    // Parameter: const SStringW & strMsg
    // remark: strMsg :一个XML格式的正文，支持标签：<color value="#ff0000">abc<link
    // color="#0000ff">home</link><underline>efg<italic>abc<bold>abc<strike>afc<font
    // value="宋体">abc<smiley id="1"
    // path="c:\a.gif"/></font></strike></bold></italic></underline></color>
    //************************************
    BOOL AppendFormatText(const SStringW &strMsg, BOOL bNewLine = TRUE, BOOL bCanUndo = TRUE);

    BOOL AppendFormatText(const SXmlNode xmlMsg, BOOL bNewLine = TRUE, BOOL bCanUndo = TRUE);

    BOOL ReplaceSelectionByFormatText(const SStringW &strMsg, BOOL bCanUndo = TRUE);

    SStringW GetFormatText();

  protected:
    int OnCreate(LPVOID);
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    SOUI_MSG_MAP_BEGIN()
    MSG_WM_CREATE(OnCreate)
    MSG_WM_KEYDOWN(OnKeyDown)
    SOUI_MSG_MAP_END()

  protected:
    int _InsertFormatText(int iCaret, CHARFORMATW cf, SXmlNode xmlText, BOOL bCanUndo);
};

SNSEND

#endif//_SCHAT_EDIT_H_


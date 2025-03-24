#pragma once

#include <control/SCmnCtrl.h>

namespace SOUI
{
class SRadioBox2 : public SRadioBox {
    DEF_SOBJECT(SRadioBox, L"radio2")
  public:
    SRadioBox2(void);
    ~SRadioBox2(void);

  protected:
    SIZE MeasureContent(int wid, int hei) override
    {
        if (m_pSkin)
            return m_pSkin->GetSkinSize();
        else
            return SWindow::MeasureContent(wid, hei);
    }
    virtual void GetTextRect(LPRECT pRect)
    {
        SWindow::GetTextRect(pRect);
        pRect->left += m_nTextOffset;
    }
    virtual void DrawFocus(IRenderTarget *pRT)
    {
    }

  protected:
    void OnPaint(IRenderTarget *pRT);

    SOUI_MSG_MAP_BEGIN()
    MSG_WM_PAINT_EX(OnPaint)
    SOUI_MSG_MAP_END()

    ISkinObj *m_pIcon;
    CPoint m_ptIcon;
    int m_nTextOffset;
    SOUI_ATTRS_BEGIN()
    ATTR_SKIN(L"iconSkin", m_pIcon, TRUE)
    ATTR_POINT(L"iconPos", m_ptIcon, TRUE)
    ATTR_INT(L"textOffset", m_nTextOffset, TRUE)
    SOUI_ATTRS_END()
};

} // namespace SOUI

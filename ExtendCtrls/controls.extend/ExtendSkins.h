﻿#pragma once

#include "core/SSkinObjBase.h"

namespace SOUI
{

class SColorMask : public SSkinObjBase {
#define STATE_COUNT 4
    DEF_SOBJECT(SSkinObjBase, L"colormask")

    enum
    {
        ST_NORMAL = 0,
        ST_HOVER,
        ST_PUSHDOWN,
        ST_DISABLE,
    };

  public:
    SColorMask();
    virtual int WINAPI GetStates() const override
    {
        return STATE_COUNT;
    }
    virtual SIZE WINAPI GetSkinSize() const override
    {
        return m_size;
    }

    void SetColors(COLORREF cr[4]);

  protected:
    virtual void _DrawByIndex(IRenderTarget *pRT, LPCRECT rcDraw, int dwState, BYTE byAlpha) const;
    HRESULT OnAttrMask(const SStringW &strValue, BOOL bLoading);
    void MakeCacheApha();

    COLORREF m_crStates[STATE_COUNT];
    SIZE m_size;

    SOUI_ATTRS_BEGIN()
    ATTR_COLOR(L"colorNormal", m_crStates[0], TRUE)
    ATTR_COLOR(L"colorHover", m_crStates[1], TRUE)
    ATTR_COLOR(L"colorDown", m_crStates[2], TRUE)
    ATTR_COLOR(L"colorDisable", m_crStates[3], TRUE)
    ATTR_INT(L"width", m_size.cx, 0)
    ATTR_INT(L"height", m_size.cy, 0)
    ATTR_CUSTOM(L"mask", OnAttrMask)
    ATTR_RECT(L"margin", m_rcMargin, FALSE) //九宫格4周
    SOUI_ATTRS_END()

    // CAutoRefPtr<IBitmap> *  m_pBmpCaches;

    SStringW m_strSkin;
    SAutoRefPtr<IBitmapS> m_bmpSkin;
    SAutoRefPtr<IBitmapS> m_bmpMask;
    CRect m_rcMargin;
    int m_iMaskChannel;
};

}; // namespace SOUI
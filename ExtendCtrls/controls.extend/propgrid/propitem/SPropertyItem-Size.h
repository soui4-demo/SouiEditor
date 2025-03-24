﻿#pragma once

#include "SPropertyItem-Text.h"

namespace SOUI
{
    class SPropertyItemSize : public SPropertyItemText
    {
		friend class SPropertyGrid;
        DEF_SOBJECT(SPropertyItemText,L"propsize")

			enum{
				CHILD_WIDTH=1,
				CHILD_HEIGHT=2
		};
    public:
		static LPCWSTR GetInplaceItemStyleName(){return NULL;}

		virtual PropType GetType() const {return PT_SIZE;}
        virtual void SetValue(const SStringT & strValue);
        
        virtual SStringT GetValue() const;
        virtual void OnValueChanged();
        virtual void OnChildValueChanged(IPropertyItem *pChild);
        
		SIZE GetValue2() const{return m_szValue;}
		virtual BOOL HasValue() const ;
		virtual void ClearValue() ;

        SOUI_ATTRS_BEGIN()
			ATTR_BOOL(L"digit",m_bDigit,FALSE)
            ATTR_CUSTOM(L"value",OnAttrValue)
            ATTR_CUSTOM(L"childrenTitles",OnAttrChildrenTitles)
        SOUI_ATTRS_END()

    protected:
        HRESULT OnAttrValue(const SStringW & strValue,BOOL bLoading);
        HRESULT OnAttrChildrenTitles(const SStringW & strValue,BOOL bLoading);
        
        SIZE    m_szValue;
        SStringT m_strValue[2];
		BOOL	m_bDigit;
        BOOL    m_bChildChanged;
    protected:
        SPropertyItemSize(SPropertyGrid *pOwner);
    };
}

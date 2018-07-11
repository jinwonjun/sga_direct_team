#pragma once
#include "IUIObject.h"
class UIText :public IUIObject
{

public:

	LPD3DXFONT m_pFont;
	//LPCTSTR m_text;

	LPCWSTR m_text;
	RECT m_pRect;
	D3DXCOLOR m_pColor;
	DWORD m_drawTextFormat;
	bool RenderingOn;
	
	void SetColor(D3DXCOLOR c) { m_color = c; }

	UIText(LPD3DXFONT pFont, LPD3DXSPRITE pSptrite, int uiTag = -1);
	virtual ~UIText();
	virtual void Render() override;
};


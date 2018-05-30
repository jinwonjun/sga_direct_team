#include "stdafx.h"
#include "UIText.h"


UIText::UIText(LPD3DXFONT pFont, LPD3DXSPRITE pSptrite, int uiTag) 
	: IUIObject(pSptrite, uiTag),m_pFont(pFont),m_drawTextFormat(DT_CENTER | DT_VCENTER)//DT_ 종류들은 텍스트 기본 정렬 방식
{
}


UIText::~UIText()
{
}

void UIText::Render()
{
	RECT rect;
	SetRect(&rect, m_combinedPos.x, m_combinedPos.y, m_combinedPos.x + m_size.x, m_combinedPos.y + m_size.y);

	//m_pFont->DrawText(m_pSprite, m_text, lstrlen(m_text), &rect, m_drawTextFormat, m_color);

	//m_text = L"123123";

	m_pFont->DrawTextW(m_pSprite, m_text, lstrlen(m_text), &rect, m_drawTextFormat, m_color);


	IUIObject::Render();
}

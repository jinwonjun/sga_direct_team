#pragma once
#define g_pFontMgr FontManager::GetInstance()


namespace FONT
{
	enum FontType
	{
		NORMAL, QUEST, BASE, Item, Equiped,
		NameOfItem, OptionOfItem
	};
}

class FontManager
{
	SINGLETON(FontManager)
private:
	map<FONT::FontType, LPD3DXFONT> m_mapFont;
public:
	LPD3DXFONT GetFont(FONT::FontType e);
	LPD3DXFONT GetFont(FONT::FontType e, int i);

	void Destroy();
};


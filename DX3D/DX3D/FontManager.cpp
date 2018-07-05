#include "stdafx.h"
#include "FontManager.h"


FontManager::FontManager()
{
}


FontManager::~FontManager()
{
}

LPD3DXFONT FontManager::GetFont(FONT::FontType e)
{
	if (m_mapFont.find(e) == m_mapFont.end())
	{
		if (e == FONT::NORMAL)
		{
			D3DXCreateFont(g_pDevice,24, 12, FW_NORMAL, 1, false, 
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("궁서체"), &m_mapFont[e]);
		}
		else if (e == FONT ::QUEST)
		{
			//폰트 추가는 이런식으로
			//AddFontResource("파일 경로/fonts/umberto.ttf");
			D3DXCreateFont(g_pDevice, 24, 12, FW_NORMAL, 1, false,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("umberto"), &m_mapFont[e]);
		}
		else if (e == FONT::Item)
		{
			//폰트 추가는 이런식으로
			//AddFontResource("파일 경로/fonts/umberto.ttf");
			D3DXCreateFont(g_pDevice, 12, 6, FW_NORMAL, 1, false,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("umberto"), &m_mapFont[e]);
		}
		else
		{
			D3DXCreateFont(g_pDevice, 50, 12, FW_NORMAL, 1, true,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("koverwatch"), &m_mapFont[e]);
		}
	}
	return m_mapFont[e];
}

void FontManager::Destroy()
{
	for (auto p : m_mapFont)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapFont.clear();
}

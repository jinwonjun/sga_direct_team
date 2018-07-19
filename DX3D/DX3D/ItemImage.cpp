#include "stdafx.h"
#include "ItemImage.h"


ItemImage::ItemImage(LPD3DXSPRITE pSprite, int uiTag)
	:IUIObject(pSprite, uiTag), m_pTex_Item_img(NULL)
{

}

ItemImage::~ItemImage()
{
}

void ItemImage::Render()
{
	if (m_pTex_Item_img)
	{
		RECT rect;
		SetRect(&rect, 0, 0, m_size.x, m_size.y);
		//m_pSprite->Draw(m_pTex_Item_img, &rect, &m_pivot, &m_combinedPos, m_color);
	}

	IUIObject::Render();

}

void ItemImage::SetTexture(string fullPath)
{
	D3DXIMAGE_INFO info;

	//m_pTex_Item_img = g_pTextureManager->GetTexture(fullPath);
	m_pTex_Item_img = g_pTextureManager->GetTexture(fullPath);

	D3DXGetImageInfoFromFileA(fullPath.c_str(), &info);

	m_size.x = info.Width;
	m_size.y = info.Height;

}

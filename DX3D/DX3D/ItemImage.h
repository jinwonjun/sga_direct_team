#pragma once
#include "IUIObject.h"

class ItemImage :
	public IUIObject
{
public:
	LPDIRECT3DTEXTURE9 m_pTex_Item_img;

	ItemImage(LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual ~ItemImage();

	virtual void Render() override;

	void SetTexture(string fullPath);


	

};


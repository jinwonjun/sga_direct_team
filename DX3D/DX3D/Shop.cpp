#include "stdafx.h"
#include "Shop.h"


Shop* Shop::instance = NULL;

Shop * Shop::Get()
{
	if (instance == NULL)
		instance = new Shop();

	return instance;

}

void Shop::Delete()
{
	SAFE_DELETE(instance);
}

void Shop::Init()
{

	for (int i = 0; i < NumberOfItems; i++)
	{
		if (g_pItem->Items[i].index == NULL)
		{
			continue;
		}
		Shop_Item.push_back(g_pItem->Items[i]);
	}

	for (int i = 0; i < NumberOfItems; i++)
	{
		if (g_pItem->Items[i].index == NULL)
		{
			continue;
		}
		Shop_Item[i].Item_rc = RectMake(0, 0, Shop_Item[i].m_image_Item_Info.Width, Shop_Item[i].m_image_Item_Info.Height);
	}

	//D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT,
		Shop_Item[0].PositionX,
		Shop_Item[0].PositionY,
		0);



}

void Shop::Update()
{
}

void Shop::Render()
{
}



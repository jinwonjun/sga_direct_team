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
	GetClientRect(g_hWnd, &clientRect);
	D3DXCreateSprite(g_pDevice, &Shop_BackGround.m_pSprite);



	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Shop/Black_Back2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Shop_BackGround.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Shop_BackGround.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	Shop_BackGround.PointX = clientRect.right * 0.05;
	Shop_BackGround.PointY = (OriginY *0.05);
	Shop_BackGround.ScaleX = 1.0f;
	Shop_BackGround.ScaleY = 1.0f;


	for (int i = 0; i < CopiedItemNum; i++)
	{
		Shop_Items[i] = g_pItem->Items[i];

		D3DXCreateSprite(g_pDevice, &Shop_Items[i].m_pSprite);
	}



	for (int i = 0; i < CopiedItemNum; i++)
	{
		float abc = i % 3;
		float def = i / 3;
		Shop_Items[i].PositionX = clientRect.right * 0.06 + (clientRect.right * (0.1 *abc));
		Shop_Items[i].PositionY = (OriginY *0.18) + (OriginY * (0.14 *def));

	}
	ShopOpen = false;
	buyItems = false;
	//g_pItem->Items[0].PositionX = clientRect.right * 0.06;
	//g_pItem->Items[0].PositionY = (OriginY *0.06);
	//g_pItem->Items[0].ScaleY = 1.0f;
	//g_pItem->Items[0].ScaleY = 1.0f;
}

void Shop::Update()
{
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	if (g_pKeyboard->KeyDown('P'))
	{
		g_pEquip->EquipScreenOn = false;
		ShopOpen = !ShopOpen;
	}
	if (g_pKeyboard->KeyDown(VK_ESCAPE))
	{
		ShopOpen = false;
	}

	if (ShopOpen == false)
	{
		buyItems = false;
	}
	else
	{

		
		for (int i = 0; i < CopiedItemNum; i++)
		{
			if (PtInRect(&Shop_Items[i].Click_rc, mousePoint))
			{
				if (g_pMouse->ButtonDown(Mouse::RBUTTON))
				{
					g_pInventory->addIndex(Shop_Items[i]);
					buyItems = true;
				}
			}
		}
		
	}
}

void Shop::Render()
{


	if (ShopOpen)
	{

		SetRect(&Shop_BackGround.m_Image_rc, 0, 0, Shop_BackGround.m_imageInfo.Width, Shop_BackGround.m_imageInfo.Height);

		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, Shop_BackGround.PointX, Shop_BackGround.PointY, 0);
		D3DXMatrixScaling(&matS, Shop_BackGround.ScaleX, Shop_BackGround.ScaleY, 1);
		Shop_BackGround.matWorld = matS * matT;

		Shop_BackGround.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		Shop_BackGround.m_pSprite->SetTransform(&Shop_BackGround.matWorld);
		Shop_BackGround.m_pSprite->Draw(
			Shop_BackGround.m_pTex,
			&Shop_BackGround.m_Image_rc,
			//&D3DXVECTOR3(Shop_BackGround.m_imageInfo.Width / 2, Shop_BackGround.m_imageInfo.Height / 2, 0),
			&D3DXVECTOR3(0,0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);
		Shop_BackGround.m_pSprite->End();



		for (int i = 0; i < CopiedItemNum; i++)
		{
			if (PtInRect(&Shop_Items[i].Click_rc, mousePoint))
			{
				g_pInventory->ShowItemInfo(Shop_Items[i]);
			}


			SetRect(&Shop_Items[i].Item_rc, 0, 0, Shop_Items[i].m_image_Item_Info.Width, Shop_Items[i].m_image_Item_Info.Height);
			SetRect(&Shop_Items[i].Click_rc,
				Shop_Items[i].PositionX,
				Shop_Items[i].PositionY,
				Shop_Items[i].PositionX + g_pInventory->ItemSizeX,
				Shop_Items[i].PositionY + g_pInventory->ItemSizeY);


			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, Shop_Items[i].PositionX, Shop_Items[i].PositionY, 0);
			D3DXMatrixScaling(&matS, Shop_Items[i].ScaleX, Shop_Items[i].ScaleY, 1);
			Shop_Items[i].m_matWorld = matS * matT;

			Shop_Items[i].m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			Shop_Items[i].m_pSprite->SetTransform(&Shop_Items[i].m_matWorld);
			Shop_Items[i].m_pSprite->Draw(
				Shop_Items[i].m_pTex_Item,
				&Shop_Items[i].Item_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				D3DCOLOR_ARGB(200, 255, 255, 255));
			Shop_Items[i].m_pSprite->End();
		}


	}

	else
	{

	}
}

// garbage
//
////
//for (int i = 0; i < NumberOfItems; i++)
//{
//	if (g_pItem->Items[i].index == NULL)
//	{
//		continue;
//	}
//	Shop_Item.push_back(g_pItem->Items[i]);
//}

//for (int i = 0; i < NumberOfItems; i++)
//{
//	if (g_pItem->Items[i].index == NULL)
//	{
//		continue;
//	}
//	Shop_Item[i].Item_rc = RectMake(0, 0, 80 * i + Shop_Item[i].m_image_Item_Info.Width, Shop_Item[i].m_image_Item_Info.Height);
//	D3DXMatrixRotationZ(&matR, fAngle);
//	D3DXMatrixIdentity(&matT);
//	D3DXMatrixTranslation(&matT,
//		Shop_Item[i].PositionX,
//		Shop_Item[i].PositionY,
//		0);
//
//}
//
//for (int i = 0; i < 15; i++)
//{
//	SetRect(&Shop_Item[i].Item_rc, 0, 0, 80 * i + (Shop_Item[i].m_image_Item_Info.Width), 0 + (Shop_Item[i].m_image_Item_Info.Height /**temp*/));
//
//	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
//	m_pSprite->SetTransform(&matWorld[matWorld_ShopItem_1]);
//	m_pSprite->Draw(
//		Shop_Item[i].m_pTex_Item,
//		&Shop_Item[i].Item_rc,
//		&D3DXVECTOR3(0, 0, 0),
//		&D3DXVECTOR3(0, 0, 0),
//		WHITE);
//	// 이 부분에 대해 물어보기
//	m_pSprite->End();
//
//	SetRect(&Shop_Item[i].Click_rc, Shop_Item[i].PositionX
//		, Shop_Item[i].PositionY
//		, Shop_Item[i].PositionX + ((Shop_Item[i].m_image_Item_Info.Width)*ShopItem_Display_Mode_X)
//		, Shop_Item[i].PositionY + ((Shop_Item[i].m_image_Item_Info.Height)*ShopItem_Display_Mode_Y));
//
//}
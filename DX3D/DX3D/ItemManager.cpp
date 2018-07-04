#include "stdafx.h"
#include "ItemManager.h"


ItemManager* ItemManager::instance = NULL;

ItemManager * ItemManager::Get()
{

	if (instance == NULL)
		instance = new ItemManager();

	return instance;
}

void ItemManager::Delete()
{

	SAFE_DELETE(instance);
}

void ItemManager::ItemTable()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	GetClientRect(g_hWnd, &clientRect);

	ItemSizeX = 80;
	ItemSizeY = 80;
	EmptyRcX = ItemSizeX - 5;
	EmptyRcY = ItemSizeY - 5;

	Adjust_Display_Mode_X = ((float)clientRect.right - (float)clientRect.left) / (float)OriginX;
	Adjust_Display_Mode_Y = ((float)clientRect.bottom - (float)clientRect.top) / (float)OriginY;

	Basic_ScaleX = 0.3f;
	Basic_ScaleY = 0.3f;

	Weapons[0] = { 1,"wood",10,0,0,0 ,"resources/images/Weapon_Normal_1.png",1 };
//	Weapons[1] = { 2, "Gun", 15,20, 0, 0, "resources/images/Gun_.png",1 };


	Weapons[0].ScaleX = 0.3f;
	Weapons[0].ScaleY = 0.3f;
	Weapons[0].PositionX = (OriginX / 3) *Adjust_Display_Mode_X;
	Weapons[0].PositionY = (OriginY / 2) * Adjust_Display_Mode_Y;
	Weapons[0].isClicked = false;
	Weapons[0].isInvenIn = false;
	Weapons[0].isEquiped = false;
	Weapons[0].Equip_Type = Weapon_Type_LeftHand;
	for (int i = 0; i < NumberOfItems; i++)
	{
		if (Weapons[i].index == NULL)
		{
			continue;
		}
		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			Weapons[i].Filename,   //LPCTSTR pSrcFile,  파일명을 가져옴
						//이거 CString으로 선언한 변수에다 집어넣고
						// LPCTSTR로 받아서 쓰면
						// 변수로 집어넣어도 작동 됨

			D3DX_DEFAULT_NONPOW2,   //UINT Width,
			D3DX_DEFAULT_NONPOW2,   //UINT Height,
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&Weapons[i].m_image_Item_Info,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Weapons[i].m_pTex_Item);   //LPDIRECT3DTEXTURE9 *ppTexture
										  // 위에서 말한 경로에서 정보를 가져와서 m_image_info에 넣고
										  // 텍스쳐도 m_pTex에 저장

	}

}

void ItemManager::ItemGet(int a)
{
	RECT rect;

	

	//D3DXMatrixScaling(&matS, 1.f, 1.2f, 1);
	//D3DXMatrixTranslation(&matT, (WINSIZEX / 5) * 4, (WINSIZEY / 32) * 20, 0);
	//m_matWorld = matS * matT;
	timer = 400;

	//pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Item Get"));
	
	g_pInventory->addIndex(g_pItem->Weapons[a]);

}

void ItemManager::render(int a)
{

}



//InventoryManager * InventoryManager::Get()
//{
//
//	if (instance == NULL)
//		instance = new InventoryManager();
//
//	return instance;
//}
//
//void InventoryManager::Delete()
//{
//
//	SAFE_DELETE(instance);
//}
//
//
//ItemManager::ItemManager()
//{
//}
//
//
//ItemManager::~ItemManager()
//{
//}

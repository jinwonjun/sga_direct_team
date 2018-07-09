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

void ItemManager::getMonsterXY(int X, int Y)
{
	MonsterX = X;
	MonsterY = Y;
}

int ItemManager::SetX()
{
	return MonsterX;
}

int ItemManager::SetY()
{

	return MonsterY;
}

void ItemManager::MonsterDamaged(int DamageFontNum)
{
	FontNum = DamageFontNum;
	
	MonsterDamageTimer[DamageFontNum] = 40;


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

	
	Weapons[0] = { 1,  //인덱스, 아이템 번호
		"M4a1", // 이름
		15, // 공격력
		0, // HP
		0, // 현재 hp
		0, // 방어력
		"resources/images/Weapons/M4a1.png", //이미지 파일이름
		Weapon_Type_LeftHand, // 장비 타입
		false, //렉트 위에 오버되어있는가? -> 파란색 이팩트를 위해 사용 
		0, //복사 번호
		false, //클릭 되었는가?
		false, // 인벤 안에 있는가?
		(OriginX / 3) *Adjust_Display_Mode_X,// X 포지션
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y 포지션
		0.3f, // X 스케일
		0.3f, // Y 스케일
		false // 착용하고 있는가?		
	};

	Weapons[1] = { 2,  //인덱스, 아이템 번호
		"Beam_Gun", // 이름
		20, // 공격력
		0, // HP
		0, // 현재 hp
		5, // 방어력
		"resources/images/Weapons/Beam_Gun_MouseOver.png", //이미지 파일이름
		Weapon_Type_LeftHand, // 장비 타입
		false, //렉트 위에 오버되어있는가? -> 파란색 이팩트를 위해 사용 
		0, //복사 번호
		false, //클릭 되었는가?
		false, // 인벤 안에 있는가?
		(OriginX / 3) *Adjust_Display_Mode_X,// X 포지션
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y 포지션
		0.3f, // X 스케일
		0.3f, // Y 스케일
		false // 착용하고 있는가?		
	};

	Weapons[2] = { 3,  //인덱스, 아이템 번호
		"zod_gun", // 이름
		10, // 공격력
		0, // HP
		0, // 현재 hp
		0, // 방어력
		"resources/images/Weapons/zod_gun.png", //이미지 파일이름
		Weapon_Type_LeftHand, // 장비 타입
		false, //렉트 위에 오버되어있는가? -> 파란색 이팩트를 위해 사용 
		0, //복사 번호
		false, //클릭 되었는가?
		false, // 인벤 안에 있는가?
		(OriginX / 3) *Adjust_Display_Mode_X,// X 포지션
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y 포지션
		0.3f, // X 스케일
		0.3f, // Y 스케일
		false // 착용하고 있는가?		
	};


	//
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

	

	timer = 30;

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

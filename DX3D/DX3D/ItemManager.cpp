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


void ItemManager::ItemGet(int a)
{
	RECT rect;	

	timer = 30;

	//pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Item Get"));
	
	g_pInventory->addIndex(g_pItem->Items[a]);

}

void ItemManager::render(int a)
{

}



void ItemManager::init()
{
	ItemTable();

	for (int i = 0; i < 1; i++)
	{
		g_pInventory->addIndex(Items[i]);
	}

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


	Items[0] = { 1,  //인덱스, 아이템 번호
		"M4a1", // 이름
		15, // 공격력
		0, // HP
		0, // 현재 hp
		0, // 방어력
		"resources/images/Items/Weapons/M4a1.png", //이미지 파일이름
		"FPS에서 잘 보이는 그 총입니다. \n 점사로 많이 쏩니다.",
		Weapon_Type_MainWeapons, // 장비 타입
		false,//렉트 위에 오버되어있는가? -> 파란색 이팩트를 위해 사용 
		0, //복사 번호
		false, //클릭 되었는가?
		false, // 인벤 안에 있는가?
		(OriginX / 3) *Adjust_Display_Mode_X,// X 포지션
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y 포지션
		0.3f, // X 스케일
		0.3f, // Y 스케일
		false // 착용하고 있는가?		
	};

	Items[1] = { 2,  //인덱스, 아이템 번호
		"Beam_Gun", // 이름
		20, // 공격력
		0, // HP
		0, // 현재 hp
		5, // 방어력
		"resources/images/Items/Weapons/Beam_Gun_MouseOver.png", //이미지 파일이름
		"방어형 총입니다. \n 약간의 방어력을 올려줍니다.",
		Weapon_Type_MainWeapons, // 장비 타입
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

	Items[2] = { 3,  //인덱스, 아이템 번호
		"zod_gun", // 이름
		10, // 공격력
		0, // HP
		0, // 현재 hp
		0, // 방어력
		"resources/images/Items/Weapons/zod_gun.png", //이미지 파일이름
		"약한 총입니다. \n없는것 보단 낫습니다.",
		Weapon_Type_MainWeapons, // 장비 타입
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

	Items[3] = { 4,  //인덱스, 아이템 번호
		"G.Armor", // 이름
		0, // 공격력
		30, // HP
		0, // 현재 hp
		10, // 방어력
		"resources/images/Items/Armor/Leather_Good_Armor.png", //이미지 파일이름
		"가죽 갑옷입니다.",
		Weapon_Type_Armor, // 장비 타입
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

	Items[4] = { 5,  //인덱스, 아이템 번호
		"B.Armor", // 이름
		0, // 공격력
		40, // HP
		0, // 현재 hp
		15, // 방어력
		"resources/images/Items/Armor/Leather_Better_Armor.png", //이미지 파일이름
		"가죽으로 만든 전투 방어구입니다.",
		Weapon_Type_Armor, // 장비 타입
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
	Items[5] = { 6,  //인덱스, 아이템 번호
		"K.Armor", // 이름
		0, // 공격력
		60, // HP
		0, // 현재 hp
		40, // 방어력
		"resources/images/Items/Armor/Leather_Great_Armor.png", //이미지 파일이름
		"죽지 않는 캐릭터를 \n만들기 위한 방어구입니다.",
		Weapon_Type_Armor, // 장비 타입
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
	// 6,7,8 장갑 
	Items[6] = { 7,  //인덱스, 아이템 번호
		"노목", // 이름
		5, // 공격력
		0, // HP
		0, // 현재 hp
		0, // 방어력
		"resources/images/Items/Gloves/Glove_NoMok.png", //이미지 파일이름
		"옛날 그 게임에서 \n인기가 많던 장갑입니다. \n 100 % 5장이 발려있습니다.",
		Weapon_Type_Glove, // 장비 타입
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
	Items[7] = { 8,  //인덱스, 아이템 번호
		"K2Glove", // 이름
		0, // 공격력
		0, // HP
		0, // 현재 hp
		5, // 방어력
		"resources/images/Items/Gloves/K2_Glove.png", //이미지 파일이름
		"국군이 일할때 많이 씁니다. \n작업에 필수입니다.",
		Weapon_Type_Glove, // 장비 타입
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
	Items[8] = { 9,  //인덱스, 아이템 번호
		"B.Glove", // 이름
		10, // 공격력
		0, // HP
		0, // 현재 hp
		15, // 방어력
		"resources/images/Items/Gloves/Glove_battle.png", //이미지 파일이름
		"전투를 위한 장갑입니다. \n불편합니다.",
		Weapon_Type_Glove, // 장비 타입
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
	// 9,10,11 벨트
	Items[9] = { 10,  //인덱스, 아이템 번호
		"B.Belt", // 이름
		0, // 공격력
		10, // HP
		0, // 현재 hp
		5, // 방어력
		"resources/images/Items/Belt/Belt_Black.png", //이미지 파일이름
		"검은 벨트입니다.\n다용도로 쓰입니다.",
		Weapon_Type_Belt, // 장비 타입
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
	// 9,10,11 벨트
	Items[10] = { 11,  //인덱스, 아이템 번호
		"TanDDe", // 이름
		0, // 공격력
		10, // HP
		0, // 현재 hp
		-5, // 방어력
		"resources/images/Items/Belt/Belt_ArmyBelt.png", //이미지 파일이름
		"많은 분들이 싫어하는 그것입니다.",
		Weapon_Type_Belt, // 장비 타입
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
	// 9,10,11 벨트
	Items[11] = { 12,  //인덱스, 아이템 번호
		"K.G.Belt", // 이름
		0, // 공격력
		10, // HP
		0, // 현재 hp
		-5, // 방어력
		"resources/images/Items/Belt/Belt_King_God.png", //이미지 파일이름
		"왜 이런 이름이 \n붙었는지 모릅니다.",
		Weapon_Type_Belt, // 장비 타입
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

	// 12,13,14 부츠
	Items[12] = { 13,  //인덱스, 아이템 번호
		"Boots.S", // 이름
		0, // 공격력
		10, // HP
		0, // 현재 hp
		5, // 방어력
		"resources/images/Items/Boots/Boots_Shoe.png", //이미지 파일이름
		"신기 편한 신발입니다.",
		Weapon_Type_Boots, // 장비 타입
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

	// 12,13,14 부츠
	Items[13] = { 14,  //인덱스, 아이템 번호
		"Boots.R", // 이름
		0, // 공격력
		10, // HP
		0, // 현재 hp
		15, // 방어력
		"resources/images/Items/Boots/Boots_Race.png", //이미지 파일이름
		"Race에 쓰일것만같은 신발입니다.",
		Weapon_Type_Boots, // 장비 타입
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

	Items[14] = { 15,  //인덱스, 아이템 번호
		"Boots.B", // 이름
		5, // 공격력
		5, // HP
		0, // 현재 hp
		5, // 방어력
		"resources/images/Items/Boots/Boots_Brown.png", //이미지 파일이름
		"갈색신발입니다.",
		Weapon_Type_Boots, // 장비 타입
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
		if (Items[i].index == NULL)
		{
			continue;
		}
		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			Items[i].Filename,   //LPCTSTR pSrcFile,  파일명을 가져옴
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
			&Items[i].m_image_Item_Info,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Items[i].m_pTex_Item);   //LPDIRECT3DTEXTURE9 *ppTexture
										// 위에서 말한 경로에서 정보를 가져와서 m_image_info에 넣고
										// 텍스쳐도 m_pTex에 저장
	}

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

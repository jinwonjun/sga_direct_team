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


	Items[0] = { 1,  //�ε���, ������ ��ȣ
		"M4a1", // �̸�
		15, // ���ݷ�
		0, // HP
		0, // ���� hp
		0, // ����
		"resources/images/Items/Weapons/M4a1.png", //�̹��� �����̸�
		Weapon_Type_MainWeapons, // ��� Ÿ��
		false, //��Ʈ ���� �����Ǿ��ִ°�? -> �Ķ��� ����Ʈ�� ���� ��� 
		0, //���� ��ȣ
		false, //Ŭ�� �Ǿ��°�?
		false, // �κ� �ȿ� �ִ°�?
		(OriginX / 3) *Adjust_Display_Mode_X,// X ������
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y ������
		0.3f, // X ������
		0.3f, // Y ������
		false // �����ϰ� �ִ°�?		
	};

	Items[1] = { 2,  //�ε���, ������ ��ȣ
		"Beam_Gun", // �̸�
		20, // ���ݷ�
		0, // HP
		0, // ���� hp
		5, // ����
		"resources/images/Items/Weapons/Beam_Gun_MouseOver.png", //�̹��� �����̸�
		Weapon_Type_MainWeapons, // ��� Ÿ��
		false, //��Ʈ ���� �����Ǿ��ִ°�? -> �Ķ��� ����Ʈ�� ���� ��� 
		0, //���� ��ȣ
		false, //Ŭ�� �Ǿ��°�?
		false, // �κ� �ȿ� �ִ°�?
		(OriginX / 3) *Adjust_Display_Mode_X,// X ������
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y ������
		0.3f, // X ������
		0.3f, // Y ������
		false // �����ϰ� �ִ°�?		
	};

	Items[2] = { 3,  //�ε���, ������ ��ȣ
		"zod_gun", // �̸�
		10, // ���ݷ�
		0, // HP
		0, // ���� hp
		0, // ����
		"resources/images/Items/Weapons/zod_gun.png", //�̹��� �����̸�
		Weapon_Type_MainWeapons, // ��� Ÿ��
		false, //��Ʈ ���� �����Ǿ��ִ°�? -> �Ķ��� ����Ʈ�� ���� ��� 
		0, //���� ��ȣ
		false, //Ŭ�� �Ǿ��°�?
		false, // �κ� �ȿ� �ִ°�?
		(OriginX / 3) *Adjust_Display_Mode_X,// X ������
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y ������
		0.3f, // X ������
		0.3f, // Y ������
		false // �����ϰ� �ִ°�?		
	};

	Items[3] = { 4,  //�ε���, ������ ��ȣ
		"Leather_Good_Armor", // �̸�
		0, // ���ݷ�
		30, // HP
		0, // ���� hp
		10, // ����
		"resources/images/Items/Armor/Leather_Good_Armor.png", //�̹��� �����̸�
		Weapon_Type_Armor, // ��� Ÿ��
		false, //��Ʈ ���� �����Ǿ��ִ°�? -> �Ķ��� ����Ʈ�� ���� ��� 
		0, //���� ��ȣ
		false, //Ŭ�� �Ǿ��°�?
		false, // �κ� �ȿ� �ִ°�?
		(OriginX / 3) *Adjust_Display_Mode_X,// X ������
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y ������
		0.3f, // X ������
		0.3f, // Y ������
		false // �����ϰ� �ִ°�?		
	};

	Items[4] = { 5,  //�ε���, ������ ��ȣ
		"Leather_Better_Armor", // �̸�
		0, // ���ݷ�
		40, // HP
		0, // ���� hp
		15, // ����
		"resources/images/Items/Armor/Leather_Better_Armor.png", //�̹��� �����̸�
		Weapon_Type_Armor, // ��� Ÿ��
		false, //��Ʈ ���� �����Ǿ��ִ°�? -> �Ķ��� ����Ʈ�� ���� ��� 
		0, //���� ��ȣ
		false, //Ŭ�� �Ǿ��°�?
		false, // �κ� �ȿ� �ִ°�?
		(OriginX / 3) *Adjust_Display_Mode_X,// X ������
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y ������
		0.3f, // X ������
		0.3f, // Y ������
		false // �����ϰ� �ִ°�?		
	};
	Items[5] = { 6,  //�ε���, ������ ��ȣ
		"Leather_Great_Armor", // �̸�
		0, // ���ݷ�
		60, // HP
		0, // ���� hp
		40, // ����
		"resources/images/Items/Armor/Leather_Great_Armor.png", //�̹��� �����̸�
		Weapon_Type_Armor, // ��� Ÿ��
		false, //��Ʈ ���� �����Ǿ��ִ°�? -> �Ķ��� ����Ʈ�� ���� ��� 
		0, //���� ��ȣ
		false, //Ŭ�� �Ǿ��°�?
		false, // �κ� �ȿ� �ִ°�?
		(OriginX / 3) *Adjust_Display_Mode_X,// X ������
		(OriginY / 2) * Adjust_Display_Mode_Y, // Y ������
		0.3f, // X ������
		0.3f, // Y ������
		false // �����ϰ� �ִ°�?		
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
			Items[i].Filename,   //LPCTSTR pSrcFile,  ���ϸ��� ������
								   //�̰� CString���� ������ �������� ����ְ�
								   // LPCTSTR�� �޾Ƽ� ����
								   // ������ ����־ �۵� ��

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
										// ������ ���� ��ο��� ������ �����ͼ� m_image_info�� �ְ�
										// �ؽ��ĵ� m_pTex�� ����

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

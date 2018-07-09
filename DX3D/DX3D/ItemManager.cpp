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

	
	Weapons[0] = { 1,  //�ε���, ������ ��ȣ
		"M4a1", // �̸�
		15, // ���ݷ�
		0, // HP
		0, // ���� hp
		0, // ����
		"resources/images/Weapons/M4a1.png", //�̹��� �����̸�
		Weapon_Type_LeftHand, // ��� Ÿ��
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

	Weapons[1] = { 2,  //�ε���, ������ ��ȣ
		"Beam_Gun", // �̸�
		20, // ���ݷ�
		0, // HP
		0, // ���� hp
		5, // ����
		"resources/images/Weapons/Beam_Gun_MouseOver.png", //�̹��� �����̸�
		Weapon_Type_LeftHand, // ��� Ÿ��
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

	Weapons[2] = { 3,  //�ε���, ������ ��ȣ
		"zod_gun", // �̸�
		10, // ���ݷ�
		0, // HP
		0, // ���� hp
		0, // ����
		"resources/images/Weapons/zod_gun.png", //�̹��� �����̸�
		Weapon_Type_LeftHand, // ��� Ÿ��
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
		if (Weapons[i].index == NULL)
		{
			continue;
		}
		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			Weapons[i].Filename,   //LPCTSTR pSrcFile,  ���ϸ��� ������
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
			&Weapons[i].m_image_Item_Info,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Weapons[i].m_pTex_Item);   //LPDIRECT3DTEXTURE9 *ppTexture
										  // ������ ���� ��ο��� ������ �����ͼ� m_image_info�� �ְ�
										  // �ؽ��ĵ� m_pTex�� ����

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

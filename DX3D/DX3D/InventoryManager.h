#pragma once

#include "ItemManager.h"
#define INVENCORSS 6
#define INVENVERTI 4
#define INVENITEMSTART_X 1000
#define INVENITEMSTART_Y 420

#define g_pInventory  InventoryManager::Get()

//#define DOUBLE_FOR \
//	for (int j = 0; j < INVENVERTI; j++) \
//	{  \
//		for (int i = 0; i < INVENCORSS; i++) \
//	{
//
//#define DOUBLE_FOR_END  }}
//	



struct Inven_UI
{

	float ScaleX;
	float ScaleY;
	float PositionX;
	float PositionY;
	bool  isEquiped;
	LPDIRECT3DTEXTURE9	 m_pTex;
	D3DXIMAGE_INFO		 m_image;
	RECT				 m_rc;
	RECT				 m_rc_click;

};



enum Equip_Type
{
	Equip_Main_Weapon_1 = 1,
	Equip_Sub_Weapon_2,
	Equip_Amor,
	Equip_Belt,
	Equip_Glove,
	Equip_Boots	
};

enum matWorld_Numbering
{
	matWorld_Inven,
	matWorld_Inven_Chara,
	matWorld_ItemSet,
	matWorld_ShopItem_1,
	matWorld_ShopItem_2,
	matWorld_Main_Weapon,
	matWorld_MouseCursor,
	

};

class InventoryManager : public ItemManager
{
	//SINGLETON(InventoryManager)
private:

	static InventoryManager* instance;
	
	std::wstring temp;

	POINT mousePoint; //���콺 ����Ʈ ��ġ�� �������� ���ؼ�
	LPD3DXSPRITE m_pSprite;

	D3DXMATRIXA16 matR, matT, matS;
	
	Inven_UI Inventory;
	Inven_UI Inventory_Chara;
	Inven_UI ItemSet;
	Inven_UI MouseCursor_Normal;
	Inven_UI MousCursor_ClickedOn;

	//�ش� �κ��丮�� �ö� �� �������� �̰���

	Inven_UI Inventory_on;


	std::vector<items> inventory; //�κ��丮�� ������ �ֱ�




	RECT clientRect; // ������ ��ü â 
	int preChosenX; // ������ ������ ��ǥ�� �����ϱ� ���� ��
	int preChosenY; // ���� ����
	bool pressOn; // �������� �ִ����� Ȯ���ϴ� ����

	int CrossX;  // ������
	int VertiY;  // ������ 

	int ItemSizeX; // ������ ��ĭ�� ������
	int ItemSizeY; // ������ ��ĭ�� ������

	bool EscapeFor; //���� Ż���ϱ� ���� �Ұ�
	D3DXMATRIXA16 matWorld[10];
	D3DXMATRIXA16 matWorld_InvenItems[INVENCORSS*INVENVERTI];
	bool alreadyWorkedRbutton;// �������� �̹� ����Ǿ������� üũ. 
							  // ���׸� �����༭ �־��µ� ��� ���Ҵ��� ��� �� ��� �ȳ�.
							  // �Ƹ� ���� 

	float Adjust_Display_Mode_X; //�ػ� ���濡 ���� ���� �������ִ� ����
	float Adjust_Display_Mode_Y; //�ػ� ���濡 ���� ���� �������ִ� ����
	float Basic_ScaleX;
	float Basic_ScaleY;
	float ShopItem_Display_Mode_X;//�ػ� ���濡 ���� ���� �������ִ� ����
	float ShopItem_Display_Mode_Y;//�ػ� ���濡 ���� ���� �������ִ� ����

	int EmptyRcX;
	int EmptyRcY;

public:
	//Inventory();
	//~Inventory();


	static InventoryManager* Get();
	static void Delete();

	bool GetalreadyWorkedRbutton() { return alreadyWorkedRbutton;  }
	//void SetalreadyWorkedRbutton(bool acb) { alreadyWorkedRbutton = acb; }
	// �� �� �򰥷�
	
	// IDisplayObject��(��) ���� ��ӵ�
	void Init();
	void Update();
	void Render() ;


	int EquipData;
	// IUIButtonDelegate��(��) ���� ��ӵ�

	std::vector<items> Equip;

	std::vector<items> Shop_Item;//���丮�� �ѱ� ���

	items Void_Item[INVENCORSS][INVENVERTI];
	// ������ ������... �ʱⰪ�� ���̺� ���ѵα� ���ؼ� ����Ѵ�...
	// ��� �迭�� ���� �ʿ� ���� �ϳ��� �ص� ���� ������ �ͱ� �ߴµ� ...
	// �ε������̶���� �迭 ��ġ�� �ٽ� �������ߵǼ� ... 
	
	RECT InventorRect[10];
	items InvenArray[INVENCORSS][INVENVERTI];
	//�κ��丮 ���ο�, ���ο� ��

	bool openInven;
	// �κ��� ���ȴ°�? ��������, ���콺 �� �����ϰ� Ŀ���� ���̰� �ϱ� ���ؼ� ���

	bool SwapDoor;
	// �����ϴ� ���� ���Ǿ��°�? 
	// �̰� ���� �������� ���� �ߴµ� ������ ...

	bool Endfor;
	// ���� ������ �����Ѵ�.

	void addIndex(items a); // �κ��丮�� ������ �ֱ�
	//void addIndex(items a, int b); // �κ��丮�� ������ �ֱ�

	void MovingItem(items* a, items* b); // �κ��丮 ������ ������ �ű�� ������ ���� ...
	
};


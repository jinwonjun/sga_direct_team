#pragma once

#include "ItemManager.h"
#include "UIText.h"
#include "UIButton.h"

#define INVENCORSS 6
#define INVENVERTI 4
#define INVENITEMSTART_X 1000
#define INVENITEMSTART_Y 420
#define NumOfItemTextKind 6
#define g_pInventory  InventoryManager::Get()


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
	Equip_Armor,	
	Equip_Glove,
	Equip_Sub_Weapon_2,
	Equip_Belt,
	Equip_Boots	
};

enum matWorld_Numbering
{
	matWorld_Inven,
	matWorld_Inven_Chara,
	matWorld_Equiped_Side,
	matWorld_Exit_Button,
	matWorld_Item_Info,
	matWorld_ItemSet,
	matWorld_ShopItem_1,
	matWorld_ShopItem_2,
	matWorld_Main_Weapon,
	matWorld_Armor,
	matWorld_Glove,
	matWorld_Sub_Weapon2,
	matWorld_Belt,
	matWorld_Boots,
	matWorld_MouseCursor,
	matWorld_MouseOver,
	matWorld_Equiped_Item, // 21����

	matWorld_Equiped_Item_Black = 25,

	matWorld_InvenArray =40

};

enum Item_Info_Names
{
	ItemName,
	ATK,
	DEF,
	MHP,
	Script,
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
	Inven_UI Exit_Button;
	Inven_UI Equiped_Side;
	Inven_UI Equiped_Item[6];
	Inven_UI Equiped_Item_BlackBack[6];
	Inven_UI Item_Info_Back;

	//�ش� �κ��丮�� �ö� �� �������� �̰���

	Inven_UI Inventory_on;

	// equip �̸� 

	D3DXMATRIXA16	m_matWorld_Euip_Name_text[6];
	LPD3DXSPRITE m_pSprite_Equip[6];
	IUIObject * m_pRootUI_Euip_Text[6];	
	RECT    Equip_Name_Rect[6];
	CString Equip_Name_Text[6];
	UIButton * Equip_Name[6];
	IUIButtonDelegate * m_pDelegate_Equip_Name[6];


	D3DXMATRIXA16	m_matWorld_Item_Info[NumOfItemTextKind];
	LPD3DXSPRITE m_pSprite_Item_Info[NumOfItemTextKind];
	IUIObject *		m_pRootUI_Item_Info[NumOfItemTextKind];
	CString			cstr_Item_Info[NumOfItemTextKind];
	UIButton * Item_Info[NumOfItemTextKind];
	IUIButtonDelegate * m_pDelegate_Item_Info[NumOfItemTextKind];

	float Item_Info_PositionX[NumOfItemTextKind];
	float Item_Info_PositionY[NumOfItemTextKind];
	


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
	D3DXMATRIXA16 matWorld[60];
	D3DXMATRIXA16 matWorld_InvenItems[matWorld_InvenArray+INVENCORSS*INVENVERTI];
	bool alreadyWorkedRbutton;// �������� �̹� ����Ǿ������� üũ. 
							  // ���׸� �����༭ �־��µ� ��� ���Ҵ��� ��� �� ��� �ȳ�.
							  // �Ƹ� ���� 

	float Adjust_Display_Mode_X; //�ػ� ���濡 ���� ���� �������ִ� ����
	float Adjust_Display_Mode_Y; //�ػ� ���濡 ���� ���� �������ִ� ����
	float Basic_ScaleX;
	float Basic_ScaleY;
	float ShopItem_Display_Mode_X;//�ػ� ���濡 ���� ���� �������ִ� ����
	float ShopItem_Display_Mode_Y;//�ػ� ���濡 ���� ���� �������ִ� ����

	//���콺 ������ ������ ������ �����ִ� ������ ��ǥ�� ������.
	float ItemInfoBack_PositionX;
	float ItemInfoBack_PositionY;
	float ItemInfoBack_ScaleX;
	float ItemInfoBack_ScaleY;

	int EmptyRcX;
	int EmptyRcY;

	int Column;
	int Cross;
	int fitstColumn;
	int SecondColumn;

	void Weapon_Equip_Text();
	void Item_Info_Text();
	void Item_Info_Description(items item);
	

	

public:
	//Inventory();
	//~Inventory();


	static InventoryManager* Get();
	static void Delete();

//	LPD3DXSPRITE Get_m_pSprite_Equip() { return m_pSprite_Equip; }
	CString Get_Equip_Name_Text(int i) { return Equip_Name_Text[i];	}
	RECT Get_Equip_Rect(int i) {	return Equip_Name_Rect[i];	}
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
	

	 //IUnit�� ������ ���Ŀ� ���� �����
	int AnswerDmg;
};


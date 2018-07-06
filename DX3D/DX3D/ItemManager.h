#pragma once

#define NumberOfItems 10

#define g_pItem ItemManager::Get()

struct items {

	int index;  //������ ��ȣ
	char* name; // �̸�
	int Atk;    // ���ݷ�
	int MaxHp;	// HP
	int Hp;     // ���� HP
	int Def;    // ����
	CString Filename;

	
	int Equip_Type;  // ������ ���� Ÿ��. �̳����� ���� �ο�


	bool isInvenOver; // ���� �ö� �ִ°�?



	int Copy_num;    // �� ��° ����� �������ΰ�?
	bool  isClicked; // Ŭ�� �Ǿ��°�?
	bool  isInvenIn; // �κ��丮 �ȿ� �ִ°�?
	float PositionX; // rc�� �� ��ġ
	float PositionY; // rc�� �� ��ġ
	float ScaleX;    // X�� ��ĳ��
	float ScaleY;    // Y�� ��ĳ��
	bool isEquiped;


	RECT Item_rc;    // �̹����� ���� ��Ʈ
	RECT Click_rc;   // Ŭ������ �����ϴ� ��Ʈ
	RECT isInven_rc;
	RECT isInven_show_rc;

	D3DXIMAGE_INFO		 m_image_Item_Info; // �̹��� ����
	D3DXIMAGE_INFO		 m_image_InvenOn_Info;

	LPDIRECT3DTEXTURE9	 m_pTex_Item;       // �ؽ��� ����
	LPDIRECT3DTEXTURE9	 m_pTex_InvenOn;
};

// �̳ѹ����� 1���� 6���� �������ش�.
enum Weapon_Types_
{
	Weapon_Type_LeftHand = 1,
	Weapon_Type_RightHand,
	Weapon_Type_Amor,
	Weapon_Type_Belt,
	Weapon_Type_Glove,
	Weapon_Type_Boots
};

class ItemManager 
{
private:
	
	static ItemManager* instance;
	LPD3DXSPRITE m_pSprite;

	RECT clientRect; // ������ ��ü â 
	float Adjust_Display_Mode_X; //�ػ� ���濡 ���� ���� �������ִ� ����
	float Adjust_Display_Mode_Y; //�ػ� ���濡 ���� ���� �������ִ� ����
	float Basic_ScaleX;
	float Basic_ScaleY;

	float ShopItem_Display_Mode_X;//�ػ� ���濡 ���� ���� �������ִ� ����
	float ShopItem_Display_Mode_Y;//�ػ� ���濡 ���� ���� �������ִ� ����

	int ItemSizeX; // ������ ��ĭ�� ������
	int ItemSizeY; // ������ ��ĭ�� ������

	int EmptyRcX;
	int EmptyRcY;

	D3DXMATRIXA16 matS;
	D3DXMATRIXA16 matT;
	D3DXMATRIXA16 m_matWorld;

	
	int MonsterX;
	int MonsterY;
	bool MonsterDead;
	

public:

	static ItemManager* Get();
	static void Delete();


	int timer;
	items Weapons[NumberOfItems];
	void getMonsterXY(int X, int Y);
	//void SetXY(int *X, int *Y);
	int SetX();
	int SetY();
	int MonsterDamageTimer[20];
	void MonsterDamaged(int DamageFontNum);
	int FontNum;
	bool FontController[20];


	void ItemTable();
	void ItemGet(int a);
	void render(int a);
	// IDisplayObject��(��) ���� ��ӵ�


};

//class ItemManager
//{
//private:
//	
//	//static ItemManager*
//
//
//public:
//	ItemManager();
//	~ItemManager();
//};


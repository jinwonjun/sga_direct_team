#pragma once
#include "IDisplayObject.h"
#define NumberOfItems 10

#define g_pItem ItemManager::Get()

<<<<<<< HEAD
//struct items {
//
//	int index;  //������ ��ȣ
//	char* name; // �̸�
//	int Atk;    // ���ݷ�
//	int MaxHp;	// HP
//	int Hp;     // ���� HP
//	int Def;    // ����
//	CString Filename;
//
//	
//	int Equip_Type;  // ������ ���� Ÿ��. �̳����� ���� �ο�
//
//
//	bool isInvenOn;
//	RECT Item_rc;    // �̹����� ���� ��Ʈ
//	RECT Click_rc;   // Ŭ������ �����ϴ� ��Ʈ
//	RECT isInven_rc;
//	RECT isInven_show_rc;
//
//
//	int Copy_num;    // �� ��° ����� �������ΰ�?
//	bool  isClicked; // Ŭ�� �Ǿ��°�?
//	bool  isInvenIn; // �κ��丮 �ȿ� �ִ°�?
//	float PositionX; // rc�� �� ��ġ
//	float PositionY; // rc�� �� ��ġ
//	float ScaleX;    // X�� ��ĳ��
//	float ScaleY;    // Y�� ��ĳ��
//
//	D3DXIMAGE_INFO		 m_image_Item_Info; // �̹��� ����
//	D3DXIMAGE_INFO		 m_image_InvenOn_Info;
//
//	LPDIRECT3DTEXTURE9	 m_pTex_Item;       // �ؽ��� ����
//	LPDIRECT3DTEXTURE9	 m_pTex_InvenOn;
//};

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

class ItemManager : public IDisplayObject
{
private:
	
	static ItemManager* instance;
	


public:

	static ItemManager* Get();
	static void Delete();

	items Weapons[NumberOfItems];

	void ItemTable();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

};
=======
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
>>>>>>> 0415652514d450b1f76eac62648af3ead5fbec42


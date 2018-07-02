#pragma once
#include "IDisplayObject.h"
#define NumberOfItems 10

#define g_pItem ItemManager::Get()

<<<<<<< HEAD
//struct items {
//
//	int index;  //아이템 번호
//	char* name; // 이름
//	int Atk;    // 공격력
//	int MaxHp;	// HP
//	int Hp;     // 지금 HP
//	int Def;    // 방어력
//	CString Filename;
//
//	
//	int Equip_Type;  // 아이템 장착 타입. 이넘으로 숫자 부여
//
//
//	bool isInvenOn;
//	RECT Item_rc;    // 이미지를 담을 렉트
//	RECT Click_rc;   // 클릭으로 반응하는 렉트
//	RECT isInven_rc;
//	RECT isInven_show_rc;
//
//
//	int Copy_num;    // 몇 번째 복사된 아이템인가?
//	bool  isClicked; // 클릭 되었는가?
//	bool  isInvenIn; // 인벤토리 안에 있는가?
//	float PositionX; // rc가 들어갈 위치
//	float PositionY; // rc가 들어갈 위치
//	float ScaleX;    // X축 스캐일
//	float ScaleY;    // Y축 스캐일
//
//	D3DXIMAGE_INFO		 m_image_Item_Info; // 이미지 정보
//	D3DXIMAGE_INFO		 m_image_InvenOn_Info;
//
//	LPDIRECT3DTEXTURE9	 m_pTex_Item;       // 텍스쳐 정보
//	LPDIRECT3DTEXTURE9	 m_pTex_InvenOn;
//};

// 이넘문으로 1부터 6까지 선언해준다.
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

	// IDisplayObject을(를) 통해 상속됨
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


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

	POINT mousePoint; //마우스 포인트 위치를 가져오기 위해서
	LPD3DXSPRITE m_pSprite;

	D3DXMATRIXA16 matR, matT, matS;
	
	Inven_UI Inventory;
	Inven_UI Inventory_Chara;
	Inven_UI ItemSet;
	Inven_UI MouseCursor_Normal;
	Inven_UI MousCursor_ClickedOn;

	//해당 인벤토리에 올라갈 것 같을때는 이것을

	Inven_UI Inventory_on;


	std::vector<items> inventory; //인벤토리에 아이템 넣기




	RECT clientRect; // 윈도우 전체 창 
	int preChosenX; // 기존에 선택한 좌표를 저장하기 위한 값
	int preChosenY; // 위랑 같은
	bool pressOn; // 눌러지고 있는지를 확인하는 아이

	int CrossX;  // 가로축
	int VertiY;  // 세로축 

	int ItemSizeX; // 아이템 한칸당 사이즈
	int ItemSizeY; // 아이템 한칸당 사이즈

	bool EscapeFor; //포문 탈출하기 위한 불값
	D3DXMATRIXA16 matWorld[10];
	D3DXMATRIXA16 matWorld_InvenItems[INVENCORSS*INVENVERTI];
	bool alreadyWorkedRbutton;// 아이템이 이미 착용되었는지를 체크. 
							  // 버그를 막아줘서 넣었는데 어떻게 막았는지 사실 잘 기억 안남.
							  // 아마 우측 

	float Adjust_Display_Mode_X; //해상도 변경에 따라 비율 조절해주는 아이
	float Adjust_Display_Mode_Y; //해상도 변경에 따라 비율 조절해주는 아이
	float Basic_ScaleX;
	float Basic_ScaleY;
	float ShopItem_Display_Mode_X;//해상도 변경에 따라 비율 조절해주는 아이
	float ShopItem_Display_Mode_Y;//해상도 변경에 따라 비율 조절해주는 아이

	int EmptyRcX;
	int EmptyRcY;

public:
	//Inventory();
	//~Inventory();


	static InventoryManager* Get();
	static void Delete();

	bool GetalreadyWorkedRbutton() { return alreadyWorkedRbutton;  }
	//void SetalreadyWorkedRbutton(bool acb) { alreadyWorkedRbutton = acb; }
	// 겟 셋 헷갈령
	
	// IDisplayObject을(를) 통해 상속됨
	void Init();
	void Update();
	void Render() ;


	int EquipData;
	// IUIButtonDelegate을(를) 통해 상속됨

	std::vector<items> Equip;

	std::vector<items> Shop_Item;//햄토리랑 총기 모양

	items Void_Item[INVENCORSS][INVENVERTI];
	// 공허의 아이템... 초기값을 세이브 시켜두기 위해서 사용한다...
	// 사실 배열로 만들 필요 없이 하나만 해도 되지 않을까 싶긴 했는뎅 ...
	// 인덱스값이라던가 배열 위치를 다시 계산해줘야되서 ... 
	
	RECT InventorRect[10];
	items InvenArray[INVENCORSS][INVENVERTI];
	//인벤토리 가로열, 세로열 등

	bool openInven;
	// 인벤이 열렸는가? 열렸으면, 마우스 락 해제하고 커서를 보이게 하기 위해서 사용

	bool SwapDoor;
	// 스왑하는 문이 사용되었는가? 
	// 이거 내가 뭐떄문에 쓰긴 했는데 뭐더라 ...

	bool Endfor;
	// 포문 종결을 선언한다.

	void addIndex(items a); // 인벤토리에 아이템 넣기
	//void addIndex(items a, int b); // 인벤토리에 아이템 넣기

	void MovingItem(items* a, items* b); // 인벤토리 내에서 아이템 옮기기 하지만 실패 ...
	
};


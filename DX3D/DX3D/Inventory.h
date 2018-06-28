#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#define INVENCORSS 6
#define INVENVERTI 4
#define INVENITEMSTART_X 1000
#define INVENITEMSTART_Y 420



struct items {

	int index;  //아이템 번호
	char* name; // 이름
	int Atk;    // 공격력
	int MaxHp;	// HP
	int Hp;     // 지금 HP
	int Def;    // 방어력

	float PositionX; // rc가 들어갈 위치
	float PositionY; // rc가 들어갈 위치
	float ScaleX;    // X축 스캐일
	float ScaleY;    // Y축 스캐일
	bool  isClicked; // 클릭 되었는가?
	bool  isInvenIn; // 인벤토리 안에 있는가?

	int Copy_num;    // 몇 번째 복사된 아이템인가?
	int Equip_Type;  // 아이템 장착 타입. 이넘으로 숫자 부여


	bool isInvenOn;
	RECT Item_rc;    // 이미지를 담을 렉트
	RECT Click_rc;   // 클릭으로 반응하는 렉트
	RECT isInven_rc;
	RECT isInven_show_rc;

	D3DXIMAGE_INFO		 m_image_Item_Info; // 이미지 정보
	D3DXIMAGE_INFO		 m_image_InvenOn_Info;

	LPDIRECT3DTEXTURE9	 m_pTex_Item;       // 텍스쳐 정보
	LPDIRECT3DTEXTURE9	 m_pTex_InvenOn;
};

// 이넘문으로 1부터 6까지 선언해준다.
enum Weapon_Type
{
	Weapon_Type_LeftHand = 1,
	Weapon_Type_RightHand,
	Weapon_Type_Amor,
	Weapon_Type_Belt,
	Weapon_Type_Glove,
	Weapon_Type_Boots

};

enum matWorld_Numbering
{
	matWorld_Inven,
	matWorld_Inven_Chara,
	matWorld_ItemSet,
	matWorld_ShopItem_1,
	matWorld_ShopItem_2,
	matWorld_Equip_LeftHand,
	matWorld_MouseCursor,

};
class IUIObject;
class Inventory : public IDisplayObject, public IUIButtonDelegate
{

private:
	std::wstring temp;


	POINT mousePoint; //마우스 포인트 위치를 가져오기 위해서
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pRootUI;


	D3DXMATRIXA16 matR, matT, matS;


	D3DXMATRIXA16 matWorld_2;//실험체 .... 쓸모가 없었다고 한다.

							 //인벤토리 텍스쳐와 이미지 인포와 렉트
	LPDIRECT3DTEXTURE9	 m_pTex_Inventory;
	D3DXIMAGE_INFO		 m_image_Inventory_info;
	RECT				 m_rc_Inventory;

	LPDIRECT3DTEXTURE9	 m_pTex_Inventory_Chara;
	D3DXIMAGE_INFO		 m_image_Inventory_Chara_info;
	RECT				 m_rc_Inventory_Chara;


	std::vector<items> Shop_Item;//햄토리랑 총기 모양

	LPDIRECT3DTEXTURE9	 m_pTex_ItemSet;
	D3DXIMAGE_INFO		 m_image_ItemSet_info;
	RECT				 m_rc_ItemSet;


	LPDIRECT3DTEXTURE9	 m_pTex_MouseCursor_Normal;
	D3DXIMAGE_INFO		 m_image_MouseCursor_Normal_info;
	RECT				 m_rc_MouseCursor_Normal;

	LPDIRECT3DTEXTURE9	 m_pTex_MouseCursor_ClickedOn;
	D3DXIMAGE_INFO		 m_image_MouseCursor_ClickedOn_info;
	RECT				 m_rc_MouseCursor_ClickedOn;


	//해당 인벤토리에 올라갈 것 같을때는 이것을
	LPDIRECT3DTEXTURE9	 m_pTex_Inventory_on;
	D3DXIMAGE_INFO		 m_image_Inventory_on_info;
	RECT				 m_rc_Inventory_on;

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
	bool alreadyWorkedRbutton;// 아이템이 이미 착용되었는지를 체크. 
							  // 버그를 막아줘서 넣었는데 어떻게 막았는지 사실 잘 기억 안남.
							  // 아마 우측 
	D3DXMATRIXA16 matWorld[10];
	D3DXMATRIXA16 matWorld_InvenItems[INVENCORSS*INVENVERTI];


	float Adjust_Display_Mode_X; //해상도 변경에 따라 비율 조절해주는 아이
	float Adjust_Display_Mode_Y; //해상도 변경에 따라 비율 조절해주는 아이
	float Basic_ScaleX;
	float Basic_ScaleY;

	float ShopItem_Display_Mode_X;//해상도 변경에 따라 비율 조절해주는 아이
	float ShopItem_Display_Mode_Y;//해상도 변경에 따라 비율 조절해주는 아이


	int EmptyRcX;
	int EmptyRcY;
public:
	Inventory();
	~Inventory();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;

	std::vector<items> Equip_RightHand; // 오른손 장착 백터
	std::vector<items> Equip_LeftHand; // 왼손 장착 백터
	std::vector<items> Equip_Amor;  // 갑빠
	std::vector<items> Equip_Belt; // 벨트
	std::vector<items> Equip_Glove; // 장갑
	std::vector<items> EQuip_Boots; //신발 



	items Weapons[10]; // 일단 무기 10개까지 만들려고 하긴 했으나...
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

	void MovingItem(items* a, items* b); // 인벤토리 내에서 아이템 옮기기 하지만 실패 ...
	
};


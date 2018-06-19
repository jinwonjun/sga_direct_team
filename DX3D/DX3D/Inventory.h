#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#define INVENCORSS 6
#define INVENVERTI 5
#define INVENITEMSTART_X 1000
#define INVENITEMSTART_Y 420

struct items {

	int index;
	char* name;
	int Atk;
	int MaxHp;	

	float PositionX;
	float PositionY;
	float ScaleX;
	float ScaleY;
	bool  isClicked;
	bool  isInvenIn;

	int Copy_num;
	int Equip_Type;

	RECT Item_rc;
	RECT Click_rc;


	D3DXIMAGE_INFO		 m_image_Item_Info;
	LPDIRECT3DTEXTURE9	 m_pTex_Item;
};

enum Weapon_Type
{
	Weapon_Type_LeftHand = 1,
	Weapon_Type_RightHand,
	Weapon_Type_Amor,
	Weapon_Type_Belt,
	Weapon_Type_Glove,
	Weapon_Type_Boots

};
class IUIObject;
class Inventory : public IDisplayObject, public IUIButtonDelegate
{

private:
	std::wstring temp; 
	
	
	POINT mousePoint;
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pRootUI;
	


	D3DXMATRIXA16 matWorld_2;

	LPDIRECT3DTEXTURE9	 m_pTex_Inventory;
	D3DXIMAGE_INFO		 m_image_Inventory_info;
	RECT				 m_rc_Inventory;

	std::vector<items> Shop_Item;

	LPDIRECT3DTEXTURE9	 m_pTex_ItemSet;
	D3DXIMAGE_INFO		 m_image_ItemSet_info;
	RECT				 m_rc_ItemSet;


	std::vector<items> inventory;



	RECT clientRect;
	int preChosenX;
	int preChosenY;
	bool pressOn;

	int CrossX;
	int VertiY;

	bool EscapeFor;
	bool alreadyWorkedRbutton;// ������ ��ư�� �ѹ��� ���ǰ� �ϱ� ���ؼ� ���

public:
	Inventory();
	~Inventory();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate��(��) ���� ��ӵ�
	virtual void OnClick(UIButton * pSender) override;

	std::vector<items> Equip_RightHand;
	std::vector<items> Equip_LeftHand;
	std::vector<items> Equip_Amor;
	std::vector<items> Equip_Belt;
	std::vector<items> Equip_Glove;
	std::vector<items> EQuip_Boots;



	items Weapons[10];
	items Void_Item[INVENCORSS][INVENVERTI];

	RECT InventorRect[10];
	items InvenArray[INVENCORSS][INVENVERTI];

	bool openInven;
	bool SwapDoor; 
	bool Endfor;
	items addIndex(items a); // �κ��丮�� ������ �ֱ�
	void MovingItem(items* a, items* b); // �κ��丮 ������ ������ �ű��
	void ExMovingItem(items* a); // �� ���� �ִ� ������
	items moveItems(items a);


};


#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#define INVENCORSS 6
#define INVENVERTI 4
#define INVENITEMSTART_X 1000
#define INVENITEMSTART_Y 420



struct items {

	int index;  //������ ��ȣ
	char* name; // �̸�
	int Atk;    // ���ݷ�
	int MaxHp;	// HP
	int Hp;     // ���� HP
	int Def;    // ����

	float PositionX; // rc�� �� ��ġ
	float PositionY; // rc�� �� ��ġ
	float ScaleX;    // X�� ��ĳ��
	float ScaleY;    // Y�� ��ĳ��
	bool  isClicked; // Ŭ�� �Ǿ��°�?
	bool  isInvenIn; // �κ��丮 �ȿ� �ִ°�?

	int Copy_num;    // �� ��° ����� �������ΰ�?
	int Equip_Type;  // ������ ���� Ÿ��. �̳����� ���� �ο�


	bool isInvenOn;
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


	POINT mousePoint; //���콺 ����Ʈ ��ġ�� �������� ���ؼ�
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pRootUI;


	D3DXMATRIXA16 matR, matT, matS;


	D3DXMATRIXA16 matWorld_2;//����ü .... ���� �����ٰ� �Ѵ�.

							 //�κ��丮 �ؽ��Ŀ� �̹��� ������ ��Ʈ
	LPDIRECT3DTEXTURE9	 m_pTex_Inventory;
	D3DXIMAGE_INFO		 m_image_Inventory_info;
	RECT				 m_rc_Inventory;

	LPDIRECT3DTEXTURE9	 m_pTex_Inventory_Chara;
	D3DXIMAGE_INFO		 m_image_Inventory_Chara_info;
	RECT				 m_rc_Inventory_Chara;


	std::vector<items> Shop_Item;//���丮�� �ѱ� ���

	LPDIRECT3DTEXTURE9	 m_pTex_ItemSet;
	D3DXIMAGE_INFO		 m_image_ItemSet_info;
	RECT				 m_rc_ItemSet;


	LPDIRECT3DTEXTURE9	 m_pTex_MouseCursor_Normal;
	D3DXIMAGE_INFO		 m_image_MouseCursor_Normal_info;
	RECT				 m_rc_MouseCursor_Normal;

	LPDIRECT3DTEXTURE9	 m_pTex_MouseCursor_ClickedOn;
	D3DXIMAGE_INFO		 m_image_MouseCursor_ClickedOn_info;
	RECT				 m_rc_MouseCursor_ClickedOn;


	//�ش� �κ��丮�� �ö� �� �������� �̰���
	LPDIRECT3DTEXTURE9	 m_pTex_Inventory_on;
	D3DXIMAGE_INFO		 m_image_Inventory_on_info;
	RECT				 m_rc_Inventory_on;

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
	bool alreadyWorkedRbutton;// �������� �̹� ����Ǿ������� üũ. 
							  // ���׸� �����༭ �־��µ� ��� ���Ҵ��� ��� �� ��� �ȳ�.
							  // �Ƹ� ���� 
	D3DXMATRIXA16 matWorld[10];
	D3DXMATRIXA16 matWorld_InvenItems[INVENCORSS*INVENVERTI];


	float Adjust_Display_Mode_X; //�ػ� ���濡 ���� ���� �������ִ� ����
	float Adjust_Display_Mode_Y; //�ػ� ���濡 ���� ���� �������ִ� ����
	float Basic_ScaleX;
	float Basic_ScaleY;

	float ShopItem_Display_Mode_X;//�ػ� ���濡 ���� ���� �������ִ� ����
	float ShopItem_Display_Mode_Y;//�ػ� ���濡 ���� ���� �������ִ� ����


	int EmptyRcX;
	int EmptyRcY;
public:
	Inventory();
	~Inventory();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate��(��) ���� ��ӵ�
	virtual void OnClick(UIButton * pSender) override;

	std::vector<items> Equip_RightHand; // ������ ���� ����
	std::vector<items> Equip_LeftHand; // �޼� ���� ����
	std::vector<items> Equip_Amor;  // ����
	std::vector<items> Equip_Belt; // ��Ʈ
	std::vector<items> Equip_Glove; // �尩
	std::vector<items> EQuip_Boots; //�Ź� 



	items Weapons[10]; // �ϴ� ���� 10������ ������� �ϱ� ������...
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

	void MovingItem(items* a, items* b); // �κ��丮 ������ ������ �ű�� ������ ���� ...
	
};


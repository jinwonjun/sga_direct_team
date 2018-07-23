#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#include "UIText.h"
#include "ItemManager.h"
#define CopiedItemNum 15

#define g_pShop Shop::Get()


class IUIObject;

class Shop 
{
private:

	static Shop * instance;

	RECT clientRect;
	POINT mousePoint;
	D3DXMATRIXA16 matT, matS, matWorld;

public:

	static Shop * Get();
	static void Delete();
	items Shop_Items[CopiedItemNum];
	Draw_UI_ Shop_BackGround;
	Button_UI_ EquipType[6];

	bool ShopOpen;
	bool buyItems; // 바로 착용되는 걸 막기 위한 고육지책
	//Weapon_Type_MainWeapons = 1,
	//	Weapon_Type_Armor =2
	//	Weapon_Type_Glove =3
	//	Weapon_Type_SubWeapons =4
	//	Weapon_Type_Belt =5
	//	Weapon_Type_Boots =6
	
	void Init();
	void Update();
	void Render();

};


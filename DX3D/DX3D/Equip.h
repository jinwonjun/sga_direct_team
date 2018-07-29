#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#include "UIText.h"
#include "ItemManager.h"

#define g_pEquip Equip::Get()


class IUIObject;

class Equip
{
private:
	static Equip * instance;
	POINT mousePoint;

	LPD3DXSPRITE m_pSprite;

	D3DXMATRIXA16	m_matWorld_Euip_Name_text[6];
	LPD3DXSPRITE m_pSprite_Equip[6];
	IUIObject * m_pRootUI_Euip_Text[6];
	RECT    Equip_Name_Rect[6];
	CString Equip_Name_Text[6];
	UIButton * Equip_Name[6];
	IUIButtonDelegate * m_pDelegate_Equip_Name[6];

	RECT clientRect;

	D3DXMATRIXA16 matR, matT, matS;
	D3DXMATRIXA16 matWorld[60];
	D3DXMATRIXA16 matWorld_InvenItems[matWorld_InvenArray + INVENCORSS * INVENVERTI];

	Inven_UI Equiped_Side;
	Inven_UI Equiped_Item[6];
	Inven_UI Equiped_Item_BlackBack[6];


	int Column, Cross;


public:
	static Equip *Get();
	static void Delete();

	vector<items> EuipeedIted;
	void Weapon_Equip_Text();
	bool EquipScreenOn;
	bool FireAvaliable;

	void Init();
	void Update();
	void Render();


};


#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"

struct Character 
{
	
	char* name;
	int Lv;
	int Atk;
	int Def;
	int MaxHp;
	int CurrHp;
	int MoveSpeed;
	int AtkSpeed;
	
	int OriginLv;
	int OriginAtk;
	int OriginDef;
	int OriginMaxHp;
	int OriginCurrHp;
	int OriginMoveSpeed;
	int OriginAtkSpeed;
	
};

class Character_Stat :
	public IDisplayObject
{
private:
	bool isEquiped;

	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pRootUI;

public:
	Character_Stat();
	~Character_Stat();

	Character IronMan;
	items Equip_LeftHand;
	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};


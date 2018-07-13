#pragma once

#include "UIText.h"
#include "UIButton.h"

#define g_pStatus  CharacterStatus::Get()

#define NumOfmatWorld 10

struct Character
{
	int index;
	char * name;
	int Atk;    // 공격력
	int MaxHp;	// HP
	int Hp;     // 지금 HP
	int Def;    // 방어력

	int EndAtk;    // 공격력
	int EndMaxHp;	// HP
	//int EndHp;     // 지금 HP
	int EndDef;    // 방어력

	int AtkType; // 공격 형태, 단발 =0 ? 점사 = 1? 연사 =2?
};

class CharacterStatus
{

private:
	static CharacterStatus * instance;

	POINT mousePoint; //마우스 포인트 위치를 가져오기 위해서
	LPD3DXSPRITE m_pSprite;

	D3DXMATRIXA16 matR, matT, matS;

	D3DXMATRIXA16 matWorld[NumOfmatWorld];

	int AddAtk; // 장비로 인한 추가공격력
	int AddMaxHp;
	int AddHp;
	int AddDef;

public:
	//CharacterStatus();
	//virtual ~CharacterStatus();

	
	Character MyChara;
	bool isChangeEquip;


	static CharacterStatus* Get();
	static void Delete();


	void Init();
	void Update();
	void Render();

	void Initialize_Adds();
	void Change_Equip();


};


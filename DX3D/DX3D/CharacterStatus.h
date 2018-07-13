#pragma once

#include "UIText.h"
#include "UIButton.h"

#define g_pStatus  CharacterStatus::Get()

#define NumOfmatWorld 10

struct Character
{
	int index;
	char * name;
	int Atk;    // ���ݷ�
	int MaxHp;	// HP
	int Hp;     // ���� HP
	int Def;    // ����

	int EndAtk;    // ���ݷ�
	int EndMaxHp;	// HP
	//int EndHp;     // ���� HP
	int EndDef;    // ����

	int AtkType; // ���� ����, �ܹ� =0 ? ���� = 1? ���� =2?
};

class CharacterStatus
{

private:
	static CharacterStatus * instance;

	POINT mousePoint; //���콺 ����Ʈ ��ġ�� �������� ���ؼ�
	LPD3DXSPRITE m_pSprite;

	D3DXMATRIXA16 matR, matT, matS;

	D3DXMATRIXA16 matWorld[NumOfmatWorld];

	int AddAtk; // ���� ���� �߰����ݷ�
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


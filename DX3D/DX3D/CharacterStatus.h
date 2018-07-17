#pragma once

#include "UIText.h"
#include "UIButton.h"

#define g_pStatus  CharacterStatus::Get()

#define NumOfmatWorld 10

struct Character
{


};

class CharacterStatus
{

private:
	static CharacterStatus * instance;

	POINT mousePoint; //���콺 ����Ʈ ��ġ�� �������� ���ؼ�
	LPD3DXSPRITE m_pSprite;

	D3DXMATRIXA16 matR, matT, matS;

	D3DXMATRIXA16 matWorld[NumOfmatWorld];



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



};


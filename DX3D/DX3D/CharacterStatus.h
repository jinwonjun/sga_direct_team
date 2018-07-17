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

	POINT mousePoint; //마우스 포인트 위치를 가져오기 위해서
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


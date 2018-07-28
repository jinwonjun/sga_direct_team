#pragma once

#include "UIText.h"
#include "UIButton.h"

#define g_pUIManager  UIManager::Get()

#define NumOfmatWorld 10



class UIManager
{
private:
	static UIManager * instance;


public:
	RECT clientRect;
	POINT mousePoint;

	Inven_UI MouseCursor_Normal;
	Inven_UI MousCursor_ClickedOn;
	D3DXMATRIXA16 matR, matT, matS;
	D3DXMATRIXA16 matWorld;

	LPD3DXSPRITE pSprite;
	

	int AnswerDmg;
	int IronMan_Atk;
	int IronMan_Def;
	void Get_IronManAtk(int atk) { IronMan_Atk = atk; }
	void Get_IronManDef(int def) { IronMan_Def = def; }


	static UIManager* Get();
	static void Delete();

	
	

	void Init();
	void Update();
	void Render();

};


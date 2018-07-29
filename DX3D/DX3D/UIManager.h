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

<<<<<<< HEAD
=======
	Inven_UI MouseCursor_Normal;
	Inven_UI MousCursor_ClickedOn;
	D3DXMATRIXA16 matR, matT, matS;
	D3DXMATRIXA16 matWorld;

	LPD3DXSPRITE pSprite;
	bool cheatKeyAtk;

	int AnswerDmg;
	int IronMan_Atk;
	//int beforeCheat;
	int IronMan_Def;
	
	void Get_IronManAtk(int atk) {
		IronMan_Atk = atk; 
	
	}
	void Get_IronManDef(int def) { IronMan_Def = def; }
>>>>>>> ce9f2df1f8d028fac14bf30c9152159971bcf68e


	static UIManager* Get();
	static void Delete();

<<<<<<< HEAD
	int AnswerDmg;
	int IronMan_Atk;
	int IronMan_Def;
	void Get_IronManAtk(int atk) { IronMan_Atk = atk; }
	void Get_IronManDef(int def) { IronMan_Def = def; }
=======
	
	
>>>>>>> ce9f2df1f8d028fac14bf30c9152159971bcf68e

	void Init();
	void Update();
	void Render();

};


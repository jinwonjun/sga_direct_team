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

	int IronMan_Atk;
	int IronMan_Def;

	static UIManager* Get();
	static void Delete();

	int AnswerDmg;
	
	void Get_IronManAtk(int atk) { IronMan_Atk = atk; }
	void Get_IronManDef(int def) { IronMan_Def = def; }

	void Init();
	void Update();
	void Render();

};


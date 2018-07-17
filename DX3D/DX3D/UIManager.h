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


	static UIManager* Get();
	static void Delete();

	int AnswerDmg;


	void Init();
	void Update();
	void Render();

};


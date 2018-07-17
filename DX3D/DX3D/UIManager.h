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

	int AnswerDmg; //데미지 공식에 의해 산출된 값을 저장


	void Init();
	void Update();
	void Render();

};


#include "stdafx.h"
#include "UIManager.h"


UIManager* UIManager::instance = NULL;


UIManager * UIManager::Get()
{
	if (instance == NULL)
		instance = new UIManager();

	return instance;
}



void UIManager::Delete()
{
	SAFE_DELETE(instance);
}

void UIManager::Init()
{
}

void UIManager::Update()
{
}

void UIManager::Render()
{
}




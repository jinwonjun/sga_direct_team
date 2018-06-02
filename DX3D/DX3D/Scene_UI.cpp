#include "stdafx.h"
#include "Scene_UI.h"

#include "SampleUI.h"

Scene_UI::Scene_UI()
{
}


Scene_UI::~Scene_UI()
{
	SAFE_RELEASE(pObj);
}

void Scene_UI::Init()
{
	pObj = new SampleUI;
	pObj->Init();
	AddSimpleDisplayObj(pObj);
}

void Scene_UI::Update()
{
	OnUpdateIScene();
}

void Scene_UI::Render()
{
	OnRenderIScene();
}

void Scene_UI::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

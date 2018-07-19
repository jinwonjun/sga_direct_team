#include "stdafx.h"
#include "Scene_Intro.h"
#include "IntroUI.h"

Scene_Intro::Scene_Intro()
{
}


Scene_Intro::~Scene_Intro()
{
}

void Scene_Intro::Init()
{

	pObject = new IntroUI;
	pObject->Init();
	AddSimpleDisplayObj(pObject);

	//조명!
	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	//씬 비추는 조명 설정하기
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//왜곡 줄이기, 맵이 밝아지는 효과가 생기네?!
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

}

void Scene_Intro::Update()
{
	OnUpdateIScene();
}

void Scene_Intro::Render()
{
	OnRenderIScene();
}

void Scene_Intro::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

#include "stdafx.h"
#include "Scene_UI.h"

#include "SampleUI.h"

#include "ObjMap.h"
#include "Ironman.h"


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

	m_pObjMAp = new ObjMap;
	m_pObjMAp->Init();
	//��ü�� ���������� ��ü �߰� �Լ��� ȣ������
	AddSimpleDisplayObj(m_pObjMAp);


	m_pCharacter = new Ironman;
	m_pCharacter->Init();
	AddSimpleDisplayObj(m_pCharacter);

	//���� �߿���
	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	//�� ���ߴ� ���� �����ϱ�
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//�ְ� ���̱�, ���� ������� ȿ���� �����?!
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
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

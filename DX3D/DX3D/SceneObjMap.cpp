#include "stdafx.h"
#include "SceneObjMap.h"
#include "ObjMap.h"
#include "Cubeman.h"
#include "AseCharacter.h"

SceneObjMap::SceneObjMap()
{
	m_pObjMAp = NULL;
	m_pCubeman = NULL;
	m_pAseCharacter = NULL;
}


SceneObjMap::~SceneObjMap()
{
	OnDestructIScene();
	//SAFE_RELEASE(m_pObjMAp);
}

void SceneObjMap::Init()
{
	m_pObjMAp = new ObjMap;
	m_pObjMAp->Init();
	//객체를 생성했으면 객체 추가 함수를 호출하자
	AddSimpleDisplayObj(m_pObjMAp);

	//큐브맨 넣어보기
	/*m_pCubeman = new Cubeman;
	m_pCubeman->Init();*/
	//AddSimpleDisplayObj(m_pCubeman);

	m_pAseCharacter = new AseCharacter;
	m_pAseCharacter->Init();
	AddSimpleDisplayObj(m_pAseCharacter);
	

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, & dir);

	//씬 비추는 조명 설정하기
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir,  & WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//왜곡 줄이기, 맵이 밝아지는 효과가 생기네?!
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void SceneObjMap::Update()
{
	OnUpdateIScene();
}

void SceneObjMap::Render()
{
	OnRenderIScene();
	//SAFE_RENDER(m_pObjMAp);
}

void SceneObjMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

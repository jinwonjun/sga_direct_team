#include "stdafx.h"
#include "SceneGrid.h"
#include "TeachGrid.h"
#include "Cubeman.h"
#include "Walls.h"
#include "SampleUI.h"
#include "Cube.h"

//월요일 수업 내용
#include "Hexagon.h"
#include "ActionCube.h"
#include "Frustum.h"

#include"SkyBox.h"
#include "HeightMap.h"
#include "EnemyManager.h"
#include "Enemy.h"


SceneGrid::SceneGrid()
{
	m_pCubeman = NULL;

	m_pSky = new SkyBox(L"resources\\skybox\\vanilla_sky_frost_up.jpg", L"resources\\skybox\\vanilla_sky_frost_dn.jpg",
		L"resources\\skybox\\vanilla_sky_frost_lf.jpg", L"resources\\skybox\\vanilla_sky_frost_rt.jpg",
		L"resources\\skybox\\vanilla_sky_frost_ft.jpg", L"resources\\skybox\\vanilla_sky_frost_bk.jpg");
}


void SceneGrid::Release()
{
	SAFE_RELEASE(tex);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pCubeman);
	SAFE_RELEASE(m_pHexagon);
	SAFE_RELEASE(m_pWalls);
	SAFE_RELEASE(m_pActionCube);
	SAFE_RELEASE(pCube);
	SAFE_RELEASE(m_pFrustum);
	SAFE_RELEASE(pObj);

	SAFE_RELEASE(m_pHeightMap);
	m_pSky->~SkyBox();
	SAFE_RELEASE(m_pEm);


	BaseObject::Release();
}

void SceneGrid::Init()
{
	pCube = new Cube;
	pCube->Init();
	////일단 파츠 구현
	//pCube_head = new Cubeman_Head;
	//pCube_head->Init();

	//pGrid = new Grid;
	//pGrid->Init();

	pObj = new SampleUI;
	pObj->Init();
	AddSimpleDisplayObj(pObj);


	m_pGrid = new TeachGrid;
	m_pGrid->Init();

	m_pCubeman = new Cubeman();
	m_pCubeman->Init();

	m_pWalls = new Walls();
	m_pWalls->Init();


	m_pHexagon = new Hexagon();
	m_pHexagon->Init();

	m_pActionCube = new ActionCube();
	m_pActionCube->Init();


	m_pFrustum = new Frustum();
	m_pFrustum->Init();

	m_pEm = new EnemyManager();
	m_pEm->Init();

	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 1)));//7
	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(0, 0)));//6
	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(1, 1, 0), D3DXVECTOR2(1, 0)));//5

	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 1)));//7
	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(1, 1, 0), D3DXVECTOR2(1, 0)));//5
	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(1, 0, 0), D3DXVECTOR2(1, 1)));//4

	//D3DXCreateTextureFromFile(g_pDevice, _T("resources/images/ham1.png"), &tex);
	D3DXCreateTextureFromFile(g_pDevice, _T("ham1.png"), &tex);


	//헤이트맵 올리기
	D3DXMATRIXA16 matS ,matT, matRX,matRY,matWorld;
	//D3DXMatrixScaling(&matS, 0.2f, 0.03f, 0.2f);
	D3DXMatrixScaling(&matS, 1.0f, 0.1f, 1.0f);
	D3DXMatrixIdentity(&matT);

	//높이맵 호출 부분
	m_pHeightMap = new HeightMap; 
	AddSimpleDisplayObj(m_pHeightMap);
	m_pHeightMap->SetDimension(257);
	m_pHeightMap->Load("resources/heightmap/HeightMap.raw", &matS);
	//m_pHeightMap->Load("resources/heightmap/HeightMap.raw", &matS);
	//m_pHeightMap->Load("resources/heightmap/data/heightmap.r16", &matS);
	m_pHeightMap->Init();

	D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;
	m_pHeightMap->SetMtlTex(mtl, g_pTextureManager->GetTexture("resources/heightmap/terrain.jpg"));
	//m_pHeightMap->SetMtlTex(mtl, g_pTextureManager->GetTexture("resources/heightmap/data/colormap.bmp"));
	

	//상태맵 저장하기
	g_pMapManager->AddMap("heightMap", m_pHeightMap);
	g_pMapManager->SetCurrentMap("heightMap");
}

void SceneGrid::Update()
{
	SAFE_UPDATE(pCube);
	//SAFE_UPDATE(pCube_head);
	OnUpdateIScene();
	SAFE_UPDATE(m_pCubeman);
	//SAFE_UPDATE(m_pActionCube);

	SAFE_UPDATE(m_pFrustum);
	SAFE_UPDATE(m_pEm);

	BoundingCheck();


}

void SceneGrid::Render()
{
	//그릴 도형의 타입, 도형의 갯수, 정점 정보의 시작 주소, 정점의 크기
	//그라데이션 형식으로 그려짐.
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,&m_vecVertex[0],sizeof(VERTEX_PC));

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pDevice->SetFVF(VERTEX_PT::FVF);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTexture(0, tex);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, vecPTVertex.size() / 3, &vecPTVertex[0], sizeof(VERTEX_PT));
	g_pDevice->SetTexture(0, NULL);

	//스카이박스!!!
	m_pSky->Render();

	//큐브 그리기
	//pCube->Render();
	//그리드 그리기
	SAFE_RENDER(m_pGrid);
	//pGrid->Render();
	SAFE_RENDER(m_pCubeman);
	//조명에 따른 벽 그려보기
	//SAFE_RENDER(m_pWalls);

	//SAFE_RENDER(m_pHexagon);

	//SAFE_RENDER(m_pActionCube);

	//SAFE_RENDER(m_pFrustum);

	//IScene상속 받는 애들 전부 렌더하기
	SAFE_RENDER(m_pHeightMap);
	SAFE_RENDER(m_pEm);



	OnRenderIScene();
}

void SceneGrid::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pHeightMap);
}

void SceneGrid::BoundingCheck()
{

	Cubeman* PlayerObj = static_cast <Cubeman *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER));
	EnemyManager* EnemyObj = static_cast <EnemyManager *>(g_pObjMgr->FindObjectByTag(TAG_ENEMY));

	for (auto p : EnemyObj->GetVecEnemy())
	{
		BoundingBox* pEnemyBox = p->GetBoundingBox();
		if (PlayerObj->GetBoundingBox()->IsIntersected(*pEnemyBox))
		{
			p->SetDestPos(PlayerObj->GetPosition());
		}
		else
		{
			p->MoveStop();
		}
	}
}

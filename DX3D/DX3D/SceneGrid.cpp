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

//맵에 스킨매쉬 올려보기
#include "ironman.h"
#include "Gun.h"

//인벤토리 넣어보기
#include "InventoryManager.h"

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
	//SAFE_RELEASE(m_pGrid);
	//SAFE_RELEASE(m_pCubeman);
	SAFE_RELEASE(m_pHexagon);
	SAFE_RELEASE(m_pWalls);
	SAFE_RELEASE(m_pActionCube);
	SAFE_RELEASE(pCube);
	SAFE_RELEASE(m_pFrustum);
	SAFE_RELEASE(pObj);

	SAFE_RELEASE(m_pHeightMap);
	//m_pSky->~SkyBox();
	SAFE_RELEASE(m_pEm);
	
	//SAFE_RELEASE(m_Inventory);
	
	SAFE_RELEASE(m_pCharacter);

	BaseObject::Release();
}

void SceneGrid::Init()
{
	g_pInventory->Init();
	//AddSimpleDisplayObj(g_pInventory->Get());

	//D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	//D3DXVec3Normalize(&dir, &dir);
	//D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	//g_pDevice->SetLight(0, &light);
	//g_pDevice->LightEnable(0, true);
	//g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	//pCube = new Cube;
	//pCube->Init();

	////일단 파츠 구현
	//pCube_head = new Cubeman_Head;
	//pCube_head->Init();

	//pGrid = new Grid;
	//pGrid->Init();

	pObj = new SampleUI;
	pObj->Init();
	AddSimpleDisplayObj(pObj);


	//m_pGrid = new TeachGrid;
	//m_pGrid->Init();

	//m_pCubeman = new Cubeman();
	//m_pCubeman->Init();

	/*m_pWalls = new Walls();
	m_pWalls->Init();*/


	//m_pHexagon = new Hexagon();
	//m_pHexagon->Init();

	//m_pActionCube = new ActionCube();
	//m_pActionCube->Init();


	//m_pFrustum = new Frustum();
	//m_pFrustum->Init();

	m_pEm = new EnemyManager();
	m_pEm->Init();

	// 인벤토리


	//m_Inventory = new Inventory;
	//m_Inventory->Init();
	

	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 1)));//7
	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(0, 1, 0), D3DXVECTOR2(0, 0)));//6
	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(1, 1, 0), D3DXVECTOR2(1, 0)));//5

	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 1)));//7
	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(1, 1, 0), D3DXVECTOR2(1, 0)));//5
	vecPTVertex.push_back(VERTEX_PT(D3DXVECTOR3(1, 0, 0), D3DXVECTOR2(1, 1)));//4

	//D3DXCreateTextureFromFile(g_pDevice, _T("resources/images/ham1.png"), &tex);
	//D3DXCreateTextureFromFile(g_pDevice, _T("ham1.png"), &tex);

	//매쉬 캐릭터 올리기
	m_pCharacter = new Ironman;
	m_pCharacter->Init();
	AddSimpleDisplayObj(m_pCharacter);

	m_pGun = new Gun;
	m_pGun->Init();
	AddSimpleDisplayObj(m_pGun);


	//헤이트맵 올리기
	//D3DXMATRIXA16 matS, matT, matRX, matRY, matWorld;
	////D3DXMatrixScaling(&matS, 0.2f, 0.03f, 0.2f);
	//D3DXMatrixScaling(&matS, 1.0f, 0.1f, 1.0f);
	//D3DXMatrixIdentity(&matT);

	////높이맵 호출 부분
	//m_pHeightMap = new HeightMap;
	//AddSimpleDisplayObj(m_pHeightMap);
	//m_pHeightMap->SetDimension(257);
	//m_pHeightMap->Load("resources/heightmap/HeightMap.raw", &matS);
	////m_pHeightMap->Load("resources/heightmap/HeightMap.raw", &matS);
	////m_pHeightMap->Load("resources/heightmap/data/heightmap.r16", &matS);
	//m_pHeightMap->Init();

	//D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;
	//m_pHeightMap->SetMtlTex(mtl, g_pTextureManager->GetTexture("resources/heightmap/terrain.jpg"));
	////m_pHeightMap->SetMtlTex(mtl, g_pTextureManager->GetTexture("resources/heightmap/data/colormap.bmp"));
	////상태맵 저장하기
	//g_pMapManager->AddMap("heightMap", m_pHeightMap);
	//g_pMapManager->SetCurrentMap("heightMap");


	//obj맵 깔기
	ObjMap* pMap = new ObjMap();
	pMap->Init();
	AddSimpleDisplayObj((pMap));

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

void SceneGrid::Update()
{
	//SAFE_UPDATE(pCube);
	//SAFE_UPDATE(m_pCubeman);
	//SAFE_UPDATE(m_pActionCube);
	//SAFE_UPDATE(m_pFrustum);


	SAFE_UPDATE(m_pEm);

	BoundingCheck();

	//SAFE_UPDATE(pCube_head);
	OnUpdateIScene();
}

void SceneGrid::Render()
{
	//그릴 도형의 타입, 도형의 갯수, 정점 정보의 시작 주소, 정점의 크기
	//그라데이션 형식으로 그려짐.
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,&m_vecVertex[0],sizeof(VERTEX_PC));

	//기본 렌더 셋팅인데 이것때문에 이상하게 그려지는거 같음
	//D3DXMATRIXA16 mat;
	//D3DXMatrixIdentity(&mat);
	//g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	//g_pDevice->SetFVF(VERTEX_PT::FVF);
	//g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pDevice->SetTexture(0, tex);
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, vecPTVertex.size() / 3, &vecPTVertex[0], sizeof(VERTEX_PT));
	//g_pDevice->SetTexture(0, NULL);

	//스카이박스!!!
	//m_pSky->Render();

	//큐브 그리기
	//pCube->Render();
	//그리드 그리기
	//SAFE_RENDER(m_pGrid);

	//SAFE_RENDER(m_pCubeman);
	//조명에 따른 벽 그려보기
	//SAFE_RENDER(m_pWalls);

	//SAFE_RENDER(m_pHexagon);

	//SAFE_RENDER(m_pActionCube);

	//SAFE_RENDER(m_pFrustum);

	//IScene상속 받는 애들 전부 렌더하기
	//SAFE_RENDER(m_pHeightMap);
	SAFE_RENDER(m_pEm);


	OnRenderIScene();
}

void SceneGrid::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//SAFE_WNDPROC(m_pHeightMap);
}

void SceneGrid::BoundingCheck()
{

	Ironman* PlayerObj = static_cast <Ironman *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER));
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
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

#include "SkyBox.h"
#include "HeightMap.h"
#include "BoundingBox.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "PortalEffect.h"

//맵에 스킨매쉬 올려보기
#include "ironman.h"
#include "Gun.h"

//인벤토리, UI
#include "InventoryManager.h"
#include "UIOperator.h"
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

	SAFE_RELEASE(m_pPortalEffect);

	BaseObject::Release();
}

void SceneGrid::Init()
{
	//g_pInventory->Init();
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
	pMap = new ObjMap();
	pMap->Init();
	AddSimpleDisplayObj((pMap));

	m_pPortalEffect = new PortalEffect();
	m_pPortalEffect->Init();
	AddSimpleDisplayObj(m_pPortalEffect);


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

	g_pSoundManager->Play("gameScene", 1.0f);
}

void SceneGrid::Update()
{
	//SAFE_UPDATE(pCube);
	//SAFE_UPDATE(m_pCubeman);
	//SAFE_UPDATE(m_pActionCube);
	//SAFE_UPDATE(m_pFrustum);

	BoundingCheck();

	SAFE_UPDATE(m_pEm);

	//SAFE_UPDATE(pCube_head);
	OnUpdateIScene();
}

void SceneGrid::Render()
{
	//스카이박스!!!
	m_pSky->Render();

	SAFE_RENDER(m_pEm);

	OnRenderIScene();
}

void SceneGrid::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void SceneGrid::BoundingCheck()
{
	for (auto p : m_pEm->GetVecEnemy())
	{
		//BoundingBox* pEnemyBox = p->GetBoundingBox();
		if (m_pCharacter->GetBoundingBox()->IsIntersected(*(p->GetBoundingBox())))
		{
			p->SetDestPos(m_pCharacter->GetPosition());
			p->SetIsMove(true);
		}
		else
		{
			p->SetIsMove(false);
		}
	}

	if (m_pCharacter->GetBoundingBox()->IsIntersected(*(m_pPortalEffect->GetBoundingBox())))
	{
		//보스맵으로 변경
		static_cast <ObjMap *>(g_pObjMgr->FindObjectByTag(TAG_OBJMAP))->Init_cs_assault();
		static_cast <ObjMap *>(g_pObjMgr->FindObjectByTag(TAG_OBJMAP))->SetMapChangeSignal(true);
		m_pCharacter->SetPosition(&D3DXVECTOR3(0, 0, 0));
	}

}

//g_pMapManager->SetCurrentMap("Assult");
//g_pMapManager->GetMapList();
//map<string, IMap*>::iterator itMap;
//map<string, IMap*> temp = g_pMapManager->GetMapList();
//for (itMap = temp.begin(); itMap != temp.end(); itMap++)
//{
//	if (temp.count("Assult") == 1)
//	{
//		g_pCurrentMap->SetMesh(temp["Assult"]->GetMesh());
//	}
//}
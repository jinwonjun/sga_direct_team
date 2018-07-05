#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{

	for (auto p : m_vecEnemy)
	{
		SAFE_RELEASE(p);
	}

}

void EnemyManager::Init(void)
{
	AddEnemy(D3DXVECTOR3(20, 0, 30), "resources/zealot/", "zealot.X",  0);
	AddEnemy(D3DXVECTOR3(45, 0, 20), "resources/zealot/", "zealot.X", 1);
	AddEnemy(D3DXVECTOR3(100, 0, 70), "resources/zealot/", "zealot.X",1);
	AddEnemy(D3DXVECTOR3(145, 0, 90), "resources/zealot/", "zealot.X", 0);
	//AddEnemy(D3DXVECTOR3(145, 0, 90), "resources/zealot/", "zealot.X");

	g_pObjMgr->AddToTagList(TAG_ENEMY, this);
}

void EnemyManager::Update(void)
{
	for each(Enemy* e in m_vecEnemy)
	{
		if (e->m_HP <= 0)
		{
			if (e->m_ItemDrop == false)
			{
				
				g_pItem->getMonsterXY(e->ScreenX, e->ScreenY);
				g_pItem->ItemGet(e->GetEnemyNum());

				e->m_ItemDrop = true;
			}
			continue;
		}

		
		e->Update();
	}

}

void EnemyManager::Render(void)
{
	for each(Enemy* e in m_vecEnemy)
	{
		if (e->m_HP <= 0) continue;
		e->Render();
	}
}

void EnemyManager::AddEnemy(D3DXVECTOR3 & pos, CString path, CString fileName, int enemyNum)
{
	Enemy* pEnemy = new Enemy(pos, path, fileName, enemyNum); pEnemy->Init();
	m_vecEnemy.push_back(pEnemy);
}
/*
void EnemyManager::WorldToVP()
{
	//월드좌표 -> 뷰 좌표 -> 프로젝션 -> 뷰포트 
	//g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	//g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj); 
	//ScreenX = projVertex.x * (ViewportWidth / 2) + ViewportLeft + (ViewportWidth / 2)
	//ScreenY = -projVertex.y * (ViewportHeight / 2) + ViewportTop + (ViewportHeight / 2)

	D3DXMATRIXA16 matProj, matWorld, matView, matWVP;
	D3DVIEWPORT9 vp;
	D3DXVECTOR3 v(0, 0, 0);
	float ScreenX, ScreenY;

	matWorld = m_vecEnemy[0]->GetWorldMatrix();//0번 인덱스 놈의 월드 행렬 가져오기

	g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	matWVP = matWorld * matView * matProj;

	D3DXVec3TransformCoord(&v, &v, &matWVP);

	g_pDevice->GetViewport(&vp);//뷰포트 정보값 가져오기

								//스크린좌표 가져오기
	ScreenX = (v.x * 0.5f + 0.5f) * vp.Width;
	ScreenY = ((-1)*v.y * 0.5f + 0.5f) * vp.Height;

	//스크린좌표 구했으니까 피통 UI를 머리 위로 올려!
	//Debug->EndLine();
	//Debug->EndLine();
	//Debug->AddText("스크린상좌표 X : ");
	//Debug->AddText(g_pCamera->GetMCenter().x);
	//Debug->AddText("  Y : ");
	//Debug->AddText(g_pCamera->GetMCenter().y);
	//Debug->EndLine();
	//Debug->EndLine();

	//Debug->AddText("0번 몹 스크린상좌표 X : ");
	//Debug->AddText(ScreenX);
	//Debug->AddText("  Y : ");
	//Debug->AddText(ScreenY);
	//Debug->EndLine();
	//Debug->EndLine();
}*/

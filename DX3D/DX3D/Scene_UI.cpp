#include "stdafx.h"
#include "Scene_UI.h"

#include "SampleUI.h"

#include "ObjMap.h"
#include "Ironman.h"

#include "EnemyManager.h"
#include "Enemy.h"

#include "Inventory.h"

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

	m_pEm = new EnemyManager();
	m_pEm->Init();
	AddSimpleDisplayObj(m_pEm);

	m_pInventory = new Inventory();
	m_pInventory->Init();
	AddSimpleDisplayObj(m_pInventory);

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
	BoundingCheck();
}

void Scene_UI::Render()
{
	OnRenderIScene();
}

void Scene_UI::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

void Scene_UI::BoundingCheck()
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

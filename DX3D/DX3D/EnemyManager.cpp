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
	AddEnemy(D3DXVECTOR3(20, 0, 30));
	AddEnemy(D3DXVECTOR3(45, 0, 20));
	AddEnemy(D3DXVECTOR3(100, 0, 70));
	AddEnemy(D3DXVECTOR3(145, 0, 90));

	g_pObjMgr->AddToTagList(TAG_ENEMY, this);
}

void EnemyManager::Update(void)
{
	for each(Enemy* e in m_vecEnemy)
	{
		if (e->m_HP <= 0) continue;
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

	Debug->AddText((int)m_vecEnemy[0]->m_HP);
}

void EnemyManager::AddEnemy(D3DXVECTOR3 & pos)
{
	Enemy* pEnemy = new Enemy(pos); pEnemy->Init();
	m_vecEnemy.push_back(pEnemy);
}
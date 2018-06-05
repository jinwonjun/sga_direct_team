#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
	for (auto p : m_listEnemy)
	{
		SAFE_RELEASE(p);
	}
}

void EnemyManager::Init(void)
{
	AddEnemy(D3DXVECTOR3(20, 0, 30));
	AddEnemy(D3DXVECTOR3(45, 0, 20));
	AddEnemy(D3DXVECTOR3(-20, 0, -30));
	AddEnemy(D3DXVECTOR3(-45, 0, -20));

	g_pObjMgr->AddToTagList(TAG_ENEMY, this);
}

void EnemyManager::Update(void)
{
	for each(Enemy* e in m_listEnemy)
	{
		e->Update();
	}
}

void EnemyManager::Render(void)
{
	for each(Enemy* e in m_listEnemy)
	{
		e->Render();
	}
}

void EnemyManager::AddEnemy(D3DXVECTOR3 & pos)
{
	Enemy* pEnemy = new Enemy(pos); pEnemy->Init();
	m_listEnemy.push_back(pEnemy);
}


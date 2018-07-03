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
	AddEnemy(D3DXVECTOR3(20, 0, 30), "resources/zealot/", "zealot.X", 0);
	AddEnemy(D3DXVECTOR3(45, 0, 20), "resources/zealot/", "zealot.X", 1);
	AddEnemy(D3DXVECTOR3(100, 0, 70), "resources/zealot/", "zealot.X", 0);
	AddEnemy(D3DXVECTOR3(145, 0, 90), "resources/zealot/", "zealot.X", 1);
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
<<<<<<< HEAD
				g_pInventory->addIndex(g_pItem->Weapons[0]);
				//g_pItem->ItemGet(1);
				//g_pInventory->addIndex(g_pItem->Weapons[0]);
=======

				g_pInventory->addIndex(g_pInventory->Shop_Item[e->GetEnemyNum()]);
>>>>>>> 50835c929f457d7ea454b07f3e75aedcaf5e5f47
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
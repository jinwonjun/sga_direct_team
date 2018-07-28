#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "SubMonster.h"
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
	AddEnemy(D3DXVECTOR3(100, 0, 70), "resources/zealot/", "zealot.X",2);
	AddEnemy(D3DXVECTOR3(145, 0, 90), "resources/zealot/", "zealot.X", 3);
	AddEnemy(D3DXVECTOR3(145, 0, 30), "resources/Boss_test/", "Mutant.X", 4);

	g_pObjMgr->AddToTagList(TAG_ENEMY, this);
}

void EnemyManager::Update(void)
{
	for each(Enemy* e in m_vecEnemy)
	{
		if (e->m_isDead)
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
	CollisionCheck();

	for (int i = 0; i < m_vecEnemy.size(); i++)
	{
		if (m_vecEnemy[i]->m_Hp <= 0)
		{
			//보스
			if (m_vecEnemy[i]->GetEnemyNum() == 4)
			{
				if (m_vecEnemy[i]->m_isDead)
				{
					g_pSoundManager->Play("zealot_death", 1.0f);
					Shaders::Get()->RemoveList(m_vecEnemy[i], m_vecEnemy[i]->m_renderMode);
					m_vecEnemy.erase(m_vecEnemy.begin() + i);
				}
			}
			else//쫄몹
			{
				g_pSoundManager->Play("zealot_death", 1.0f);
				Shaders::Get()->RemoveList(m_vecEnemy[i], m_vecEnemy[i]->m_renderMode);
				m_vecEnemy.erase(m_vecEnemy.begin() + i);
			}
		}
	}
}

void EnemyManager::Render(void)
{
	for each(Enemy* e in m_vecEnemy)
	{
		e->Render();
	}
}

void EnemyManager::AddEnemy(D3DXVECTOR3 & pos, CString path, CString fileName, int enemyNum)
{
	//Enemy* pEnemy = new Enemy(pos, path, fileName, enemyNum); pEnemy->Init();
	if (enemyNum < 4)
	{
		Enemy* pEnemy = new SubMonster(pos, path, fileName, enemyNum); pEnemy->Init();
		m_vecEnemy.push_back(pEnemy);
	}
	else
	{
		Enemy* pEnemy = new Boss(pos, path, fileName, enemyNum); pEnemy->Init();
		m_vecEnemy.push_back(pEnemy);
	}
}

void EnemyManager::CollisionCheck()
{
	for (int i = 0; i < m_vecEnemy.size(); i++)
	{
		//큰 값으로 초기화 : 충돌 했을 시 밀어낼 벡터
		D3DXVECTOR3 tempAvoid(100, 100, 100);

		for (int j = 0; j < m_vecEnemy.size(); j++)
		{
			//본인 제외 모든 몬스터끼리 체크
			if (i == j) continue;

			//충돌하면 밀어낼 벡터 방향 대입
			IntersectHead(m_vecEnemy[i]->m_frontHead, m_vecEnemy[i]->m_backHead
				, m_vecEnemy[j]->m_pBounidngSphere->center, m_vecEnemy[j]->m_CollRadius, tempAvoid);

			//충돌 했으면 밀어낼 벡터 삽입 : 초기화값이 아니라면 충돌!!
			if (tempAvoid != D3DXVECTOR3(100, 100, 100))
				m_vecEnemy[i]->m_avoid = tempAvoid;
			else
				m_vecEnemy[i]->m_avoid = D3DXVECTOR3(0, 0, 0);
		}
	}
}

void EnemyManager::IntersectHead(D3DXVECTOR3 fHead, D3DXVECTOR3 bHead, D3DXVECTOR3 const center, float radius, D3DXVECTOR3 & avoid)
{
	D3DXVECTOR3 fTemp = fHead - center; //피격 이너미 중점에서 먼 헤드 가르키는 벡터 
	D3DXVECTOR3 bTemp = bHead - center;	//피격 이너미 중점에서 근접 헤드 가르키는 벡터

	//인접 헤드 포인트가 피격 범위 안에 있고, 이전 밀어낼 벡터보다 가까운 곳에서 일어난거라면
	if (D3DXVec3Length(&bTemp) <= radius && D3DXVec3Length(&bTemp) < D3DXVec3Length(&avoid))
		D3DXVec3Normalize(&avoid, &bTemp); return;
	//먼 헤드 포인트가 ...
	if (D3DXVec3Length(&fTemp) <= radius && D3DXVec3Length(&fTemp) < D3DXVec3Length(&avoid))
		D3DXVec3Normalize(&avoid, &fTemp); return;

}
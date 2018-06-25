#include "stdafx.h"
#include "BloodManager.h"
#include "BloodParticle.h"
#include "SkinnedMesh.h"
#include "Ironman.h"

BloodManager::BloodManager()
{

}

BloodManager::~BloodManager()
{
	for (auto p : m_vecBP)
	{
		SAFE_RELEASE(p);
	}
}



void BloodManager::Init()
{
	g_pObjMgr->AddToTagList(TAG_PARTICLE, this);

	m_vecBP.resize(BLOOD_PARTICLE_MAX);

	for (size_t i = 0; i < BLOOD_PARTICLE_MAX; i++)
	{
		//파티클 묶음 벡터에 저장
		BloodParticle* bp = new BloodParticle(); bp->Init();
		m_vecBP[i] = bp;
	}
}

void BloodManager::Update()
{
	for (auto p : m_vecBP)
	{
		//파티클 묶음 업데이트, fire가 트루인애만 연산
		p->Update();
	}
}

void BloodManager::Render()
{
	for (auto p : m_vecBP)
	{
		//파티클 묶음 랜더, fire가 트루인애만 랜더
		p->Render();
	}
}

void BloodManager::Fire()
{
	for (auto p : m_vecBP)
	{
		//활성화중이 아닌 파티클을 만나면
		if (p->GetFire() == false)
		{
			D3DXVECTOR3 tempPos =  static_cast<Ironman*>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->BloodCalPos;
			tempPos = D3DXVECTOR3(tempPos.x, tempPos.y , tempPos.z);
			p->SetFire(true);
			p->SetPos(tempPos);
			break;
		}
	}
}

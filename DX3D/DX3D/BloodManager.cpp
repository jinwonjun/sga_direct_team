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
		//��ƼŬ ���� ���Ϳ� ����
		BloodParticle* bp = new BloodParticle(); bp->Init();
		m_vecBP[i] = bp;
	}
}

void BloodManager::Update()
{
	for (auto p : m_vecBP)
	{
		//��ƼŬ ���� ������Ʈ, fire�� Ʈ���ξָ� ����
		p->Update();
	}
}

void BloodManager::Render()
{
	for (auto p : m_vecBP)
	{
		//��ƼŬ ���� ����, fire�� Ʈ���ξָ� ����
		p->Render();
	}
}

void BloodManager::Fire()
{
	for (auto p : m_vecBP)
	{
		//Ȱ��ȭ���� �ƴ� ��ƼŬ�� ������
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

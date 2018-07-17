#include "stdafx.h"
#include "BloodEffect.h"
#include "BloodParticle.h"


BloodEffect::BloodEffect()
{
}


BloodEffect::~BloodEffect()
{
	for (auto p : m_vecBP)
	{
		SAFE_RELEASE(p);
	}
}

void BloodEffect::Fire(D3DXVECTOR3 _pos, D3DXVECTOR3 _dir)
{
	for (auto p : m_vecBP)
	{
		//Ȱ��ȭ���� �ƴ� ��ƼŬ�� ������
		if (p->GetFire() == false)
		{
			p->SetFire(true);
			p->SetPos(_pos);
			p->SetDir(_dir);
			break;
		}
	}
}

void BloodEffect::Init()
{
	m_vecBP.resize(BLOOD_PARTICLE_MAX);

	for (size_t i = 0; i < BLOOD_PARTICLE_MAX; i++)
	{
		//��ƼŬ ���� ���Ϳ� ����
		BloodParticle* bp = new BloodParticle(); bp->Init();
		m_vecBP[i] = bp;
	}
}

void BloodEffect::Update()
{
	for (auto p : m_vecBP)
	{
		//��ƼŬ ���� ������Ʈ, fire�� Ʈ���ξָ� ����
		p->Update();
	}
}

void BloodEffect::Render()
{
	for (auto p : m_vecBP)
	{
		//��ƼŬ ���� ����, fire�� Ʈ���ξָ� ����
		p->Render();
	}
}

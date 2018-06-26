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
		//활성화중이 아닌 파티클을 만나면
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
		//파티클 묶음 벡터에 저장
		BloodParticle* bp = new BloodParticle(); bp->Init();
		m_vecBP[i] = bp;
	}
}

void BloodEffect::Update()
{
	for (auto p : m_vecBP)
	{
		//파티클 묶음 업데이트, fire가 트루인애만 연산
		p->Update();
	}
}

void BloodEffect::Render()
{
	for (auto p : m_vecBP)
	{
		//파티클 묶음 랜더, fire가 트루인애만 랜더
		p->Render();
	}
}

#pragma once
#include "IDisplayObject.h"

#define BLOOD_PARTICLE_MAX 100

class BloodParticle;

class BloodEffect : public IDisplayObject
{
private:
	vector<BloodParticle*>	m_vecBP;

public:
	BloodEffect();
	~BloodEffect();

	void Fire(D3DXVECTOR3 _pos, D3DXVECTOR3 _dir);

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

};


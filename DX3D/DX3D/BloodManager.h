#pragma once
#include "IDisplayObject.h";

class BloodParticle;

#define BLOOD_PARTICLE_MAX 10

class BloodManager : public IDisplayObject
{
private:
	vector<BloodParticle*> m_vecBP;

public:
	BloodManager();
	~BloodManager();

	//피격 되는 코드상에서 스태틱 캐스트로 선언
	//static_cast<BloodManager*>(g_pObjMgr->FindObjectByTag(TAG_PARTICLE))->Fire();
	void Fire();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

};


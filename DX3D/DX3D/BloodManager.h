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

	//�ǰ� �Ǵ� �ڵ�󿡼� ����ƽ ĳ��Ʈ�� ����
	//static_cast<BloodManager*>(g_pObjMgr->FindObjectByTag(TAG_PARTICLE))->Fire();
	void Fire();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

};


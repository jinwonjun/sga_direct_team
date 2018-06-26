#pragma once
#include "IUnitObject.h"

class SkinnedMesh;
class BoundingBox;
class BloodEffect;

class Ironman :
	public IUnitObject
{
public:
	Ironman();
	~Ironman();

	// IUnitObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	D3DXMATRIXA16	matT, matS, matR;

	BoundingBox*	m_pBox;

	SkinnedMesh * m_pSkinnedMesh;

	BoundingBox* GetBoundingBox() { return m_pBox; }

	BloodEffect* m_pBlood;

	D3DXVECTOR3 BloodCalPos;

	D3DXMATRIXA16 ApplyMatWorld;//��Ų�Ž����� �׸��� ���� ��İ��� ���⼭ ��������.

	void Shoot();

	//�ִϸ��̼� �׽�Ʈ�� ���� ���� ����
	bool keyPress;

	void AnimationModify();//X���� ��ġ �� ������ �����κ�.
};


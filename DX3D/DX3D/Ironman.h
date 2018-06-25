#pragma once
#include "SkinnedMesh.h"

class SkinnedMesh;
class BoundingBox;

class Ironman :
	public SkinnedMesh
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

	D3DXVECTOR3 BloodCalPos;

	D3DXMATRIXA16 ApplyMatWorld;//��Ų�Ž����� �׸��� ���� ��İ��� ���⼭ ��������.

	void Shoot();

	void AnimationModify();//X���� ��ġ �� ������ �����κ�.
};


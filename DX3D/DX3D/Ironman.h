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

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	D3DXMATRIXA16	matT, matS, matR;

	BoundingBox*	m_pBox;

	SkinnedMesh * m_pSkinnedMesh;

	BoundingBox* GetBoundingBox() { return m_pBox; }

	D3DXVECTOR3 BloodCalPos;

	D3DXMATRIXA16 ApplyMatWorld;//스킨매쉬에서 그리는 월드 행렬값을 여기서 가져오자.

	void Shoot();

	void AnimationModify();//X파일 위치 및 스케일 조정부분.
};


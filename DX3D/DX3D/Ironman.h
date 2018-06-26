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

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	D3DXMATRIXA16	matT, matS, matR;

	BoundingBox*	m_pBox;

	SkinnedMesh * m_pSkinnedMesh;

	BoundingBox* GetBoundingBox() { return m_pBox; }

	BloodEffect* m_pBlood;

	D3DXVECTOR3 BloodCalPos;

	D3DXMATRIXA16 ApplyMatWorld;//스킨매쉬에서 그리는 월드 행렬값을 여기서 가져오자.

	void Shoot();

	//애니메이션 테스트용 변수 아직 못함
	bool keyPress;

	void AnimationModify();//X파일 위치 및 스케일 조정부분.
};


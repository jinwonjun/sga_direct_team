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

	D3DXMATRIXA16 RightHand;

	void Shoot();

	//애니메이션 테스트용 변수 아직 못함
	bool keyPress;

	//UI 열엇을 시 캐릭터 이동 제한
	bool OpenUI;

	void AnimationModify();//X파일 위치 및 스케일 조정부분.
};

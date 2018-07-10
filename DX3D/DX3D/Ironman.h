#pragma once
#include "IUnitObject.h"

class SkinnedMesh;
class BoundingBox;
class BloodEffect;

class Ironman :
	public IUnitObject
{

private:
	float timer;
	bool checkTimer;

public:
	Ironman();
	~Ironman();

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;



	BoundingBox*	m_pBox;

	SkinnedMesh * m_pSkinnedMesh;

	BoundingBox* GetBoundingBox() { return m_pBox; }

	BloodEffect* m_pBlood;

	D3DXVECTOR3 BloodCalPos;

	D3DXMATRIXA16 RightHand;

	void Shoot();

	//애니메이션 테스트용 변수 아직 못함
	bool keyPress;

	//UI 열었을 시 캐릭터 이동 제한
	bool OpenUI;

	//damagefont를 위한 숫자
	int DamageFontNum;


	void AnimationModify();//X파일 위치 및 스케일 조정부분.

	//아이언맨의 계산된 월드 행렬을 가져오자
	D3DXMATRIXA16 matRotY, matRotX, matT, matR, matS, matTemp;


	void RenderUseShader_0();
	void RenderUseShader_1();
};

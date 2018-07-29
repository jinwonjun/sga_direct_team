#pragma once
#include "IUnitObject.h"

class SkinnedMesh;
class BoundingBox;
class BloodEffect;

#define SCALE 0.1f

class Ironman :
	public IUnitObject
{

private:
	float	timer;
	float	deathTimer;
	bool	checkTimer;
	bool	checkDeathTimer;
	int		check;		//구체 그리는거 체크용 함수

	//피격 구체 그려주기
	vector<BoundingSphere*> m_vecBoundary;
	LPD3DXMESH				m_pSphereMesh;

	int AddAtk;		// 장비로 인한 추가공격력
	int AddMaxHp;	// 장비로 인한 맥스 HP
	int AddDef;		// 장비로 인한 추가방어력

	//사운드를 위해 만든 bool 변수
	bool isRun;

	//총 반동
	bool	isShoot;	//총을 쐈는지
	int		shootTime;	//쏜시점 시간 증가
	int		endTime;	//반동 종료 시간 : 클수록 천천히 오래
	float	recoilPower;//반동 파워

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
	void Death();
	void Hit();
	void Status();
	bool SphereCollideCheck(BoundingSphere player, BoundingSphere Monster);
	vector<BoundingSphere*> GetVecBoundary() { return m_vecBoundary; }

	bool SphereDrawRender;

	//애니메이션 테스트용 변수 아직 못함
	bool keyPress;

	//damagefont를 위한 숫자
	int DamageFontNum;


	void AnimationModify();//X파일 위치 및 스케일 조정부분.
	void AnimationKeySetting();//키입력에 따른 애니메이션 출력만들기
	void SoundSetting();

	//매인 캐릭터의 계산된 월드 행렬을 가져오자
	D3DXMATRIXA16 matRotY, matRotX, matT, matR, matS, matTemp;


	void RenderUseShader_0();
	void RenderUseShader_1();

	bool GetCheckDeathTimer() { return checkDeathTimer; }
};
